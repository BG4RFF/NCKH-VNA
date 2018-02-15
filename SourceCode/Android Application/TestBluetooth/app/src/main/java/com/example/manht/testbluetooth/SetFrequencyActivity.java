package com.example.manht.testbluetooth;

import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.AsyncTask;
import android.os.IBinder;
import android.os.SystemClock;
import android.support.v4.content.LocalBroadcastManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static java.lang.Math.abs;

public class SetFrequencyActivity extends AppCompatActivity {
    public static final String EXTRA_FREQUENCY = "MEASURE_FREQUENCY";
    public static final String EXTRA_MAGNITUDE_RESULT = "EXTRA_MAGNITUDE_RESULT";
    public static final String EXTRA_PHASE_RESULT = "EXTRA_PHASE_RESULT";
    public static final int MAX_RETRY_MEASURE_COUNT = 3;
    public static final double MIN_FREQUENCY = 135.5;
    public static final double MAX_FREQUENCY = 4400;
    public static final int WAITING_FOR_MEASURE_RESPONCE_TIME_MS = 4000; // 4s

    Button btnSetFrequency, btn315MHz, btn433MHz, btn868MHz, btn2400MHz, btnDel, btnComma;
    EditText txtFrequency;
    ProgressDialog progressDialog;

    private BluetoothComunicationService service;
    private boolean serviceBounded = false;

    private boolean receiveMessageProcessed = true;
    private String receiveMessageBuffer = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set_frequency);

        LocalBroadcastManager.getInstance(this).registerReceiver(new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if (receiveMessageProcessed) {
                    receiveMessageBuffer = intent.getStringExtra(BluetoothComunicationService.EXTRA_MESSAGE);
                    receiveMessageProcessed = false;
                }
            }
        }, new IntentFilter(BluetoothComunicationService.ACTION_BROADCASE_MESSAGE));

        txtFrequency = (EditText) findViewById(R.id.txtFrequency);

        progressDialog = new ProgressDialog(this);
        progressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        progressDialog.setIndeterminate(false);
        progressDialog.setProgress(0);
        progressDialog.setMax(100);
        progressDialog.setCanceledOnTouchOutside(false);
        progressDialog.setCancelable(false);

        btnComma = (Button) findViewById(R.id.btnComma);
        btnComma.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtFrequency.getText().append(",");
            }
        });

        btnDel = (Button) findViewById(R.id.btnDel);
        btnDel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String[] frequencyArray = txtFrequency.getText().toString().split(",");
                String str = "";
                for (int i = 0; i < frequencyArray.length - 1; i++) {
                    str += frequencyArray[i] + ",";
                }
                txtFrequency.setText(str);
                txtFrequency.setSelection(str.length());
            }
        });

        btn315MHz = (Button) findViewById(R.id.btn315MHz);
        btn315MHz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtFrequency.getText().append("315,");
            }
        });

        btn433MHz = (Button) findViewById(R.id.btn433MHz);
        btn433MHz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtFrequency.getText().append("433,");
            }
        });

        btn868MHz = (Button) findViewById(R.id.btn868MHz);
        btn868MHz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtFrequency.getText().append("868,");
            }
        });

        btn2400MHz = (Button) findViewById(R.id.btn2400MHz);
        btn2400MHz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                txtFrequency.getText().append("2400,");
            }
        });


        btnSetFrequency = (Button) findViewById(R.id.btnSetFrequency);
        btnSetFrequency.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                /* DEBUG */
//                double freqArrTmp[] = {315, 433, 868, 2400};
//                double magArrTmp[] = {-20.12, -12.3, -31.75, -28.15};
//
//                Intent newActivityIntent = new Intent(SetFrequencyActivity.this, DisplayDiagram.class);
//                newActivityIntent.putExtra(EXTRA_FREQUENCY, freqArrTmp);
//                newActivityIntent.putExtra(EXTRA_MAGNITUDE_RESULT, magArrTmp);
//                startActivity(newActivityIntent);
                /* DEBUG */

                String frequency = txtFrequency.getText().toString();
                String[] frequencyArray = frequency.split(",");
                List<Double> frequencyList = new ArrayList<Double>();
                double[] sortedDistinctDoubleFrequencyArray = null;

                boolean availableFrequenciesFlag = true;

                if (frequencyArray.length == 0) {
                    availableFrequenciesFlag = false;
                } else {
                    for (int i = 0; i < frequencyArray.length; i++) {
                        try {
                            double value = Double.parseDouble(frequencyArray[i]);

                            if ((frequencyList.indexOf(value) == -1) && (value >= MIN_FREQUENCY) && (value <= MAX_FREQUENCY)) {
                                frequencyList.add(value);
                            }
                        } catch (NumberFormatException e) {
                            availableFrequenciesFlag = false;
                        }
                    }
                }

                if (availableFrequenciesFlag) {
                    sortedDistinctDoubleFrequencyArray = new double[frequencyList.size()];
                    for (int i = 0; i < frequencyList.size(); i++) {
                        sortedDistinctDoubleFrequencyArray[i] = frequencyList.get(i);
                    }
                    Arrays.sort(sortedDistinctDoubleFrequencyArray);

                    MeasureTask measureTask = new MeasureTask(sortedDistinctDoubleFrequencyArray);
                    measureTask.execute();
                } else {
                    Toast.makeText(getApplicationContext(), "Frequency(s) not available, enter again", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();

        Intent intent = new Intent(SetFrequencyActivity.this, BluetoothComunicationService.class);
        bindService(intent, mConnection, Context.BIND_AUTO_CREATE);
    }

    @Override
    protected void onStop() {
        super.onStop();

        if (serviceBounded) {
            unbindService(mConnection);
            serviceBounded = false;
        }
    }

    private ServiceConnection mConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            BluetoothComunicationService.LocalBinder binder = (BluetoothComunicationService.LocalBinder) iBinder;
            service = binder.getService();
            serviceBounded = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            serviceBounded = false;
        }
    };

    private class MeasureTask extends AsyncTask<Void, String, Void> {
        private double[] frequencyArray, magnitudeResultArray;
        private boolean mMeasureSuccess = true;

        public MeasureTask(double[] frequencies) {
            frequencyArray = frequencies;
            magnitudeResultArray = new double[frequencyArray.length];
        }

        @Override
        protected void onPreExecute() {
            progressDialog.show();
        }

        @Override
        protected Void doInBackground(Void... voids) {
            mMeasureSuccess = true;
            double freq;
            for (int i = 0; i < frequencyArray.length; i++) {
                freq = frequencyArray[i];
                try {
                    int retryCount = 0;
                    while (retryCount < MAX_RETRY_MEASURE_COUNT) {
                        publishProgress("Measuring at frequency " + freq + " MHz (Retry " + (retryCount + 1) + "/" + MAX_RETRY_MEASURE_COUNT + ")");
                        String message = getJSONStringMeasureRequest(freq) + "\0";
                        service.SendMessage(message);

                        SystemClock.sleep(WAITING_FOR_MEASURE_RESPONCE_TIME_MS);

                        if (!receiveMessageProcessed) {
                            try {
                                JSONObject object = new JSONObject(receiveMessageBuffer);
                                double frequency = object.getDouble("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ");

                                if (abs(frequency - freq) <= 0.25) {
                                    double mag = object.getDouble("MAGNITUDE");
                                    magnitudeResultArray[i] = mag;

                                    receiveMessageProcessed = true;
                                    break;
                                } else {
                                    receiveMessageProcessed = false;
                                }
                            } catch (JSONException e) {
                                receiveMessageProcessed = false;
                            }
                        } else {
                            retryCount++;
                        }
                    }

                    if (retryCount == MAX_RETRY_MEASURE_COUNT) {
                        mMeasureSuccess = false;
                        break; // Stop measure
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return null;
        }

        @Override
        protected void onProgressUpdate(String... values) {
            progressDialog.setMessage(values[0]);
        }

        @Override
        protected void onPostExecute(Void result) {
            progressDialog.dismiss();

            if (mMeasureSuccess) {
                Intent newActivityIntent = new Intent(SetFrequencyActivity.this, DisplayDiagram.class);
                newActivityIntent.putExtra(EXTRA_FREQUENCY, frequencyArray);
                newActivityIntent.putExtra(EXTRA_MAGNITUDE_RESULT, magnitudeResultArray);
                startActivity(newActivityIntent);
            } else {
                Toast.makeText(getApplicationContext(), "Measuring fail", Toast.LENGTH_SHORT).show();
            }
        }

        private String getJSONStringMeasureRequest(double frequency) {
            try {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("TYPE", "MEASURE");
                jsonObject.put("FREQUENCY", frequency);
                return jsonObject.toString();
            } catch (JSONException e) {
                e.printStackTrace();
                return null; // Fail to create
            }
        }
    }
}
