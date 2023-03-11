package com.example.electronbot_android.Comm;

import android.os.Environment;
import android.util.Log;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.RandomAccessFile;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class TcpClientRunnable implements Runnable {

    private String TAG = "TcpClientRunnable";

    private Socket client = null;
    private String serverIp = "192.168.1.158";
    private int serverPort = 3008;
    private byte[] senddata_a;
    private boolean sendFlag = false;

    public TcpClientRunnable(String serverIp, int port) {
        this.serverIp = serverIp;
        this.serverPort = port;
    }

    public String getServerIp() {
        return serverIp;
    }

    public int getServerPort() {
        return serverPort;
    }

    public void sendData(byte[] data){
        senddata_a = data;
        sendFlag = true;
    }

    @Override
    public void run() {
        InputStream in = null;
        OutputStream out = null;
        while(client==null||!client.isConnected()){
            try{
                client = new Socket();
                client.connect(new InetSocketAddress(InetAddress.getByName(serverIp),serverPort),100);
                in = client.getInputStream();
                out = client.getOutputStream();
            }catch(Exception e){
                e.printStackTrace();
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException interruptedException) {
                    interruptedException.printStackTrace();
                }

            }

            if(client!=null&&client.isConnected()){
                if (listener != null){
                    listener.onTcpClientConnectServer(true);
                }
                Log.i(TAG,"onTcpClientConnectServer true");

                int heartNUM = 0;
                while (client!= null && client.isClosed()==false && client.isConnected()) {
                    try {
                        if (in.available()>0) {
                            byte[] b = new byte[1024];    //定义字节数组
                            int len = in.read(b);
                            byte[] tempData = Arrays.copyOf(b, len);
                            String s = new String(tempData);
                            int slen = s.length();
                            if(b[0] == 48 && b[1] == 0 && b[2] == 0 && slen ==8){
                                heartNUM =0;
                            }else {
                                if (listener != null){
                                    listener.onTcpClientReceiveData(s,serverIp,serverPort);
                                }
                                Log.i(TAG,s);
                            }


                        }else{
                            heartNUM ++;
                        }
                        if(heartNUM ==100){
                            sendData("0".getBytes(StandardCharsets.UTF_8));
                        }
                        if (sendFlag) {
                            out.write(senddata_a);
                            sendFlag = false;
                        }
                        if(heartNUM>200){
                            close();
                        }

                    } catch (Exception e) {
                        e.printStackTrace();
                        break;
                    }

                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    //Log.i(TAG,"still con");
                }

                if (listener != null){
                    listener.onTcpClientConnectServer(false);
                }
                Log.i(TAG,"onTcpClientConnectServer false");

                if (listener != null){
                    listener.onTcpClientClose();
                }
                Log.i(TAG,"onTcpClientClose");
            }

            try {
                Thread.sleep(1000);
            } catch (InterruptedException interruptedException) {
                interruptedException.printStackTrace();
            }
        }



    }

    public void close(){
        if (client != null){
            try {
                client.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
        client = null;
    }

    private TcpClientListener listener;

    public void setListener(TcpClientListener listener) {
        this.listener = listener;
    }

    public interface TcpClientListener{
        void onTcpClientConnectServer(boolean flag);
        void onTcpClientReceiveData(String data,String serverIp,int serverPort);
        void onTcpClientClose();
    }
}
