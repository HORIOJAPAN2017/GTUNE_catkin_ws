#include <iostream>
#include <ros/ros.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/opencv.hpp>
#include <fstream>
#include "sensor_msgs/LaserScan.h"



using namespace std;
using namespace cv;


#define IMG_RAW_WIDTH 1920
#define IMG_RAW_HEIGHT 1080
#define IMG_WIDTH 640
#define IMG_HEIGHT 480
#define PI 3.141592

//image parameter
int IMGWIDTH, IMGHEIGHT, ORGWIDTH, ORGHEIGHT, MAPWIDTH, MAPHEIGHT, Start_x, Start_y;
int IMGFAR, IMGNEAR, IMGWIDTHR;
double Hvc, Hc, Angle, Dvc, f;
//urg
double urg_radian[720];
int urg_pix_x[720];
int urg_pix_y[720];
int urg_size = 0;

float front_urg_data[640];
int front_data_size;

//encoder
int enc_x = 0; 
int enc_y = 0;
double enc_radian = 0;//0~3.14
int Grid_x = 0;
int Grid_y = 0;

image_transport::Publisher image_pub;
sensor_msgs::ImagePtr msg; 

VideoCapture cap;
Mat affine;  

void UrgLine(const Mat &img_roi, const int CUTWIDTH, const int urg_pix_x, const int urg_pix_y, const double urg_radian){
	if (urg_pix_x > CUTWIDTH / 2){
		if ((CUTWIDTH - urg_pix_x) / cos(urg_radian) <= urg_pix_y / sin(urg_radian)){
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(CUTWIDTH, urg_pix_y - int((CUTWIDTH - urg_pix_x)*tan(urg_radian))), Scalar(0, 0, 0), 4, 4);
		}
		else{
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(urg_pix_x + int(urg_pix_y  * tan((CV_PI / 2) - urg_radian)), 0), Scalar(0, 0, 0), 4, 4);

		}
	}
	else if (urg_pix_x < CUTWIDTH / 2){
		if ((CUTWIDTH - urg_pix_x) / (-cos(urg_radian)) <= urg_pix_y / sin(urg_radian)){
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(1, urg_pix_y - int((0 - urg_pix_x)*(tan(urg_radian)))), Scalar(0, 0, 0), 4, 4);
		}
		else{
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(urg_pix_x + int(urg_pix_y  * (tan((CV_PI / 2) - urg_radian))), 0), Scalar(0, 0, 0), 4, 4);

		}
	}
	else if (urg_pix_x == CUTWIDTH / 2&&urg_pix_y>0&&urg_pix_y<120){
		line(img_roi, Point(urg_pix_x, urg_pix_y), Point(urg_pix_x, 0), Scalar(0, 0, 0), 4, 4);
	}
}


void TopViewKami(int point[4][2], const Mat &capImage, const Mat &grayImage, const Mat &topImageGray, const Mat &topImage, const int IMGWIDTH, const int IMGHEIGHT, const double Hvc, const double Hc, const double Angle,const double Dvc, const double f){
	//double Hvc = 3.85;
	//double Hc = 0.603;
	//double Angle=40;
	//double Dvc = 3;
	//double f = 289;
	double theta = (Angle / 180.0) * 3.14;
	double fp = f;
	double s = sin(theta);
	double c = cos(theta);
	int cx = IMGWIDTH / 2;
	int cy = IMGHEIGHT / 2;
	int cxp = IMGWIDTH / 2;
	int cyp = IMGHEIGHT / 2 ;

	for (int y = 0; y < topImage.rows; y++) {
		for (int x = 0; x < topImage.cols; x++) {
			int xOrg = x - cx;
			int yOrg = -y + cy;



			int newX = fp / Hvc * Hc * xOrg / (f * s - yOrg * c);
			int newY = fp / Hvc * (Hc * (f * c + yOrg * s) / (f * s - yOrg * c) - Dvc);

			newX = newX + cx;
			newY = -newY + cyp;

			if (x == 0 && y == 0) { //printf(" x = %d , y = %d \n", newX, newY);
				point[0][0] = newX;
				point[0][1] = newY;
			}
			if (x == topImage.cols - 1 && y == 0) { //printf(" x = %d , y = %d \n", newX, newY);
				point[1][0] = newX;
				point[1][1] = newY;
			}
			if (x == 0 && y == topImage.rows - 1) { //printf(" x = %d , y = %d \n", newX, newY);
				point[2][0] = newX;
				point[2][1] = newY;
			}
			if (x == topImage.cols - 1 && y == topImage.rows - 1) { //printf(" x = %d , y = %d \n", newX, newY);
				point[3][0] = newX;
				point[3][1] = newY;
			}

			if (newX < 0 || topImage.cols - 1 < newX || newY < 0 || topImage.rows - 1 < newY) {
				continue;
			}

			topImageGray.data[newY * topImageGray.cols + newX] = grayImage.data[y * grayImage.cols + x];

			topImage.data[(newY * topImage.cols + newX) * topImage.channels()] = /*undistort*/capImage.data[(y * topImage.cols + x) * topImage.channels()];
			topImage.data[(newY * topImage.cols + newX) * topImage.channels() + 1] = /*undistort*/capImage.data[(y * topImage.cols + x) * topImage.channels() + 1];
			topImage.data[(newY * topImage.cols + newX) * topImage.channels() + 2] = /*undistort*/capImage.data[(y * topImage.cols + x) * topImage.channels() + 2];
		}
	}

}
void Resize(Mat *src, Mat *dst) {

	vector<Point2f> src_p, dst_p;
	src_p.push_back(Point2f(0, 0));
	src_p.push_back(Point2f((*src).cols, 0));
	src_p.push_back(Point2f((*src).cols, (*src).rows));

	dst_p.push_back(Point2f(0, 0));
	dst_p.push_back(Point2f((*dst).cols, 0));
	dst_p.push_back(Point2f((*dst).cols, (*dst).rows));

	Mat affine2 = getAffineTransform(src_p, dst_p);
	warpAffine(*src, *dst, affine2, (*dst).size(), CV_INTER_LINEAR);

	//imshow("func", *dst);
}





//////////
//
//明日確認することーーーーーーーーーーーーーーーーーーーーーーーーー
//
/////////

void frontCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
  int i = 0;

  float resolution = 0.25;//  本来は0.25
  float start_radian = 170.0;

  for(std::vector<float>::const_iterator it = scan->ranges.begin(); it != scan->ranges.end();++it){
    front_urg_data[i] = *it;
    if(front_urg_data[i] > 7)
      front_urg_data[i] = -1;
    i++;
 }
  front_data_size = i;
  urg_size = 0;
  for(int j = 0;j<front_data_size;j++){
    //urg_radian[720];
    //urg_pix_x[720];
    //urg_pix_y[720];
    if((front_urg_data[j] > 0.05)){
      urg_radian[urg_size] = (-j * resolution + start_radian)/180*PI;
      urg_pix_x[urg_size] = front_urg_data[j] * cos(urg_radian[urg_size]) * 20;
      urg_pix_y[urg_size] = front_urg_data[j] * sin(urg_radian[urg_size]) * 20;
      urg_size++;
    }
  }

  int point[4][2];

	Size org_size(ORGWIDTH, ORGHEIGHT);
	Mat orgImage(Size(ORGWIDTH, ORGHEIGHT), CV_8UC3, Scalar::all(0));
	cap.set(CV_CAP_PROP_FRAME_WIDTH, org_size.width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, org_size.height);

	Mat clbImage(Size(ORGWIDTH, ORGHEIGHT), CV_8UC3);
	Mat capImage(Size(IMGWIDTH, IMGHEIGHT), CV_8UC3, Scalar::all(0));



  Mat camera = (Mat_<double>(3, 3) << 656.88224769690828, 0, 895.69654864028951,
    0, 651.32162740877448, 565.29102950436300, 0, 0, 1);
  Mat distCoeffs = (Mat_<double>(1, 5) << -0.0013803092701364925, -0.030357817044642622,
    0.0013587349848218459, -0.0021188966756608076, 0.0064651827514648000);

	vector<Point2f> src, dst;
	src.push_back(Point2f(0, 0));
	src.push_back(Point2f(orgImage.cols, 0));
	src.push_back(Point2f(orgImage.cols, orgImage.rows));

	dst.push_back(Point2f(0, 0));
	dst.push_back(Point2f(capImage.cols, 0));
	dst.push_back(Point2f(capImage.cols, capImage.rows));

	affine = getAffineTransform(src, dst);
	
  cap >> orgImage;//1920*1080
  //imshow("raw", orgImage);

  clbImage = orgImage.clone();
  undistort(orgImage, clbImage, camera, distCoeffs);

  warpAffine(clbImage, capImage, affine, capImage.size(), CV_INTER_LINEAR);
  //imshow("capImage", capImage);//640*480

  Mat grayImage(capImage.rows, capImage.cols, CV_8UC1);
  cvtColor(capImage, grayImage, COLOR_RGB2GRAY);
  
  Mat topImage(capImage.rows, capImage.cols, CV_8UC3);
  topImage.setTo(Scalar(0));

  Mat topImageGray(capImage.rows, capImage.cols, CV_8UC1);
  TopViewKami(point, capImage, grayImage, topImageGray, topImage, IMGWIDTH, IMGHEIGHT, Hvc, Hc, Angle, Dvc, f);
  line(topImage,Point(310,454),Point(330,454),Scalar(0,0,0),5,CV_AA);
  //imshow("Top Image", topImage);
  
  Mat cut(Size(342, point[2][1]), CV_8UC3);
  Mat roi(topImage, Rect(topImage.cols / 2 - 171, 0, 342, point[2][1]));
  roi.copyTo(cut);
  //imshow("cut", cut);
  
  int CutWidth = IMGWIDTHR / 5;
  int CutHeight = (IMGFAR - IMGNEAR) / 5;
  Mat resize(Size(CutWidth, CutHeight), CV_8UC3, Scalar::all(0));
  Resize(&cut, &resize);
  //imshow("resize", resize);
  ////////////////////////////

  for (int u = 0; u < urg_size; u++){
    UrgLine(resize, resize.cols, urg_pix_x[u] + resize.cols / 2, resize.rows - urg_pix_y[u] + 10 - 1, urg_radian[u]);
  }

  msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8",resize).toImageMsg();
  image_pub.publish(msg);

}


int main(int argc, char** argv)
{
//640,480,1920,1080,500,500(11/1)
	FILE *fi;
	fi = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/Img.csv", "r");
	if (fi != NULL){
		while (fscanf(fi, "%d,%d,%d,%d,%d,%d,%d,%d", &IMGWIDTH, &IMGHEIGHT, &ORGWIDTH, &ORGHEIGHT, &MAPWIDTH, &MAPHEIGHT, &Start_x, &Start_y) != EOF){
			printf("IMGWIDTH:%d IMGHEIGHT:%d ORGWIDTH:%d ORGHEIGHT:%d\nMAPWIDTH:%d MAPHEIGHT:%d Start_x:%d Start_y:%d\n", IMGWIDTH, IMGHEIGHT, ORGWIDTH, ORGHEIGHT, MAPWIDTH, MAPHEIGHT,Start_x, Start_y);
		}
		fclose(fi);
	}

	//600,15,600(11/1)
	FILE *fr;
	fr = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/Resize.csv", "r");
	if (fr != NULL){
		while (fscanf(fr, "%d,%d,%d",&IMGFAR,&IMGNEAR,&IMGWIDTHR) != EOF){
			printf("IMGFAR:%d IMGNEAR:%d IMGWIDTHR:%d\n", IMGFAR, IMGNEAR, IMGWIDTHR);
		}
		fclose(fr);
	}

	//3.85,0.62,40,3,289(11/1)
	FILE *ft;
	ft = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/Top.csv", "r");
	if (ft != NULL){
		while (fscanf(ft, "%lf,%lf,%lf,%lf,%lf", &Hvc, &Hc, &Angle, &Dvc, &f) != EOF){
			printf("Hvc:%lf Hc:%lf\nAngle:%lf Dvc:%lf f:%lf\n", Hvc, Hc, Angle, Dvc, f);
		}
		fclose(ft);
	}

	//double urg_radian[720] int urg_pix_x[720] int urg_pix_y[720]
	FILE *fu;
	fu = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/grid.csv", "r");
	if (fu != NULL){
		while (fscanf(fu, "%d,%d,%lf", &urg_pix_x[urg_size], &urg_pix_y[urg_size], &urg_radian[urg_size]) != EOF){
			printf("%d,%d,%lf\n", urg_pix_x[urg_size], urg_pix_y[urg_size], urg_radian[urg_size]);
			urg_size++;
		}
		fclose(fu);
	}


  ros::init(argc, argv, "img_topview_publisher");

  ros::NodeHandle nh_("~");

  image_transport::ImageTransport it(nh_);
  image_pub = it.advertise("image_top",1);
  ros::Subscriber front_sub = nh_.subscribe("/urg_front/scan",1,frontCallback); 

  cap.open(0);
  if (!cap.isOpened()) {
    ROS_ERROR("camera_is_not_opened!!");
    return 1;
  }


  ros::spin();








/*
  int point[4][2];
	Size org_size(ORGWIDTH, ORGHEIGHT);
	Mat orgImage(Size(ORGWIDTH, ORGHEIGHT), CV_8UC3, Scalar::all(0));
	cap.set(CV_CAP_PROP_FRAME_WIDTH, org_size.width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, org_size.height);

	Mat clbImage(Size(ORGWIDTH, ORGHEIGHT), CV_8UC3);
	Mat capImage(Size(IMGWIDTH, IMGHEIGHT), CV_8UC3, Scalar::all(0));

	vector<Point2f> src, dst;
	src.push_back(Point2f(0, 0));
	src.push_back(Point2f(orgImage.cols, 0));
	src.push_back(Point2f(orgImage.cols, orgImage.rows));

	dst.push_back(Point2f(0, 0));
	dst.push_back(Point2f(capImage.cols, 0));
	dst.push_back(Point2f(capImage.cols, capImage.rows));

	Mat affine = getAffineTransform(src, dst);
	

  while(ros::ok()){
    Mat camera = (Mat_<double>(3, 3) << 656.88224769690828, 0, 895.69654864028951,
      0, 651.32162740877448, 565.29102950436300, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(1, 5) << -0.0013803092701364925, -0.030357817044642622,
      0.0013587349848218459, -0.0021188966756608076, 0.0064651827514648000);


		cap >> orgImage;//1920*1080
		//imshow("raw", orgImage);

		clbImage = orgImage.clone();
		undistort(orgImage, clbImage, camera, distCoeffs);

		warpAffine(clbImage, capImage, affine, capImage.size(), CV_INTER_LINEAR);
		//imshow("capImage", capImage);//640*480

		Mat grayImage(capImage.rows, capImage.cols, CV_8UC1);
		cvtColor(capImage, grayImage, COLOR_RGB2GRAY);
		
		Mat topImage(capImage.rows, capImage.cols, CV_8UC3);
		topImage.setTo(Scalar(0));

		Mat topImageGray(capImage.rows, capImage.cols, CV_8UC1);
		TopViewKami(point, capImage, grayImage, topImageGray, topImage, IMGWIDTH, IMGHEIGHT, Hvc, Hc, Angle, Dvc, f);
    line(topImage,Point(310,454),Point(330,454),Scalar(0,0,0),5,CV_AA);
		//imshow("Top Image", topImage);
		
		Mat cut(Size(342, point[2][1]), CV_8UC3);
		Mat roi(topImage, Rect(topImage.cols / 2 - 171, 0, 342, point[2][1]));
		roi.copyTo(cut);
		//imshow("cut", cut);
		
		int CutWidth = IMGWIDTHR / 5;
		int CutHeight = (IMGFAR - IMGNEAR) / 5;
		Mat resize(Size(CutWidth, CutHeight), CV_8UC3, Scalar::all(0));
		Resize(&cut, &resize);
		//imshow("resize", resize);
		////////////////////////////

    for (int u = 0; u < urg_size; u++){
			UrgLine(resize, resize.cols, urg_pix_x[u] + resize.cols / 2, resize.rows - urg_pix_y[u] + 10 - 1, urg_radian[u]);
		}

    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8",topImage).toImageMsg();
    image_pub.publish(msg);

    ros::spinOnce();
    looprate.sleep();
  }*/

  return 0;
}


