package com.example.electronbot_android;

import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.IBinder;

//监视服务的状态
public class MyConn implements ServiceConnection {

    private ElectronService.ElfBinder myBinder;//我定义的中间人对象
    private final static MyConn instance = new MyConn();
    private MyConn(){}
    public static MyConn getInstance(){
        return instance;
    }
    //当服务连接成功调用
    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {
        //获取中间人对象
        myBinder = (ElectronService.ElfBinder) service;
    }

    public ElectronService.ElfBinder getMyBinder() {
        return myBinder;
    }

    //失去连接
    @Override
    public void onServiceDisconnected(ComponentName name) {

    }
}