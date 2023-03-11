package com.example.electronbot_android;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.telephony.TelephonyManager;
import android.util.Log;

public class PhoneStateBroadCastReceiver  extends BroadcastReceiver {
    private static final String TAG = "PhoneState";

    private static boolean mIncomingFlag = true;
    private static String mIncomingNumber = null;
    ElectronService service;

    public void setServer(ElectronService service){
        this.service = service;
    }
    @Override
    public void onReceive(Context context, Intent intent) {
        // 如果是拨打电话
        if (intent.getAction().equals(Intent.ACTION_NEW_OUTGOING_CALL))
        {
            mIncomingFlag = false;
            String phoneNumber = intent.getStringExtra(Intent.EXTRA_PHONE_NUMBER);
            Log.i(TAG, "call OUT:" + phoneNumber);
        } else
        {
            // 如果是来电
            TelephonyManager tManager =
                    (TelephonyManager) context.getSystemService(Service.TELEPHONY_SERVICE);
            switch (tManager.getCallState())
            {
                case TelephonyManager.CALL_STATE_RINGING:
                    service.setOnPhoneCallStatusChange("CALL_STATE_RINGING");
                    break;
                case TelephonyManager.CALL_STATE_OFFHOOK:
                    service.setOnPhoneCallStatusChange("CALL_STATE_OFFHOOK");
                    break;
                case TelephonyManager.CALL_STATE_IDLE:
                    service.setOnPhoneCallStatusChange("CALL_STATE_IDLE");
                    break;
            }
        }
    }

}
