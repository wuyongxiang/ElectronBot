#ifndef ELECTRONBOTSDK_ELECTRONCONTROLLER_H
#define ELECTRONBOTSDK_ELECTRONCONTROLLER_H

#include <iostream>
#include <cstdio>
#include <thread>
#include "electron_low_level.h"
#include <electron_player.h>
#include<queue>

using namespace std;

class __declspec(dllexport) ElectronController
{
public:
    ElectronController()
    {
        player = new ElectronPlayer();
    }

    ~ElectronController()
    {

    }
    
    bool isCalling = false;
    int callNum = 0;

    ElectronPlayer* player;
    queue<ElectronPlayer::RobotTask> robotTasks;

    bool Connect();
    void Init();
    void MsgFromTCP(const char* msg,SOCKET s);
    void Disconnect();
    //void Play_Follow();
    ElectronPlayer::RobotTask Stay_ss();
    ElectronPlayer::RobotTask Stay_ss1();
    ElectronPlayer::RobotTask Stay_ss2();

    ElectronPlayer::RobotTask LookLeft_start();
    ElectronPlayer::RobotTask LookLeft_cycle();
    ElectronPlayer::RobotTask Lookleft_end();

    ElectronPlayer::RobotTask LookRight_start();
    ElectronPlayer::RobotTask LookRight_cycle();
    ElectronPlayer::RobotTask LookRight_end();

    ElectronPlayer::RobotTask Happy_start(bool isOpen);
    ElectronPlayer::RobotTask Happy_cycle();
    ElectronPlayer::RobotTask Happy_end();

    ElectronPlayer::RobotTask Sad_start(bool isClose);
    ElectronPlayer::RobotTask Sad_cycle();
    ElectronPlayer::RobotTask Sad_end();

    ElectronPlayer::RobotTask Disdain_start();
    ElectronPlayer::RobotTask Disdain_cycle();
    ElectronPlayer::RobotTask Disdain_end();

    ElectronPlayer::RobotTask Angry_start();
    ElectronPlayer::RobotTask Angry_cycle();
    ElectronPlayer::RobotTask Angry_cycle_calling();
    ElectronPlayer::RobotTask Angry_end();

    ElectronPlayer::RobotTask Alarmed_start();
    ElectronPlayer::RobotTask Alarmed_cycle();
    ElectronPlayer::RobotTask Alarmed_cycle_calling();
    ElectronPlayer::RobotTask Alarmed_end();

    void RunTask();
    void CallingTask();
    void AssignTasks(int num);
    void AddTask(ElectronPlayer::RobotTask task);
    void AddTask(ElectronPlayer::RobotTask task ,bool needQueue); 
    void ClearTask();
private:


};


#endif