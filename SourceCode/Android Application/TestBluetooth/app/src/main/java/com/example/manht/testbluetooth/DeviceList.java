package com.example.manht.testbluetooth;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
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
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class DeviceList extends AppCompatActivity {
    public static final String EXTRA_ADDRESS = "DEVICE_ADDRESS";
    public static final int REQUEST_ENABLE_BT = 1;
    public static final int NUM_OF_MAX_HELLO_TO_DEVICE_COUNT = 3;
    public static final int WAITING_HELLO_RESPONCE_TIME_MS = 3000; // 3s
    public static final int PROGRESS_CODE_ERROR = -1;

    private ProgressDialog progress;
    Button btnRefresh;
    ListView deviceList;

    private BluetoothAdapter bluetoothAdapter = null;

    private BluetoothComunicationService service;
    private boolean serviceBounded = false;

    private boolean receiveMessageProcessed = true;
    private String receiveMessageBuffer = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Intent startBluethoothServiceIntent = new Intent(this, BluetoothComunicationService.class);
        startService(startBluethoothServiceIntent);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_list);

        LocalBroadcastManager.getInstance(getApplicationContext()).registerReceiver(new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if (receiveMessageProcessed) {
                    receiveMessageBuffer = intent.getStringExtra(BluetoothComunicationService.EXTRA_MESSAGE);
                    receiveMessageProcessed = false;
                }
            }
        }, new IntentFilter(BluetoothComunicationService.ACTION_BROADCASE_MESSAGE));

        btnRefresh = (Button) findViewById(R.id.btnRefreshList);
        deviceList = (ListView) findViewById(R.id.listView);

        progress = new ProgressDialog(this);
        progress.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        progress.setIndeterminate(false);
        progress.setProgress(0);
        progress.setMax(2);
        progress.setCanceledOnTouchOutside(false);
        progress.setCancelable(false);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null) {
            Toast.makeText(getApplicationContext(), "Bluetooth Device Not Available", Toast.LENGTH_LONG).show();
            finish();
        } else {
            if (bluetoothAdapter.isEnabled()) {

            } else {
                Intent turnBluetoothOnIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(turnBluetoothOnIntent, REQUEST_ENABLE_BT);
            }
        }

        btnRefresh.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                updateDeviceList();
            }
        });

        updateDeviceList();
    }

    public void updateDeviceList() {
        Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();
        List pairedDeviceList = new ArrayList();

        if (pairedDevices.size() > 0) {
            for (BluetoothDevice device : pairedDevices) {
                pairedDeviceList.add(device.getName() + "\n" + device.getAddress());
            }
        } else {
            Toast.makeText(getApplicationContext(), "No Paired Bluetooth Devices Found.", Toast.LENGTH_LONG).show();
        }

        final ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, pairedDeviceList);
        deviceList.setAdapter(adapter);
        deviceList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                // Get the device MAC address, the last 17 chars in the View
                String info = ((TextView) view).getText().toString();
                String address = info.substring(info.length() - 17);

                SayHelloToDevice_AsyncTask asyncTask = new SayHelloToDevice_AsyncTask(address);
                asyncTask.execute();
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();

        Intent intent = new Intent(DeviceList.this, BluetoothComunicationService.class);
        bindService(intent, mConnection, Context.BIND_AUTO_CREATE);
    }

    @Override
    protected void onResume() {
        super.onResume();

        try {
            if (service != null) {
                service.disconnect();
            }
        } catch (IOException e) {
            Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_LONG).show();
        }
    }

    @Override
    protected void onStop() {
        super.onStop();

        if (serviceBounded) {
            unbindService(mConnection);
            serviceBounded = false;
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        Intent stopBluetoothServiceIntent = new Intent(this, BluetoothComunicationService.class);
        stopService(stopBluetoothServiceIntent);
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

    private class SayHelloToDevice_AsyncTask extends AsyncTask<Void, Integer, Void> {
        private String mAddress = null;
        private boolean connectSuccessFlag = true;

        public SayHelloToDevice_AsyncTask(String address) {
            mAddress = address;
        }

        @Override
        protected void onPreExecute() {
            progress.setMessage("Waiting for response from device...");
            progress.show();
        }

        @Override
        protected Void doInBackground(Void... voids) {
            connectSuccessFlag = true;

            try {
                service.connect(mAddress);
            } catch (IOException e) {
                connectSuccessFlag = false;
                publishProgress(PROGRESS_CODE_ERROR);
                return null;
            }

            JSONObject helloObject = null;
            try {
                helloObject = new JSONObject();
                helloObject.put("TYPE", "HELLO");
            } catch (JSONException e) {
                connectSuccessFlag = false;
                publishProgress(PROGRESS_CODE_ERROR);
                return null;
            }

            int retryCount = 0;
            while (retryCount < NUM_OF_MAX_HELLO_TO_DEVICE_COUNT) {
                try {
                    service.SendMessage(helloObject.toString() + "\0");
                } catch (IOException e) {
                    publishProgress(PROGRESS_CODE_ERROR);
                }

                SystemClock.sleep(WAITING_HELLO_RESPONCE_TIME_MS);

                // READ INPUT FOR HELLO RESPONCE
                if (!receiveMessageProcessed) {
                    try {
                        JSONObject responce = new JSONObject(receiveMessageBuffer);
                        String messageType = responce.getString("TYPE");
                        if (messageType.equals("HELLO")) {
                            receiveMessageProcessed = true;
                            connectSuccessFlag = true;
                            return null;
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }

                publishProgress(++retryCount);
            }

            connectSuccessFlag = false;
            return null;
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            super.onProgressUpdate(values);

            switch (values[0]) {
                case PROGRESS_CODE_ERROR:
                    Toast.makeText(getApplicationContext(), "Something wrong", Toast.LENGTH_LONG).show();
                    break;
                default:
                    progress.setMessage("[" + values[0] + "/" + progress.getMax() + "] Retry...");
                    break;
            }
        }

        @Override
        protected void onPostExecute(Void voids) {
            super.onPostExecute(voids);
            progress.dismiss();

            /* DEBUG */
//            Intent newActivityIntent = new Intent(DeviceList.this, SetFrequencyActivity.class);
//            startActivity(newActivityIntent);
            /* DEBUG */

            if (connectSuccessFlag) {
                // Make an intent to start next activity.
                Intent newActivityIntent = new Intent(DeviceList.this, SetFrequencyActivity.class);
                startActivity(newActivityIntent);
            } else {
                Toast.makeText(getApplicationContext(), "Fail to pair to device.", Toast.LENGTH_LONG).show();

                try {
                    service.disconnect();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
