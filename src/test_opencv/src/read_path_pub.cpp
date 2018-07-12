#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "test_opencv/coordinate.h"
#include "test_opencv/now_num.h"
#include "test_opencv/path.h"

test_opencv::path path;
ros::Publisher point_pub; 
int num = 0;

int main(int argc, char **argv){
  ros::init(argc,argv,"path");

  ros::NodeHandle n;

  FILE *fp;

  char filename[] = "/home/user/catkin_ws/src/test_opencv/tsukuba/path.txt";
  char str[256];

  fp = fopen(filename,"r");
  if(fp == NULL){
    ROS_ERROR("%s file not opened",filename);
    return -1;
  }

  int count = 0;
  while(fgets(str,256,fp) !=NULL){
    count++;
  }

  fclose(fp);

  path.gridX.clear();
  path.gridY.clear();
  path.height.clear();
  path.width.clear();
  //path.theta.clear(); 
  path.number_of_path=count;

  fp = fopen(filename,"r");

  int i = 0;
  int gridX,gridY,width,height;
  while(fgets(str,256,fp) != NULL){
    sscanf(str,"%d,%d,%d,%d",&gridX,&gridY,&height,&width);
    path.gridX.push_back(gridX);
    path.gridY.push_back(gridY);
    path.width.push_back(width);
    path.height.push_back(height);
    //path.theta.push_back(theta);
    ROS_ERROR("%d,%d,%d,%d",path.gridX[i],path.gridY[i],path.height[i],path.width[i]);
    i++;
  }

  fclose(fp);
  
  point_pub = n.advertise<test_opencv::path>("path",1);

  while(ros::ok()){

    point_pub.publish(path);

    ros::spinOnce();
//    ROS_ERROR("hoge");
  }
  

  return 0;
}
