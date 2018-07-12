#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "opencv2/opencv.hpp"
#include <fstream>
#include "test_opencv/coordinate.h"
#include "test_opencv/Nineaxes.h"




using namespace std;
using namespace cv;

#define IMGWIDTH 640
#define IMGHEIGHT 480
#define ORGWIDTH 1920
#define ORGHEIGHT 1080
#define MAPWIDTH 500
#define MAPHEIGHT 500
#define Start_x 214
#define Start_y 320

#define PI 3.141592
	int IMGFAR, IMGNEAR, IMGWIDTHR;

//map create
int Map_x; 
int Map_y;
double Map_r;
int Total_x;
int Total_y;
int hst_count = 0;
int cap_count = 1;

//encoder
int enc_x = 250; 
int enc_y = 500;
double enc_radian = 1.5745;//0~3.14
int Grid_x = 0;
int Grid_y = 0;

int MapHst[1000][2];
int OldGrid[2] = { 0, 0 };
char IMG[256], IMG2[256], IMG3[256];
cv::Mat originMap;
cv::Mat alphaMap;
cv::Mat grandMap;

void ArduinoCallback(const test_opencv::Nineaxes &arduino){
   enc_radian = (-arduino.EulerHeading + 450)/180*PI; 
   while(enc_radian > 2*PI || enc_radian < 0){
     if(enc_radian > 2*PI)
       enc_radian = enc_radian - 2 * PI;
     else if(enc_radian < 0)
       enc_radian = enc_radian + 2 * PI;
   }
}


void coordinateCallback(const test_opencv::coordinate &now_coordinate)
{
  Grid_x = now_coordinate.gridX;
  Grid_y = now_coordinate.gridY;
  enc_x = now_coordinate.width;
  enc_y = now_coordinate.height;
  //enc_radian = now_coordinate.theta;

}


template < typename T > std::string to_string(const T& n){
  std::ostringstream stm;
  stm <<n;
  return stm.str();
}

void Alpha(Mat &alpha_image){
	for (int y = 0; y < alpha_image.cols; y++) {
		for (int x = 0; x < alpha_image.rows; x++) {
			Vec4b px = alpha_image.at<cv::Vec4b>(x, y);
			if (px[0] + px[1] + px[2] == 0) {
				px[3] = 0;
				alpha_image.at<cv::Vec4b>(x, y) = px;
			}
		}
	}
}

void Grand(Mat &grand_image, Mat &alpha_image){
	for (int y = 0; y < alpha_image.cols; y++) {
		for (int x = 0; x < alpha_image.rows; x++) {
			Vec4b px = alpha_image.at<cv::Vec4b>(x, y);
			Vec4b gx = grand_image.at<cv::Vec4b>(x, y);
			if (px[3] == 0) {
				px[0] = gx[0];
				px[1] = gx[1];
				px[2] = gx[2];
				px[3] = 255;
				alpha_image.at<cv::Vec4b>(x, y) = px;
			}
		}

	}
}
void PinP(const Mat &mapImg, const Mat &smallImg, const double angle, const double tx, const double ty)
{

	Mat dstImg;
	mapImg.copyTo(dstImg);

	Point2d ctr(smallImg.cols / 2, smallImg.rows + 12);
	Mat mat = getRotationMatrix2D(ctr, angle, 1.0);

	mat.at<double>(0, 2) += tx;

	mat.at<double>(1, 2) += ty;

	warpAffine(smallImg, mapImg, mat, mapImg.size(), CV_INTER_LINEAR, BORDER_TRANSPARENT);

}

cv::Mat img;

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
  try{
    img = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;}
    catch(cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }

//		int CutWidth = IMGWIDTHR / 5;
//		int CutHeight = (IMGFAR - IMGNEAR) / 5;	
//		Mat resize(Size(CutWidth, CutHeight), CV_8UC3, Scalar::all(0));

/*    Map_x = enc_x + (MAPWIDTH / 2) - (img.cols / 2);
		Map_y = enc_y + MAPHEIGHT - img.rows - 10;
    Map_r = enc_radian * 180 / CV_PI;
*/
    Map_x = enc_x - img.cols / 2;
		Map_y = enc_y - img.rows - 10;
    Map_r = enc_radian * 180 / CV_PI - 90;

    ROS_ERROR("%d,%d,%d,%d,%f", Grid_x,Grid_y,enc_x,enc_y,enc_radian);
    string MapName;
    Mat alphaImage = Mat(img.size(), CV_8UC3);
		cvtColor(img, alphaImage, CV_RGB2RGBA);
		Alpha(alphaImage);


		if (OldGrid[0] != Grid_x || OldGrid[1] != Grid_y){
			sprintf(IMG3, "/home/user/catkin_ws/src/test_opencv/Image/Grid/Grid%d_%d.png", OldGrid[0], OldGrid[1]);
			imwrite(IMG3, grandMap);
			MapHst[hst_count][0] = OldGrid[0];
			MapHst[hst_count][1] = OldGrid[1];
			for (int m = 0; m <= hst_count; m++){
				if (MapHst[m][0] == Grid_x && MapHst[m][1] == Grid_y){
					MapName = "/home/user/catkin_ws/src/test_opencv/Image/Grid/Grid" + to_string(MapHst[m][0]) + "_" + to_string(MapHst[m][1]) + ".png";
					originMap = cv::imread(MapName, 1);
					//imshow("map", originMap);
					cvtColor(originMap, grandMap, CV_RGB2RGBA);
					alphaImage = Scalar::all(0);
					alphaMap = Scalar::all(0);
					break;
				}
				originMap = Scalar::all(0);
				cvtColor(originMap, grandMap, CV_RGB2RGBA);
				alphaImage = Scalar::all(0);
				alphaMap = Scalar::all(0);
			}
			hst_count++;
			OldGrid[0] = Grid_x;
			OldGrid[1] = Grid_y;
		}

		Alpha(alphaMap);
		PinP(alphaMap, alphaImage, Map_r, Map_x, Map_y);
		Grand(grandMap, alphaMap);
		grandMap = alphaMap.clone();

		imshow("grand", grandMap);
    waitKey(1);
		//imshow("alpha", alphaImage);
    moveWindow("grand",500,500);

    imshow("image", img);
    moveWindow("image",100,100);
 
		if (cap_count%5==0){
			//sprintf(IMG, "/home/user/catkin_ws/src/test_opencv/Image/Cap/Cap%03d_%d_%d.jpg", cap_count/5, Total_x, Total_y);
/*	  if(imwrite(IMG, capImage))
        printf("done_capImage\n");
      else
        printf("cannot_write_capImage");
*/
			sprintf(IMG2, "/home/user/catkin_ws/src/test_opencv/Image/Top/Top%03d_%d_%d.png", cap_count/5, Total_x, Total_y);
			if(imwrite(IMG2, img))
        printf("done_topImage\n");
      else
        printf("cannot_write_topImage");


			sprintf(IMG3, "/home/user/catkin_ws/src/test_opencv/Image/Grid/Grid%d_%d.png", Grid_x, Grid_y);
			if(imwrite(IMG3, alphaMap))
        printf("done_alphaMap");
      else
        printf("cannot_write_alphaMap");
		}

		Total_x = enc_x + MAPWIDTH * Grid_x;
		Total_y = enc_y + MAPHEIGHT * Grid_y;
		printf("COUNT:%d_enc:(%d,%d)_Map:(%d,%d,%d)_Grid:(%d,%d)_Global:(%d,%d)\r", cap_count, enc_x, enc_y, Map_x, Map_y, Map_r, Grid_x, Grid_y, Total_x, Total_y);
		cap_count++;
    waitKey(1);
}

int main(int argc, char** argv)
{
  ros::init(argc,argv, "img_topview_subscriber");
  ros::NodeHandle nh("~");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("now_pos_GL",1,coordinateCallback);
  ros::Subscriber sub_ard=n.subscribe("arduino",1,ArduinoCallback);

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber image_sub = it.subscribe("/img_topview_publisher/image_top",1,imageCallback);

  originMap = Mat(Size(MAPWIDTH, MAPHEIGHT), CV_8UC3, Scalar(0, 0, 0));
  alphaMap = Mat(Size(MAPWIDTH, MAPHEIGHT), CV_8UC3);
  grandMap = Mat(Size(MAPWIDTH, MAPHEIGHT), CV_8UC3, Scalar(0, 0, 0));


  cvtColor(originMap, alphaMap, CV_RGB2RGBA);
  cvtColor(originMap, grandMap, CV_RGB2RGBA);


  ros::spin();

  return 0;
}

