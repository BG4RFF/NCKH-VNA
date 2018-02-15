package com.example.thaonguyen.vna;

import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by thaonguyen on 11/20/2017.
 */

public abstract class BluetoothController {
    String buffer = "";
    private BluetoothSocket bluetoothSocket;
    private OutputStream outputStream;
    private InputStream inputStream;

    public BluetoothController(BluetoothSocket bluetoothSocket) throws IOException {
        this.bluetoothSocket = bluetoothSocket;

        this.outputStream = bluetoothSocket.getOutputStream();
        this.inputStream = bluetoothSocket.getInputStream();
    }

    public void sendData(String message) throws IOException {
        outputStream.write(message.getBytes());
    }

    public abstract void error();

    public abstract void disconnect();

    public abstract void receiveData(String data);

    public void sendHello() {
        String json = "{\"TYPE\":\"HELLO\"}\0";

        try {
            sendData(json);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendStart() {
        String json = "{\"TYPE\":\"START\"}\0";

        try {
            sendData(json);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendStop() {
        String json = "{\"TYPE\":\"STOP\"}\0";

        try {
            sendData(json);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void startListening() {
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
                                // Send to UI
                                receiveData(buffer);
                                buffer = "";
                            }
                        }
                    }

                    disconnect();
                } catch (IOException e) {
                    // Error
                    error();
                }
            }
        }).start();
    }
}
