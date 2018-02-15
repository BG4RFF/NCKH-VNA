package com.example.thaonguyen.vna;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.Color;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.AxisBase;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.formatter.IAxisValueFormatter;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.Flushable;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.UUID;

public class MeasureActivity extends AppCompatActivity {
    LineChart lineChart;
    ProgressDialog progress;
    Switch swChannel868, swChannel2400, swWithConnector;
    TextView tvDeviceName, tvMinValue, tvMaxValue, tvAvgValue;

    String jsonResult = "";
    Float[] F868ResultArray, F2400ResultArray;

    String deviceName, deviceAddress;
    private BluetoothSocket bluetoothSocket;
    BluetoothController controller;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    Handler mainHandler;

    void connectToDevice() throws IOException {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        BluetoothDevice device = bluetoothAdapter.getRemoteDevice(deviceAddress);
        bluetoothSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
        BluetoothAdapter.getDefaultAdapter().cancelDiscovery();

        bluetoothSocket.connect();

        controller = new BluetoothController(bluetoothSocket) {

            @Override
            public void error() {
                Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_SHORT).show();
                finish();
            }

            @Override
            public void disconnect() {
                mainHandler.post(new Runnable() {

                    @Override
                    public void run() {
                        Toast.makeText(getApplicationContext(), "Device disconnected", Toast.LENGTH_SHORT).show();
                        finish();
                    }
                });
            }

            @Override
            public void receiveData(String data) {
                try {
                    JSONObject receivedObject = new JSONObject(data);
                    String type = receivedObject.getString("TYPE");
                    switch (type) {
                        case "F868": {
                            int freq = receivedObject.getInt("FREQ");
                            float result = (float) receivedObject.getDouble("RES");

                            int index = freq - 860;
                            if (index >= 0 && index <= 70) {
                                F868ResultArray[index] = result;
                            }

                            mainHandler.post(new Runnable() {
                                @Override
                                public void run() {
                                    if (swChannel868.isChecked()) {
                                        List<Float> dataSet = new ArrayList<Float>(Arrays.asList(F868ResultArray));
                                        setData868(dataSet);
                                        updateMaxMinAvg868();
                                    }
                                }
                            });

                            break;
                        }
                        case "F2400": {
                            int freq = receivedObject.getInt("FREQ");
                            float result = (float) receivedObject.getDouble("RES");

                            int index = freq - 2400;
                            if (index >= 0 && index <= 125) {
                                F2400ResultArray[index] = result;
                            }

                            mainHandler.post(new Runnable() {
                                @Override
                                public void run() {
                                    if (swChannel2400.isChecked()) {
                                        List<Float> dataSet = new ArrayList<Float>(Arrays.asList(F2400ResultArray));
                                        setData2400(dataSet);
                                        updateMaxMinAvg2400();
                                    }
                                }
                            });
                            break;
                        }
                        default:
                            final String message = data;
                            Toast.makeText(getApplicationContext(), "ERROR:\n" + message, Toast.LENGTH_SHORT).show();
                            break;
                    }


                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        };
    }

    private void getViews() {
        tvDeviceName = (TextView) findViewById(R.id.tv_device_name);
        tvMinValue = (TextView) findViewById(R.id.tv_min_value);
        tvMaxValue = (TextView) findViewById(R.id.tv_max_value);
        tvAvgValue = (TextView) findViewById(R.id.tv_avg_value);

        lineChart = (LineChart) findViewById(R.id.chart);
        lineChart.getDescription().setEnabled(false);
        lineChart.setPinchZoom(true);
        lineChart.getAxisRight().setEnabled(false);

        progress = new ProgressDialog(this);
        progress.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        progress.setIndeterminate(false);
        progress.setProgress(0);
        progress.setMax(2);
        progress.setCanceledOnTouchOutside(false);
        progress.setCancelable(false);

        swChannel868 = (Switch) findViewById(R.id.sw_channel_868);
        swChannel868.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b) {
                    swChannel2400.setChecked(false);

                    controller.sendStart();
                } else {
                    if (!swChannel2400.isChecked()) {
                        lineChart.clear();
                        lineChart.invalidate();
                        controller.sendStop();
                    }
                }
            }
        });

        swChannel2400 = (Switch) findViewById(R.id.sw_channel_2400);
        swChannel2400.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b) {
                    swChannel868.setChecked(false);

                    controller.sendStart();
                } else {
                    if (!swChannel868.isChecked()) {
                        lineChart.clear();
                        lineChart.invalidate();

                        controller.sendStop();
                    }
                }
            }
        });

        swWithConnector = (Switch) findViewById(R.id.sw_with_connector);
        swWithConnector.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {

            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();

        try {
            bluetoothSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // remove title
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_measure);

        mainHandler = new Handler(this.getMainLooper());
        F868ResultArray = new Float[71];
        for (int i = 0; i < 71; i++) {
            F868ResultArray[i] = Float.valueOf(0);
        }
        F2400ResultArray = new Float[126];
        for (int i = 0; i < 126; i++) {
            F2400ResultArray[i] = Float.valueOf(0);
        }

        Intent intent = getIntent();
        deviceName = intent.getStringExtra(DeviceList.EXTRA_BLUETOOTH_NAME);
        deviceAddress = intent.getStringExtra(DeviceList.EXTRA_BLUETOOTH_ADDRESS);

        getViews();

        try {
            connectToDevice();
        } catch (IOException ex) {
            Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_SHORT).show();
            finish();
        }

        controller.startListening();
    }

    @Override
    protected void onStart() {
        super.onStart();

        tvDeviceName.setText("Device: " + deviceName);
    }

    private void setData868(List<Float> DataSet1) {
        List<String> Labels = new ArrayList<>();
        for (int i = 0; i < 71; i++) {
            Labels.add(String.valueOf(860 + i));
        }

        List<ILineDataSet> dataSets = new ArrayList<ILineDataSet>();

        List<Entry> entries1 = new ArrayList<Entry>();
        for (int i = 0; i < DataSet1.size(); i++) {
            entries1.add(new Entry(i, DataSet1.get(i)));
        }
        LineDataSet dataSet1 = new LineDataSet(entries1, "868 MHz");
        dataSet1.setColor(Color.rgb(127, 223, 255));
        dataSets.add(dataSet1);

        final List<String> labels = Labels;
        IAxisValueFormatter axisValueFormatter = new IAxisValueFormatter() {
            @Override
            public String getFormattedValue(float value, AxisBase axis) {
                if (value < labels.size()) {
                    return labels.get((int) value);
                } else {
                    return "Undefined";
                }
            }
        };
        XAxis xAxis = lineChart.getXAxis();
        xAxis.setGranularity(1f);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawAxisLine(false);
        xAxis.setValueFormatter(axisValueFormatter);

        YAxis yAxis = lineChart.getAxisLeft();
        yAxis.setAxisMinimum(-30);
        yAxis.setAxisMaximum(5);

        LineData lineData = new LineData(dataSets);
        if (DataSet1.size() > 0) {
            lineChart.setData(lineData);
        } else {
            lineChart.clear();
        }
        lineChart.invalidate();
    }

    private void setData2400(List<Float> DataSet1) {
        List<String> Labels = new ArrayList<>();
        for (int i = 0; i < 126; i++) {
            Labels.add(String.valueOf(2400 + i));
        }

        List<ILineDataSet> dataSets = new ArrayList<ILineDataSet>();

        List<Entry> entries1 = new ArrayList<Entry>();
        for (int i = 0; i < DataSet1.size(); i++) {
            entries1.add(new Entry(i, DataSet1.get(i)));
        }
        LineDataSet dataSet1 = new LineDataSet(entries1, "2.4GHz");
        dataSet1.setColor(Color.rgb(255, 199, 104));
        dataSets.add(dataSet1);

        final List<String> labels = Labels;
        IAxisValueFormatter axisValueFormatter = new IAxisValueFormatter() {
            @Override
            public String getFormattedValue(float value, AxisBase axis) {
                if (value < labels.size()) {
                    return labels.get((int) value);
                } else {
                    return "Undefined";
                }
            }
        };
        XAxis xAxis = lineChart.getXAxis();
        xAxis.setGranularity(1f);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawAxisLine(false);
        xAxis.setValueFormatter(axisValueFormatter);

        YAxis yAxis = lineChart.getAxisLeft();
        yAxis.setAxisMinimum(-30);
        yAxis.setAxisMaximum(5);

        LineData lineData = new LineData(dataSets);
        if (DataSet1.size() > 0) {
            lineChart.setData(lineData);
        } else {
            lineChart.clear();
        }
        lineChart.invalidate();
    }

    void updateMaxMinAvg868() {
        Float max = Float.valueOf(-100);
        Float min = Float.valueOf(100);
        Float avg = Float.valueOf(0);

        for (int i = 0; i < 71; i++) {
            avg += F868ResultArray[i];

            if (F868ResultArray[i] < min) {
                min = F868ResultArray[i];
            }

            if (F868ResultArray[i] > max) {
                max = F868ResultArray[i];
            }
        }

        avg /= 71;

        // Update UI
        tvMaxValue.setText("Max: " + String.valueOf(max));
        tvMinValue.setText("Min: " + String.valueOf(min));
        tvAvgValue.setText("Avg: " + String.valueOf(avg));
    }

    void updateMaxMinAvg2400() {
        Float max = Float.valueOf(-100);
        Float min = Float.valueOf(100);
        Float avg = Float.valueOf(0);

        for (int i = 0; i < 126; i++) {
            avg += F2400ResultArray[i];

            if (F2400ResultArray[i] < min) {
                min = F2400ResultArray[i];
            }

            if (F2400ResultArray[i] > max) {
                max = F2400ResultArray[i];
            }
        }

        avg /= 71;

        // Update UI
        tvMaxValue.setText("Max: " + String.valueOf(max));
        tvMinValue.setText("Min: " + String.valueOf(min));
        tvAvgValue.setText("Avg: " + String.valueOf(avg));
    }
}
