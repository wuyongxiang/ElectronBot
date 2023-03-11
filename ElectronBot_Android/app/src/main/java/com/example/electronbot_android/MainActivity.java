package com.example.electronbot_android;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.example.electronbot_android.Comm.Msg;

import java.util.ArrayList;
import java.util.List;


public class MainActivity extends AppCompatActivity {
    EditText edt_send;
    Button btn_send;
    private MyConn conn;
    MsgReceiver msgReceiver ;
    private RecyclerView msgRecyclerView;
    private MsgAdapter adapter;
    private List<Msg> msgList = new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        edt_send = findViewById(R.id.edt_send);
        btn_send = findViewById(R.id.btn_send);
        Intent intent = new Intent(this, ElectronService.class);
        conn = MyConn.getInstance();
        bindService(intent, conn, BIND_AUTO_CREATE);

        btn_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                conn.getMyBinder().sendCmd(edt_send.getText().toString());
                Msg msg = new Msg(edt_send.getText().toString() +" :I",Msg.TYPE_SENT);
                msgList.add(msg);
                adapter.notifyItemInserted(msgList.size()-1);
                msgRecyclerView.scrollToPosition(msgList.size()-1);
                edt_send.setText("");
            }
        });
        msgReceiver = new MsgReceiver();
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("com.example.communication.RECEIVER");
        registerReceiver(msgReceiver, intentFilter);
        msgRecyclerView = (RecyclerView) findViewById(R.id.msg_recycler_view);
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        msgRecyclerView.setLayoutManager(layoutManager);
        adapter = new MsgAdapter(msgList);
        msgRecyclerView.setAdapter(adapter);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(msgReceiver);
    }
    public class MsgReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            String s = intent.getStringExtra("msgFromElectron");
            Msg msg = new Msg("Electron: "+s,Msg.TYPE_RECEIVED);
            msgList.add(msg);
            adapter.notifyItemInserted(msgList.size()-1);
            msgRecyclerView.scrollToPosition(msgList.size()-1);
        }
    }


}