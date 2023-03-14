#include "CaptureDlib.h"

int CaptureDlib::Init_CaptureDlib(ElectronController* controller)
{	
	cv::line(Eye_Waveform, p1, p2, line_color, 1, LINE_AA);
	cv::line(Eye_Waveform, p3, p4, line_color, 1, LINE_AA);
	try {
		VideoCapture cap(0);
		if (!cap.isOpened()) {   //������ͷ
			printf("Unable to connect a camera");
			return 1;
		}
		frontal_face_detector detector = get_frontal_face_detector();

		shape_predictor pos_modle;

		//�����õ���shape_predictor_68_face_landmarks/shape_predictor_68_face_landmarks.dat  �ļ��Ѿ��ŵ�������ϱ�������
		deserialize("shape_predictor_68_face_landmarks.dat") >> pos_modle;
		while (waitKey(30) != 27) {
			Mat temp;
			cap >> temp;

			//��ͼ��ת��Ϊdlib�е�BGR����ʽ
			cv_image<bgr_pixel> cimg(temp);

			std::vector<dlib::rectangle> faces = detector(cimg);
			std::vector<full_object_detection> shapes;
			unsigned int faceNumber = faces.size();   //��ȡ�����������ĸ����������ĸ���
			for (unsigned int i = 0; i < faceNumber; i++) {
				shapes.push_back(pos_modle(cimg, faces[i]));
			}
			if (!shapes.empty()) {
				int faceNumber = shapes.size();
				/*
				for (int j = 0; j < faceNumber; j++)
				{
					for (int i = 0; i < 68; i++)
					{
						//����������ֵ�ĵ�
						cv::circle(temp, cvPoint(shapes[j].part(i).x(), shapes[j].part(i).y()), 1, cv::Scalar(0, 0, 255), -1);
						//����˵�� ͼ�� Բ�� ������� ��ɫ �ߵ�����
						//��ʾ����
						cv::putText(temp, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255));

					}
				}
				*/
				

				//����

					//��36������ 
				unsigned int x_36 = shapes[0].part(36).x();
				unsigned int y_36 = shapes[0].part(36).y();

				//��37������
				unsigned int x_37 = shapes[0].part(37).x();
				unsigned int y_37 = shapes[0].part(37).y();

				//��38������
				unsigned int x_38 = shapes[0].part(38).x();
				unsigned int y_38 = shapes[0].part(38).y();

				//��39������
				unsigned int x_39 = shapes[0].part(39).x();
				unsigned int y_39 = shapes[0].part(39).y();

				//��40������
				unsigned int x_40 = shapes[0].part(40).x();
				unsigned int y_40 = shapes[0].part(40).y();

				//��41������
				unsigned int x_41 = shapes[0].part(41).x();
				unsigned int y_41 = shapes[0].part(41).y();

				/*
				//�����۵�����������,Ϊ��֤���۾��ϵ�ȡ��û��ȡ��
				Point pts[1][6];
				pts[0][0] = Point(x_36, y_36);
				pts[0][1] = Point(x_37, y_37);
				pts[0][2] = Point(x_38, y_38);
				pts[0][3] = Point(x_39, y_39);
				pts[0][4] = Point(x_40, y_40);
				pts[0][5] = Point(x_41, y_41);

				const Point* ppts[] = { pts[0] };
				int npt[] = { 6 };
				Scalar eye_color = Scalar(0, 0, 255);
				fillPoly(temp, ppts, npt, 1, eye_color, LINE_AA);  //���۾��Ϲ��ն����

				*/



				int height_left_eye1 = y_41 - y_37;			//37��41���������
				//cout << "���۸߶�1\t" << height_left_eye1 << endl;
				int height_left_eye2 = y_40 - y_38;			//38��40���������
				//cout << "���۸߶�2\t" << height_left_eye2 << endl;
				float height_left_eye = (height_left_eye1 + height_left_eye2) / 2;		//�۾����¾���
				//cout << "���۸߶�\t" << height_left_eye << endl;
				int length_left_eye = x_39 - x_36;
				//cout << "���۳���\t" << length_left_eye << endl;
				if (height_left_eye == 0)  //���۾��պϵ�ʱ�򣬾�����ܼ��Ϊ0����߱ȳ���
					height_left_eye = 1;

				float EAR_left_eye;			//�۾���߱�
				EAR_left_eye = height_left_eye / length_left_eye;

				/*
				//����Ļ����ʾ�۾��ĸ߶ȼ���߱�

				cout << "���ۿ�߱�" << EAR_left_eye << endl;

				��ʾheight_left_eye��length_left_eye�Լ�ERA_left_eye

				��hight_left_eye��float����ת�����ַ�������
				char height_left_eye_text[30];
				char length_left_eye_text[30];
				char ERA_left_eye_text[30];

				_gcvt_s(height_left_eye_text, height_left_eye, 10);   //��hight_left_eye��float����ת�����ַ�������
				_gcvt_s(length_left_eye_text, length_left_eye,10);
				_gcvt_s(ERA_left_eye_text, EAR_left_eye, 10);

				putText(temp, height_left_eye_text, Point(10, 100), FONT_HERSHEY_COMPLEX, 1.0, Scalar(12, 255, 200), 1, LINE_AA);
				putText(temp,height_left_eye_text, Point(10, 200), FONT_HERSHEY_COMPLEX, 1.0, Scalar(12, 255, 200), 1, LINE_AA);
				putText(temp, height_left_eye_text, Point(10, 300), FONT_HERSHEY_COMPLEX, 1.0, Scalar(12, 255, 200), 1, LINE_AA);
				*/

				//����

				//��42������ 
				unsigned int x_42 = shapes[0].part(42).x();
				unsigned int y_42 = shapes[0].part(42).y();

				//��37������
				unsigned int x_43 = shapes[0].part(43).x();
				unsigned int y_43 = shapes[0].part(43).y();

				//��38������
				unsigned int x_44 = shapes[0].part(44).x();
				unsigned int y_44 = shapes[0].part(44).y();

				//��39������
				unsigned int x_45 = shapes[0].part(45).x();
				unsigned int y_45 = shapes[0].part(45).y();

				//��40������
				unsigned int x_46 = shapes[0].part(46).x();
				unsigned int y_46 = shapes[0].part(46).y();

				//��41������
				unsigned int x_47 = shapes[0].part(47).x();
				unsigned int y_47 = shapes[0].part(47).y();

				unsigned int height_right_eye1 = y_47 - y_43;			//37��41���������
				unsigned int height_right_eye2 = y_46 - y_44;			//38��40���������
				float height_right_eye = (height_right_eye1 + height_right_eye2) / 2;		//�۾����¾���
				if (height_right_eye == 0)  //���۾��պϵ�ʱ�򣬾�����ܼ��Ϊ0����߱ȳ���
					height_right_eye = 1;

				unsigned int length_right_eye = x_45 - x_42;

				float EAR_right_eye;			//�۾���߱�
				EAR_right_eye = height_right_eye / length_right_eye;

				//ȡ��ֻ�۾���ƽ����߱���Ϊ�۾��Ŀ�߱�
				float EAR_eyes = (EAR_left_eye + EAR_right_eye) / 2;

				//cout << "�۾��Ŀ�߱�Ϊ" << EAR_eyes << endl;

				/*
				eye_now_x = eye_now_x + 1;			//�����꣨ÿ10��������һ���㣩
				eye_now_y = 900 - (EAR_eyes * 900);		//������
				Point poi1 = Point(eye_previous_x, eye_previous_y);		//��һ����
				Point poi2 = Point(eye_now_x, eye_now_y);				//���ڵĵ�
				Scalar eyes_color = Scalar(0, 255, 0);
				cv::line(Eye_Waveform, poi1, poi2, eyes_color, 1, LINE_AA);			//����
				eye_previous_x = eye_now_x;
				eye_previous_y = eye_now_y;
				namedWindow("Blink waveform figure", WINDOW_AUTOSIZE);
				*/
				//���۾��Ĳ���ͼ
				
				bool isBlink = false;
				//����գ�۴���
				if (blink_EAR_before < EAR_eyes) {
					blink_EAR_before = EAR_eyes;
				}
				if (blink_EAR_now > EAR_eyes) {
					blink_EAR_now = EAR_eyes;
				}
				if (blink_EAR_after < EAR_eyes) {
					blink_EAR_after = EAR_eyes;
				}
				if (blink_EAR_before > 0.2 && blink_EAR_now <= 0.2 && blink_EAR_after > 0.2) {
					count_blink = count_blink + 1;
					isBlink = true;
					blink_EAR_before = 0.0;
					blink_EAR_now = 0.2;
					blink_EAR_after = 0.0;
				}

				//��ʾheight_left_eye��length_left_eye�Լ�ERA_left_eye

				//��hight_left_eye��float����ת�����ַ�������
				//char count_blink_text[30];

				//_gcvt_s(count_blink_text, count_blink, 10);   //��hight_left_eye��float����ת�����ַ�������

				//putText(temp, count_blink_text, Point(10, 100), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 0, 255), 1, LINE_AA);


				unsigned int x_21 = shapes[0].part(21).x();
				unsigned int y_21 = shapes[0].part(21).y();
				unsigned int x_22 = shapes[0].part(22).x();
				unsigned int y_22 = shapes[0].part(22).y();
				unsigned int x_top = (x_21 + x_22) / 2;
				unsigned int y_top = (y_21 + y_22) / 2;

				unsigned int x_nose = shapes[0].part(30).x();
				unsigned int y_nose = shapes[0].part(30).y();

				unsigned int x_left = shapes[0].part(1).x();
				unsigned int y_left = shapes[0].part(1).y();

				unsigned int x_right = shapes[0].part(15).x();
				unsigned int y_right = shapes[0].part(15).y();

				unsigned int x_bottom = shapes[0].part(8).x();
				unsigned int y_bottom = shapes[0].part(8).y();


				float count_y_joint_f = (y_nose - y_top) / ((y_bottom - y_nose)*1.0f);
				int count_y_joint = (count_y_joint_f - 0.6f) * 5 * 15;
				if (count_y_joint > 15) {
					count_y_joint = 15;
				}
				if (count_y_joint < -15) {
					count_y_joint = -15;
				}
				//char count_y_joint_c[30];
				//_gcvt_s(count_y_joint_c, count_y_joint, 10);   //��hight_left_eye��float����ת�����ַ�������
				//putText(temp, count_y_joint_c, Point(10, 150), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 0, 255), 1, LINE_AA);

				float count_x_joint_f = (x_nose - x_left) / ((x_right - x_nose) * 1.0f);//�м䣺1 ���� 0.1  ����6
				int count_x_joint = 0;
				if (count_x_joint_f < 1) {
					count_x_joint = (1 - count_x_joint_f)*0.8 * -90;
				}else if(count_x_joint_f > 1) {
					count_x_joint = (count_x_joint_f) /9  * 90;
				}
				
				if (count_x_joint > 60) {
					count_x_joint = 60;
				}
				if (count_x_joint < -60) {
					count_x_joint = -60;
				}

				//char count_x_joint_fc[30];
				//_gcvt_s(count_x_joint_fc, count_x_joint_f, 10);   //��hight_left_eye��float����ת�����ַ�������
				//putText(temp, count_x_joint_fc, Point(10, 200), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 0, 255), 1, LINE_AA);
				
				controller->RunCaptureTask(isBlink, count_x_joint, count_y_joint);
			}

			//Display it all on the screen  չʾÿһ֡��ͼƬ
			cv::imshow("Dlib���", temp);
			//cv::imshow("Blink waveform figure", Eye_Waveform);


			/*
			*
			clock_t start = clock();
			clock_t finish = clock();
			double consumeTime = (double)(finish - start);//ע��ת��Ϊdouble��λ��
			if (count_blink >= 25) {
				if (consumeTime / 1000 < 60) {
					cout << "����ƣ�ͣ�����Ϣ����" << endl;
					count_blink = 0;
					return 0;
				}
			}
				*/
				//��ʱһ���ӣ�60�룩


		}
		

	}
	catch (serialization_error& e) {
		cout << "You need dlib��s default face landmarking file to run this example." << endl;
		cout << endl << e.what() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;

	}
}
