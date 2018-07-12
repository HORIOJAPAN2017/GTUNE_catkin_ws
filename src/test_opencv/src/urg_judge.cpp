#include "ros/ros.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "sensor_msgs/LaserScan.h"
#include "test_opencv/key.h"

#include <sstream>

float front_urg_data[640];
int front_data_size;

float back_urg_data[260];
int back_data_size;

ros::Publisher front_pub;
ros::Publisher back_pub;
test_opencv::key front_key;
test_opencv::key back_key;

void frontCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
  int i = 0;

  for(std::vector<float>::const_iterator it = scan->ranges.begin(); it != scan->ranges.end();++it){
    front_urg_data[i] = *it;
    if(front_urg_data[i] > 10)
      front_urg_data[i] = -1;
    i++;
  }
  front_data_size = i;

  float length;
  int judgment = -1;
  float zone_A = 5.0;
  float zone_B = 3.0;
  float zone_C = 1.0;
  float zone_D = 0.5;

  for (int i = 0; i < front_data_size; i++){
    
    length = front_urg_data[i];

    if(length > 0.01){
      if(length > zone_A && judgment < 0){
      judgment = 0;
      }
      else if(length <= zone_A && length > zone_B && judgment < 1){
        judgment = 1;
      }
      else if(length <= zone_B && length > zone_C && judgment < 2){
        judgment = 2;
      }
      else if(length <= zone_C){
        judgment = 3;
      }
      else if(length <= zone_D){
        judgment = 4;
        break;
      }

    }
  }

  front_key.ENTER = judgment;
  front_pub.publish(front_key);
}

void backCallback(const sensor_msgs::LaserScan::ConstPtr& scan){
  int i = 0;

  for(std::vector<float>::const_iterator it = scan->ranges.begin(); it != scan->ranges.end();++it){
    back_urg_data[i] = *it;
    if(back_urg_data[i] > 4)
      back_urg_data[i] = -1;
    i++;
  }
  back_data_size = i;

  float length;
  int judgment = -1;
  float zone_A = 4.0;
  float zone_B = 2.0;
  float zone_C = 1.0;

  for (int i = 0; i < back_data_size; i++){
    
    length = back_urg_data[i];

    if(length > 0.01){
      if(length > zone_A && judgment < 0){
      judgment = 0;
      }
      else if(length <= zone_A && length > zone_B && judgment < 1){
        judgment = 1;
      }
      else if(length <= zone_B && length > zone_C && judgment < 2){
        judgment = 2;
      }
      else if(length <= zone_C){
        judgment = 3;
        break;
      }
    }
  }

  back_key.ENTER = judgment;
  back_pub.publish(back_key);
}
 

int main(int argc, char **argv){
  ros::init(argc,argv,"urg_judge");

  ros::NodeHandle n;

  front_pub = n.advertise<test_opencv::key>("front_ok",1);
  back_pub = n.advertise<test_opencv::key>("back_ok",1);
  ros::Subscriber front_sub = n.subscribe("/urg_front/scan",1,frontCallback); 
  ros::Subscriber back_sub = n.subscribe("/urg_back/scan",1,backCallback); 

  ros::spin();

  return 0;
}
