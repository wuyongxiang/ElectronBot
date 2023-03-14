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
    //��������
    Mat Eye_Waveform = Mat::zeros(900, 900, CV_8UC3);    //���ڼ�¼գ�۵Ĳ���ͼ
    Point p1 = Point(10, 0);
    Point p2 = Point(10, 900);
    Point p3 = Point(0, 890);
    Point p4 = Point(900, 890);
    Scalar line_color = Scalar(255, 255, 255);


    //�洢�۾�����һ���������
    int eye_previous_x = 10;			//ԭ�������
    int eye_previous_y = 890;		//ԭ��������
    int eye_now_x = 1;
    int eye_now_y = 1;


    //�洢գ�۵Ĵ���
    unsigned int count_blink = 0;			//գ�۴���


    //ÿ��գ��EAR��Ҫ������  ����0.2-С��0.2-����0.2 �Ĺ���
    float blink_EAR_before = 0.0;		//գ��ǰ
    float blink_EAR_now = 0.2;			//գ����
    float blink_EAR_after = 0.0;			//գ�ۺ�

    int Init_CaptureDlib(ElectronController* controller);
    int Start_CaptureDlibHandler(ElectronController* controller);


private:


};

#endif