#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "test_opencv/coordinate.h"

#define CURSORKEYTOP 2490368
#define CURSORKEYBOTTOM 2621440
#define CURSORKEYRIGHT 2555904
#define CURSORKEYLEFT 2424832

#define IMGWIDTH 640
#define IMGHEIGHT 480
#define ORGWIDTH 1920
#define ORGHEIGHT 1080
#define MAPWIDTH 500
#define MAPHEIGHT 500
#define Start_x 214
#define Start_y 320

#define PI 3.141592

using namespace std;
using namespace cv;

#define MAPSIZE 500

static int flag = 0;
static int gX = 0;
static int gY = 0;
static Mat Map(Size(1500, 1500), CV_8UC3, Scalar::all(0));


cv::Mat image;

int now_WIDTH=250;
int now_HEIGHT=500;
double enc_radian = 1.570796;//0~3.14

//grobal
int error_of_x = 5;
int error_of_y = 5;
//


int sgn(int a) {
	if (a >= 0)	return 0;
	else return -1;
}

void Calcgrid(int wx, int wy, int *gx, int *gy){
	*gx = wx / MAPSIZE;
	*gy = wy / MAPSIZE;
	if (*gx < 0) *gx = *gx - 1;
	if (*gy < 0) *gy = *gy - 1;
	
	if (*gx == 0) *gx = sgn(wx);
	if (*gy == 0) *gy = sgn(wy);

	
}

void Calclocal(int wx, int wy, int *lx, int *ly){
	int x, y;
	x = wx % MAPSIZE;
	y = wy % MAPSIZE;

	if(sgn(x) >= 0)	*lx = MAPSIZE + x;
	else *lx = 2 * MAPSIZE + x;

	if( wy >= 0)	*ly = MAPSIZE + y;
	else *ly = 2 * MAPSIZE + y;

	//printf("lx = %d, ly = %d \n", *lx, *ly);
}

void MapResize(Mat *src, Mat *dst) {

	vector<Point2f> src_p, dst_p;
	src_p.push_back(Point2f(0, 0));
	src_p.push_back(Point2f((*src).cols, 0));
	src_p.push_back(Point2f((*src).cols, (*src).rows));

	dst_p.push_back(Point2f(0, 0));
	dst_p.push_back(Point2f((*dst).cols, 0));
	dst_p.push_back(Point2f((*dst).cols, (*dst).rows));

	Mat affine2 = getAffineTransform(src_p, dst_p);
	warpAffine(*src, *dst, affine2, (*dst).size(), CV_INTER_LINEAR);

}

void AreaSearch(const int wx, const int wy, const float rad) {

  cv::imshow("image", image);
  cv::moveWindow("image",100,100);
  cv::waitKey(1);

	int gx, gy;
	Calcgrid(wx, wy, &gx, &gy);
	printf("gx = %d, gy = %d \n", gx, gy);

	if (flag == 0 || gX != gx || gY != gy) {
		char str[64];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				sprintf(str, "/home/user/catkin_ws/src/test_opencv/Image/Grid2/map_%d_%d.png", (gx - 1) + j, (gy - 1) + i);

				Mat piece(MAPSIZE, MAPSIZE, CV_8UC1, Scalar::all(0));
				piece = imread(str, CV_LOAD_IMAGE_COLOR);
				if (piece.empty()) {
					piece = imread("/home/user/catkin_ws/src/test_opencv/Image/map_sample/black.png", CV_LOAD_IMAGE_COLOR);
				}
				Mat roi(Map, Rect(MAPSIZE * j, MAPSIZE * i, MAPSIZE, MAPSIZE));
				piece.copyTo(roi);
			}
		}
		if(flag == 0)	flag = 1;
		gX = gx;
		gY = gy;
	}
	//imshow("map", Map);

	//Mat smallmap(Size(600, 600), CV_8UC3, Scalar::all(0));
	//MapResize(&Map, &smallmap);
	//imshow("smallmap", smallmap);

	int lx, ly;
	Calclocal(wx, wy, &lx, &ly);

	//Mat matching(Map, Rect(lx - (MAPSIZE / 2), ly - (MAPSIZE / 2), MAPSIZE, MAPSIZE));

	Mat roi(Map, Rect(lx - 100, ly - 100, 200, 200));
  Mat matching(Size(200, 200), CV_8UC3, Scalar::all(0));
  roi.copyTo(matching);





const float threshold = 0.4;
const float threshold2 = 0.5;







  int new_angle;
  int pixel_length = 5;
  int scan_angle = 5;
  int scan_time = 360 / scan_angle;

 int count_match_point = 0;

  float image_to_robot = 0.5;
  float pix_of_image_to_robot = image_to_robot * 100 / pixel_length;

  cv::Point2f center(image.cols * 0.5, image.rows*0.5);
  float angle = 0;
  float scale = 1.0;

  vector<int> pos_x(scan_time,0), pos_y(scan_time,0), TM_angle(scan_time,0);
  vector<double> TM(scan_time);
  cv::Mat result;
  cv::Point maxPt;

  vector<vector<float> > match_val_point;
  match_val_point.resize(4);



  for (int i = 0; i < scan_time; i++){
    cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);
    cv::Mat rotation_temp_image;
    cv::warpAffine(image, rotation_temp_image, affine_matrix, image.size());
    cv::matchTemplate(matching, rotation_temp_image, result, CV_TM_CCORR_NORMED);
    double max_Val;
    minMaxLoc(result, 0, &max_Val, 0, &maxPt);
    TM_angle[i] = angle;
    pos_x[i] = maxPt.x;
    pos_y[i] = maxPt.y;
    TM[i] = max_Val;

    //from encoder
    float E_x = 100,E_y = 100,E_angle = rad /PI*180;

    float angle_error = 20;
    for (int j = 0; j < result.rows; j++){
      for (int k = 0; k < result.cols; k++){
        if (result.at<float>(j, k) > threshold){
          if (E_angle - angle < angle_error && E_angle - angle > -angle_error){
            new_angle = angle + 90;
          }
          else{
            new_angle = angle - 270;
          }
          match_val_point[3].push_back(new_angle / 180 * M_PI);
          match_val_point[0].push_back(result.at<float>(j, k));
          int my_x = (k + image.cols * 0.5) + (image.rows * 0.5 + pix_of_image_to_robot) * sin(new_angle / 180 * M_PI);
          int my_y = (j + image.rows * 0.5) + (image.rows * 0.5 + pix_of_image_to_robot) * cos(new_angle / 180 * M_PI);
          if(result.at<float>(j,k) > threshold2 || (my_x - E_x) * (my_x - E_x) + (my_y - E_y) * (my_y - E_y) < 2 * 20 * 20){
            match_val_point[1].push_back(my_x);
            match_val_point[2].push_back(my_y);
            error_of_x = E_x - my_x;
            error_of_y = E_y - my_y;
          }
          else{
            if((my_x - E_x) * (my_x - E_x) + (my_y - E_y) * (my_y - E_y) < (error_of_x + 20) * (error_of_x + 20) + (error_of_y + 20) * (error_of_y + 20)){
              match_val_point[1].push_back(E_x - error_of_x);
              match_val_point[2].push_back(E_y - error_of_y);
            }
            else{
              match_val_point[1].push_back(0);
              match_val_point[2].push_back(0);
              match_val_point[0][count_match_point] = 0;
            }
          }
          count_match_point ++;
        }
      }
    }
    angle = angle + scan_angle;
  }
  ROS_ERROR("count=%d",count_match_point);
  if(count_match_point != 0){
    int max_add = 0;
    float max_Val;

    for(int E = 0; E < count_match_point; E++){
      if(max_Val < match_val_point[0][E]){
        max_Val = match_val_point[0][E];
        max_add = E;
      }
    }

    float E_my_pix_x;
    float E_my_pix_y;
    float E_my_angle;
    E_my_pix_x = match_val_point[1][max_add];
    E_my_pix_y = match_val_point[2][max_add];
    E_my_angle = match_val_point[3][max_add];

//    int check_add = 0;
//    float check_Val = TM[0];
//    int TM_i;
//    float max_pos_x, max_pos_y, max_angle;
//    for (TM_i = 0; TM_i < scan_time; TM_i++){
//      if (check_Val < TM[TM_i]){
//        check_Val = TM[TM_i];
//        check_add = TM_i;
//      }
//    }
//    max_pos_x = pos_x[check_add] + image.cols * 0.5;
//    max_pos_y = pos_y[check_add] + image.rows * 0.5;
//    max_angle = TM_angle[check_add];

//    float max_radian = max_angle / 180 * M_PI;
//    float my_pos_x, my_pos_y, my_angle, my_pix_x, my_pix_y;
//    my_pix_x = (max_pos_x + (image.rows * 0.5 + pix_of_image_to_robot) * sin(max_radian));
//    my_pix_y = (max_pos_y + (image.rows * 0.5 + pix_of_image_to_robot) * cos(max_radian));
//  my_pos_x = my_pix_x * pixel_length / 1000;
//  my_pos_y = my_pix_y * pixel_length / 1000;
//    my_angle = max_angle;


  //position of grid
    int X=wx-100,Y=wy-100;

    int grobal_x = X + E_my_pix_x;
    int grobal_y = Y + E_my_pix_y;

    int grid_ID_x = grobal_x / 500;
    int grid_ID_y = grobal_y / 500;
    if(grid_ID_x < 0){
      grid_ID_x = grid_ID_x - 1;
    }
    if(grid_ID_y < 0){
      grid_ID_y = grid_ID_y - 1;
    }

    int grid_pos_x = grobal_x - 500 * grid_ID_x;
    int grid_pos_y = grobal_y - 500 * grid_ID_y;

    ROS_ERROR("pix_x_y=%f,%f,%f",E_my_pix_x,E_my_pix_y,E_my_angle);

  
        cv::circle(matching,cv::Point(E_my_pix_x,E_my_pix_y),5,cv::Scalar(255,255,0),2,8,0);
  }

  imshow("matching", matching);
  cv::moveWindow("matching",300,300);
  cv::waitKey(1);



  /*
  float deg = rad * 180 / PI - 90;
	Point2d ctr(lx, ly);
	Mat affine = getRotationMatrix2D(ctr, -deg, 1.0);
	Mat rotate; 
	Map.copyTo(rotate);
	warpAffine(Map, rotate, affine, rotate.size(), CV_INTER_LINEAR);
	//imshow("rotated", rotate);
	
	Mat area(rotate, Rect(lx - 8, ly - 159, 17, 160));
	//imshow("area", area);
	
	for (int i = 0; i < 10; i++) {
		
		int b_p = 0;

		for (int y = 0; y < area.rows/10; y++) {//srcImg.rows

			cv::Vec3b* ptr = area.ptr<cv::Vec3b>(y + (i * area.rows / 10));//i(y + (i * area.rows / 10))

			for (int x = 0; x < area.cols; x++) {
				cv::Vec3b bgr = ptr[x];
				if (bgr[0] == 0 && bgr[1] == 0 && bgr[2] == 0) b_p++;
			}

		}

		int wariai = b_p * 100 / ((area.rows/10) * area.cols);
		//printf("wariai%d = %d\nb_p = %d\n", i, wariai, b_p);
	}
	*/
	//printf("gx = %d, gy = %d \n", gx, gy);

	return;
}

void coordinateCallback(const test_opencv::coordinate &now_coordinate)
{
  now_WIDTH = now_coordinate.gridX * MAPWIDTH + now_coordinate.width;
  now_HEIGHT = now_coordinate.gridY * MAPHEIGHT + now_coordinate.height;
  enc_radian = now_coordinate.theta;

  ROS_ERROR("%d,%d,%f", now_WIDTH,now_HEIGHT,enc_radian);
}


void imageCallback(const sensor_msgs::ImageConstPtr& msg){
  try{
    image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;}
    catch(cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    AreaSearch(now_WIDTH, now_HEIGHT, enc_radian);//radian

    //cv::imshow("image", image);
    //cv::moveWindow("image",100,100);

}

int main(int argc, char** argv) {

  ros::init(argc,argv, "AroundSearch");
  ros::NodeHandle nh("~");
  ros::NodeHandle n;

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber image_sub = it.subscribe("/img_topview_publisher/image_top",1,imageCallback);
  ros::Subscriber sub = n.subscribe("now_pos_GL",1,coordinateCallback);
  ros::spin();

  return 0;
}
