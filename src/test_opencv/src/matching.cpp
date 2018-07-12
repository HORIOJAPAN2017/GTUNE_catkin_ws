#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int main(){
	//時間計測
	clock_t start, end;
	//時間計測開始
	start = clock(); 

	//画素あたりの長さ[cm]
	int pixel_length = 5;
	//スキャンパラメータ
	int scan_angle = 5;
	int scan_time = 360 / scan_angle;

	//閾値
	float threshold = 0.98;
	//閾値以上のマッチング点数をカウントする変数
	int count_match_point = 0;


	//地図画像を読み込む
	cv::Mat src_image = cv::imread("/home/user/catkin_ws/src/test_opencv/image/akigasemap.png");
	//cv::namedWindow("画像");
	//cv::imshow("原画像",src_image);
	//テンプレート画像を読み込む
	cv::Mat temp_image = cv::imread("/home/user/catkin_ws/src/test_opencv/image/akigasetemp.png");
	//cv::namedWindow("テンプレート画像");
	//cv::imshow("テンプレート画像",temp_image);
	//テンプレート画像の中心値を出す
	cv::Point2f center(temp_image.cols * 0.5, temp_image.rows*0.5);
	//回転パラメータ
	float angle = 0;
	float scale = 1.0;

	vector<int> pos_x(scan_time,0), pos_y(scan_time,0), TM_angle(scan_time,0);
	vector<double> TM(scan_time);
	cv::Mat result;
	cv::Point maxPt;

	//volの格納配列
	vector<vector<float> > match_val_point;
	match_val_point.resize(4);

	//各角度でマッチングする
	for (int i = 0; i < scan_time; i++){
		//2次元の回転行列を計算
		cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);
		//テンプレート画像を回転
		cv::Mat rotation_temp_image;
		cv::warpAffine(temp_image, rotation_temp_image, affine_matrix, temp_image.size());
		//cv::namedWindow("回転テンプレート画像");
		//cv::imshow("回転テンプレート画像", rotation_temp_image);
		//テンプレートマッチング
		cv::matchTemplate(src_image, rotation_temp_image, result, CV_TM_CCORR_NORMED);
		//cv::namedWindow("マッチング画像");
		//cv::imshow("マッチング画像", result);

		//Valが最大となるマッチング点の座標取得
		double max_Val;
		minMaxLoc(result, 0, &max_Val, 0, &maxPt);
		TM_angle[i] = angle;
		pos_x[i] = maxPt.x;
		pos_y[i] = maxPt.y;
		TM[i] = max_Val;

		//Valの格納
		for (int j = 0; j < result.rows; j++){
			for (int k = 0; k < result.cols; k++){
				if (result.at<float>(j, k) > threshold){
					match_val_point[0].push_back(result.at<float>(j, k));
					match_val_point[1].push_back(k);
					match_val_point[2].push_back(j);
					match_val_point[3].push_back(angle);
					count_match_point ++;
				}
			}
		}

		angle = angle + scan_angle;
	}
	
	//最も大きい値をとる時の中心画素座標を調べる
	int check_add = 0;
	float check_Val = TM[0];
	int TM_i;
	float max_pos_x, max_pos_y, max_angle;
	for (TM_i = 0; TM_i < scan_time; TM_i++){
		if (check_Val < TM[TM_i]){
			check_Val = TM[TM_i];
			check_add = TM_i;
		}
	}
	max_pos_x = pos_x[check_add] + temp_image.cols * 0.5;
	max_pos_y = pos_y[check_add] + temp_image.rows * 0.5;
	max_angle = TM_angle[check_add];

	//地図上の自己位置座標を計算する[m]
	float image_to_robot = 0.5;		//画像の端からロボットまでの距離
	float pix_of_image_to_robot = image_to_robot * 100 / pixel_length;		//ピクセルに変換
	float max_radian = max_angle / 180 * M_PI;
	float my_pos_x, my_pos_y, my_angle, my_pix_x, my_pix_y;
	my_pix_x = (max_pos_x + (temp_image.rows * 0.5 + pix_of_image_to_robot) * sin(max_radian));
	my_pix_y = (max_pos_y + (temp_image.rows * 0.5 + pix_of_image_to_robot) * cos(max_radian));
	my_pos_x = my_pix_x * pixel_length / 1000;
	my_pos_y = my_pix_y * pixel_length / 1000;
	my_angle = max_angle;











	//時間計測終了
	end = clock();
	double result_of_time = (end - start) ;
	//時間を表示する
	cout << result_of_time <<"μs"<< endl;

	cout << "threshold=" <<threshold << endl;
	cout << "閾値以上の点数" << count_match_point;
/*	for (int i = 0; i < count_match_point; i++){
		cout << "[val=" << match_val_point[0][i] << ",x=" << match_val_point[1][i] << ",y=" << match_val_point[2][i] << ",angle=" << match_val_point[3][i] << "°]" << endl;
	}*/
	cout <<"maxVal="<<check_Val<<endl;
	cout <<"自己位置画素座標[pixel]("<< my_pix_x <<","<< my_pix_y<<","<<my_angle<<"度)"<< endl;
	cout <<"地図上の自己位置[m]("<<my_pos_x<<","<<my_pos_y<<","<<my_angle<<"度)"<<endl;

	//マッチングを表示する
	cv::circle(src_image,cv::Point(max_pos_x,max_pos_y),temp_image.rows * 0.5,cv::Scalar(0,255,255),2,8,0);
	cv::namedWindow("マッチング表示画像");
	cv::imshow("マッチング表示画像",src_image);



	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
