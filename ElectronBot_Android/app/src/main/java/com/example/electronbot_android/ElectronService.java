package com.example.electronbot_android;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Configuration;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

import com.example.electronbot_android.Comm.Msg;
import com.example.electronbot_android.Comm.TcpClientRunnable;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class ElectronService extends Service {
	public TcpClientRunnable tcpClientRunnable;
	ExecutorService cachedThreadPool = Executors.newCachedThreadPool();
	PhoneStateBroadCastReceiver phoneStateBroadCastReceiver;
	public IBinder onBind(Intent intent) {
		return new ElfBinder();
	}
	//[1]定义中间人对象(IBinder)

	public boolean tcpClientConnect = false;
	public class ElfBinder extends Binder {
		public void sendCmd(String cmd){
			tcpClientRunnable.sendData(cmd.getBytes(StandardCharsets.UTF_8));
		}
	}
	@Override
	public void onCreate() {
		super.onCreate();
		tcpClientRunnable = new TcpClientRunnable("192.168.1.108",3008);
		tcpClientRunnable.setListener(tcpClientListener);
		cachedThreadPool.execute(tcpClientRunnable);
		IntentFilter filter = new IntentFilter();
		filter.addAction("android.intent.action.NEW_OUTGOING_CALL");
		filter.addAction("android.intent.action.PHONE_STATE");
		phoneStateBroadCastReceiver = new PhoneStateBroadCastReceiver();
		phoneStateBroadCastReceiver.setServer(this);
		registerReceiver(phoneStateBroadCastReceiver,filter);

	}

	public void setOnPhoneCallStatusChange(String status){
		tcpClientRunnable.sendData(status.getBytes(StandardCharsets.UTF_8));
	}
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.e("TopAppService", "服务执行了");
		//telephony();
		phoneStateBroadCastReceiver = new PhoneStateBroadCastReceiver();

		return super.onStartCommand(intent, flags, startId);
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
	}

	TcpClientRunnable.TcpClientListener tcpClientListener = new TcpClientRunnable.TcpClientListener() {
		@Override
		public void onTcpClientConnectServer(boolean flag) {
			String tcpClientData = "";
			if (flag) {
				tcpClientData += "connected";
			} else {
				tcpClientData += "disconnected";
			}
			tcpClientData += "\n";
			Log.d("tcpClientData", tcpClientData);
			String finalTcpClientData = tcpClientData;
			tcpClientConnect = true;
		}

		@Override
		public void onTcpClientReceiveData(final String s, String serverIp, int serverPort) {
			Intent intent = new Intent("com.example.communication.RECEIVER");
			intent.putExtra("msgFromElectron", s);
			sendBroadcast(intent);

		}

		@Override
		public void onTcpClientClose() {
			tcpClientConnect = false;
		}
	};



	@Override
	public void onDestroy() {
		super.onDestroy();
		tcpClientRunnable.close();
	}
}





























