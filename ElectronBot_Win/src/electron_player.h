#ifndef ELECTRONBOTSDK_ELECTRONPLAYER_H
#define ELECTRONBOTSDK_ELECTRONPLAYER_H

#include <iostream>
#include <cstdio>
#include <thread>
#include "electron_low_level.h"
#include<vector>
#include<iostream>
#include "../AudioClip.h"
#include <time.h>  

using namespace std;

class __declspec(dllexport) ElectronPlayer
{
public:
    ElectronPlayer()
    {
        lowLevelHandle = new ElectronLowLevel();
    }

    ElectronPlayer(int _vid, int _pid) :
        USB_PID(_pid), USB_VID(_vid)
    {
        lowLevelHandle = new ElectronLowLevel(_vid, _pid);
    }

    ~ElectronPlayer()
    {
        delete (lowLevelHandle);
    }


    struct RobotPose_t
    {
        float j1;
        float j2;
        float j3;
        float j4;
        float j5;
        float j6;
    };

    struct RobotTask
    {
        std::string _vedioPath;
        std::string _soundPath;
        vector<RobotPose_t> tasks;
        float _speedRatio;
        bool isPoseCirculate;
    };

    RobotPose_t currentPose{0, 0, 0, 0, 0, 0};
    vector<RobotPose_t> poseTasks;
    ElectronLowLevel* lowLevelHandle;
    AudioClip bulabula;

    bool Connect();
    bool Disconnect();

    void Play(RobotTask robotTask);
    void Stop();
    void SetPlaySpeed(float _ratio);
    void Relax();
    RobotPose_t GetPose();

    int USB_VID = 0x1001;
    int USB_PID = 0x8023;
    bool isConnected = false;


private:
    bool isVideoPlaying = false;
    bool isPosePlaying = false;
    float playSpeedRatio = 2.0f;
    float oneFrameTime = 60.0f;
    static void VideoTask(ElectronPlayer* _obj, const std::string &_filePath, float _speedRatio, vector<RobotPose_t> tasks, bool isPoseCirculate);
};


#endif