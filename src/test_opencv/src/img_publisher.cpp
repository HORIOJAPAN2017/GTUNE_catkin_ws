#include <iostream>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include "test_opencv/key.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#define IMG_RAW_WIDTH 1920
#define IMG_RAW_HEIGHT 1080
#define IMG_WIDTH 640
#define IMG_HEIGHT 480

using namespace std;
using namespace cv;

void TopView(const Mat &capImage, const Mat &topImage){
  double Hvc = 3.0;
  double Hc = 0.603;
  double theta = (25.0 / 180.0) * 3.1415;
  double Dvc = Hc * tan(theta);
  double f = 640;
  double s = sin(theta);
  double c = cos(theta);
  int cx = IMG_WIDTH / 2;
  int cy = IMG_HEIGHT / 2;

  for (int y = 0;y < topImage.rows; y++){
    for(int x = 0;x < topImage.cols; x++){
      int xOrg = x - cx;
      int yOrg = -y + cy;

      double oldX = 0.5 + (Hvc/Hc)*c*(s/c - (yOrg*Hvc*s - f*Hc*c + f*Dvc*s)/(f*Hc*s + Hvc*yOrg*c + f*Dvc*c))*xOrg;
      double oldY = 0.5 + f*((yOrg*Hvc*s - f*Hc*c + f*Dvc*s) / (f*Hc*s + Hvc*yOrg*c+ f*Dvc*c));

      oldX = oldX + cx;
      oldY = -oldY + cy;

      if(oldX < 0|| topImage.cols - 1 < oldX || oldY < 0 || topImage.rows - 1 < oldY){
        continue;
      }

      if((int)oldX + 1 >= topImage.cols || (int)oldY + 1 >= topImage.rows){
        topImage.data[(y*topImage.cols + x)*topImage.channels() + 0] = capImage.data[((int)oldY*topImage.cols + (int)oldX)*topImage.channels() + 0];
        topImage.data[(y*topImage.cols + x)*topImage.channels() + 1] = capImage.data[((int)oldY*topImage.cols + (int)oldX)*topImage.channels() + 1];
        topImage.data[(y*topImage.cols + x)*topImage.channels() + 2] = capImage.data[((int)oldY*topImage.cols + (int)oldX)*topImage.channels() + 2];
        continue;
      }

      for(int i = 0; i < topImage.channels();i++){
        uchar f11 = capImage.data[(((int)oldY + 0)*topImage.cols + (int)oldX + 0)*topImage.channels() + i];
        uchar f12 = capImage.data[(((int)oldY + 1)*topImage.cols + (int)oldX + 0)*topImage.channels() + i];
        uchar f21 = capImage.data[(((int)oldY + 0)*topImage.cols + (int)oldX + 1)*topImage.channels() + i];
        uchar f22 = capImage.data[(((int)oldY + 1)*topImage.cols + (int)oldX + 1)*topImage.channels() + i];

        double dx2 = (int)oldX + 1 - oldX;
        double dx1 = oldX - (int)oldX;

        double dy2 = (int)oldY + 1 - oldY;
        double dy1 = oldY - (int)oldY;

        topImage.data[(y * topImage.cols + x) * topImage.channels() + i] = dy2 * (f11 * dx2 + f21 * dx1) + dy1 * (f12 * dx2 + f22 * dx1);
      }
    }
  }
}

void keyCallback(const test_opencv::key &key){
  ROS_INFO("ENTER");
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "img_publisher");
  ros::NodeHandle nh("~");
  ros::Rate looprate(10);

  image_transport::ImageTransport it(nh);
  image_transport::Publisher image_pub = it.advertise("image",1);

  cv::Mat image(Size(IMG_RAW_WIDTH,IMG_RAW_HEIGHT),CV_8UC3,Scalar::all(0));
  cv::VideoCapture camera;//変更したよん
  camera.open(1);

  camera.set(CV_CAP_PROP_FRAME_WIDTH,IMG_RAW_WIDTH);
  camera.set(CV_CAP_PROP_FRAME_HEIGHT,IMG_RAW_HEIGHT);

  if(!camera.isOpened()){
    ROS_INFO("failed to open camera.");
    return -1;
  }

  cv::Mat resize(Size(IMG_WIDTH,IMG_HEIGHT),CV_8UC3,Scalar::all(0));

  vector<Point2f> src, dst;
  src.push_back(Point2f(0,0));
  src.push_back(Point2f(image.cols,0));
  src.push_back(Point2f(image.cols,image.rows));
  dst.push_back(Point2f(0,0));
  dst.push_back(Point2f(resize.cols,0));
  dst.push_back(Point2f(resize.cols,resize.rows));

  cv::Mat affine = getAffineTransform(src,dst);
  cv::Mat topImage(Size(IMG_WIDTH,IMG_HEIGHT),CV_8UC3);
  topImage.setTo(Scalar(0));

  while(ros::ok()){
    camera >> image;
    warpAffine(image, resize, affine,resize.size(),CV_INTER_LINEAR);
    TopView(resize,topImage);

    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8",topImage).toImageMsg();
    image_pub.publish(msg);
    ros::Subscriber key_sub = nh.subscribe("key_pub",1,keyCallback);

    ros::spinOnce();
    looprate.sleep();
  }
  return 0;
}


