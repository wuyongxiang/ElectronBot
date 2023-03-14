#ifndef ELECTRONBOTSDK_CAPTUREDLIB_H
#define ELECTRONBOTSDK_CAPTUREDLIB_H
#include "electron_controller.h"
#include <dlib\opencv.h>
#include <opencv2\opencv.hpp>
#include <dlib\image_processing\frontal_face_detector.h>
#include <dlib\image_processing\render_face_detections.h>
#include <dlib\image_processing.h>
#include <dlib\gui_widgets.h>
#include <iostream>
#include <vector>
#include <cmath>
#include<time.h>

using namespace std;
using namespace dlib;
using namespace cv;

class __declspec(dllexport) CaptureDlib
{
public:
    CaptureDlib()
    {

    }

    ~CaptureDlib()
    {

    }
    //画坐标轴
    Mat Eye_Waveform = Mat::zeros(900, 900, CV_8UC3);    //用于记录眨眼的波形图
    Point p1 = Point(10, 0);
    Point p2 = Point(10, 900);
    Point p3 = Point(0, 890);
    Point p4 = Point(900, 890);
    Scalar line_color = Scalar(255, 255, 255);


    //存储眼睛的上一个点的坐标
    int eye_previous_x = 10;			//原点横坐标
    int eye_previous_y = 890;		//原点纵坐标
    int eye_now_x = 1;
    int eye_now_y = 1;


    //存储眨眼的次数
    unsigned int count_blink = 0;			//眨眼次数


    //每次眨眼EAR都要经历从  大于0.2-小于0.2-大于0.2 的过程
    float blink_EAR_before = 0.0;		//眨眼前
    float blink_EAR_now = 0.2;			//眨眼中
    float blink_EAR_after = 0.0;			//眨眼后

    int Init_CaptureDlib(ElectronController* controller);
    int Start_CaptureDlibHandler(ElectronController* controller);


private:


};

#endif