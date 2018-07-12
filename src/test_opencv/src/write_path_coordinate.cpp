#include "ros/ros.h"
#include "test_opencv/coordinate.h"
#include "test_opencv/key.h"
#include <stdio.h>
#include <stdlib.h>

FILE *outputfile;

int now_gridX = 0;
int now_gridY = 0;
int now_coordinate_HEIGHT = 0;
int now_coordinate_WIDTH = 0;

void coordinateCallback(const test_opencv::coordinate &now_coordinate)
{
  ROS_INFO("%d,%d,%d,%d", now_coordinate.gridX,now_coordinate.gridY,now_coordinate.height,now_coordinate.width);
  now_gridX = now_coordinate.gridX;
  now_gridY = now_coordinate.gridY;
  now_coordinate_HEIGHT = now_coordinate.height;
  now_coordinate_WIDTH = now_coordinate.width;
}

void keyCallback(const test_opencv::key &key){
  fprintf(outputfile,"%d,%d,%d,%d\n",now_gridX,now_gridY,now_coordinate_HEIGHT,now_coordinate_WIDTH);
  ROS_INFO("output:%d,%d,%d,%d", now_gridX,now_gridY,now_coordinate_HEIGHT,now_coordinate_WIDTH);
}

int main(int argc, char **argv){
  ros::init(argc,argv, "write_path_coord");

  ros::NodeHandle n;
  outputfile = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/path.txt","w");
  if(outputfile == NULL){
    ROS_INFO("path.txtが開けないよん");
    exit(1);
  }

  ros::Subscriber sub = n.subscribe("now_pos_GL",1,coordinateCallback);
  ros::Subscriber sub_key = n.subscribe("key",1,keyCallback);

  ros::spin();

  fclose(outputfile);
  return 0;
}
