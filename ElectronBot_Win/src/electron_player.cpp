#include "electron_player.h"
#include <opencv2/opencv.hpp>



bool ElectronPlayer::Connect()
{
    isConnected = lowLevelHandle->Connect();
    return isConnected;
}


bool ElectronPlayer::Disconnect()
{
    return lowLevelHandle->Disconnect();
}


void ElectronPlayer::Play(ElectronPlayer::RobotTask robotTask)
{
    cout << robotTask._vedioPath << endl;
    playSpeedRatio = robotTask._speedRatio;
    if (!robotTask._soundPath.empty()) {
        bulabula.load(robotTask._soundPath);//加载歌曲（相对路径）
        bulabula.play();//播放
    }
    VideoTask(this, robotTask._vedioPath, playSpeedRatio, robotTask.tasks, robotTask.isPoseCirculate);
}





void ElectronPlayer::Stop()
{
    isVideoPlaying = false;
    isPosePlaying = false;
}

void ElectronPlayer::Relax()
{
    lowLevelHandle->SetJointAngles(0, 0, 0, 0, 0, 0, false);
}

ElectronPlayer::RobotPose_t ElectronPlayer::GetPose()
{
    return ElectronPlayer::RobotPose_t();
}


void ElectronPlayer::SetPlaySpeed(float _ratio)
{
    if (_ratio > 0)
    {
        playSpeedRatio = _ratio;
    }
}


void ElectronPlayer::VideoTask(ElectronPlayer* _obj, 
    const std::string &_filePath, 
    float _speedRatio , 
    vector<RobotPose_t> tasks, 
    bool isPoseCirculate)
{
    
    // Picture type
    if (_filePath.find(".jpg") != std::string::npos ||
        _filePath.find(".png") != std::string::npos ||
        _filePath.find(".bmp") != std::string::npos)
    {
        _obj->lowLevelHandle->SetImageSrc(cv::imread(_filePath));
        for (int poseIndex = 0; poseIndex < tasks.size(); poseIndex++) {
            _obj->lowLevelHandle->SetJointAngles(
                tasks[poseIndex].j1,
                tasks[poseIndex].j2,
                tasks[poseIndex].j3,
                tasks[poseIndex].j4,
                tasks[poseIndex].j5,
                tasks[poseIndex].j6,
                true);
        }
        _obj->lowLevelHandle->Sync();
    }
    // Video type
    else if (_filePath.find(".mp4") != std::string::npos ||
        _filePath.find(".mov") != std::string::npos)
    {
        if (_obj->isConnected)
        {
            _obj->isVideoPlaying = true;
            cv::VideoCapture video(_filePath);
            cv::Mat frame;

            auto totalFrameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
            if (totalFrameCount < tasks.size()) {
                totalFrameCount = tasks.size();
            }
            long index = 1;
            long poseIndex = 0;
            time_t start, end;       // 计时
            start = clock();
            while (_obj->isVideoPlaying && index < totalFrameCount)
            {
                if (index < video.get(CV_CAP_PROP_FRAME_COUNT)) {
                    video >> frame;
                    index += (long)_speedRatio;
                    video.set(CV_CAP_PROP_POS_FRAMES, index);
                    _obj->lowLevelHandle->SetImageSrc(frame);
                }
                else {
                    if (isPoseCirculate) {
                        index = 1;
                    }
                }
                //std::cout << "poseIndex: " << poseIndex <<  std::endl;
                if (poseIndex < tasks.size()-1) {        
                    poseIndex += 1;
                    _obj->lowLevelHandle->SetJointAngles(
                        tasks[poseIndex].j1,
                        tasks[poseIndex].j2,
                        tasks[poseIndex].j3,
                        tasks[poseIndex].j4,
                        tasks[poseIndex].j5,
                        tasks[poseIndex].j6,
                        true);
                    
                }
                else {
                    if (isPoseCirculate) {
                        poseIndex = 0;
                    }
                    else {
                        _obj->lowLevelHandle->SetJointAngles(
                            tasks[tasks.size() - 1].j1,
                            tasks[tasks.size() - 1].j2,
                            tasks[tasks.size() - 1].j3,
                            tasks[tasks.size() - 1].j4,
                            tasks[tasks.size() - 1].j5,
                            tasks[tasks.size() - 1].j6,
                            true);
                    }
                }

               
                _obj->lowLevelHandle->Sync();
                
            }
            tasks.clear();
            _obj->isVideoPlaying = false;
            end = clock();
            std::cout << "DBSCAN time: " << (end - start) / totalFrameCount << " ms" << std::endl;
        }
    }
    
}


