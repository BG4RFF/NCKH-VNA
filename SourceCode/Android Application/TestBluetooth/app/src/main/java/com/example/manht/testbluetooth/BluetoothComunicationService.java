package com.example.manht.testbluetooth;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.support.v4.content.LocalBroadcastManager;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class BluetoothComunicationService extends Service {
    public static final String
            ACTION_BROADCASE_MESSAGE = "ACTION_BROADCASE_MESSAGE",
            EXTRA_MESSAGE = "EXTRA_MESSAGE";
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    private final IBinder mBinder = new LocalBinder();

    private BluetoothSocket bluetoothSocket;
    private OutputStream outputStream;
    private InputStream inputStream;

    String buffer = "";

    public BluetoothComunicationService() {
        super();
    }

    @Override
    public void onCreate() {
        Log.d("DEBUG", "CALLED");
    }

    @Override
    public void onDestroy() {
        Log.d("DEBUG", "CALLED");
    }

    public void connect(String address) throws IOException {
        String bluetoothDeviceAddress = address;

        disconnect();

        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        BluetoothDevice device = bluetoothAdapter.getRemoteDevice(bluetoothDeviceAddress);
        bluetoothSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
        BluetoothAdapter.getDefaultAdapter().cancelDiscovery();

        bluetoothSocket.connect();

        outputStream = bluetoothSocket.getOutputStream();
        inputStream = bluetoothSocket.getInputStream();

        StartListening();
    }

    public void disconnect() throws IOException {
        if ((bluetoothSocket != null) && bluetoothSocket.isConnected()) {
            bluetoothSocket.close();
        }
    }

    public class LocalBinder extends Binder {
        public BluetoothComunicationService getService() {
            return BluetoothComunicationService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    public void SendMessage(String message) throws IOException {
        outputStream.write(message.getBytes());
    }

    private void StartListening() {
        (new Thread() {
            @Override
            public void run() {
                try {
                    while (bluetoothSocket.isConnected()) {
                        if (inputStream.available() > 0) {
                            byte[] inputBytes = new byte[1];
                            inputBytes[0] = (byte) inputStream.read();

                            if (inputBytes[0] != '\0') {
                                buffer += new String(inputBytes);
                            } else {
                                Intent intent = new Intent(ACTION_BROADCASE_MESSAGE);
                                intent.putExtra(EXTRA_MESSAGE, buffer);
                                buffer = "";
                                LocalBroadcastManager.getInstance(getApplicationContext()).sendBroadcast(intent);
                            }
                        }
                    }
                } catch (IOException e) {
                    // Error
                }
            }
        }).start();
    }
}
