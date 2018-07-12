#include "ros/ros.h"
#include "std_msgs/String.h"
#include "test_opencv/key.h"
#include <sstream>

int main(int argc, char **argv){
  ros::init(argc,argv,"key_pub");

  ros::NodeHandle n;

  ros::Publisher key_pub = n.advertise<test_opencv::key>("key",1);

  ros::Rate loop_rate(10);

  int count = 0;
  while(ros::ok()){
    test_opencv::key k;
    k.ENTER = 0;

    getchar();

    ROS_ERROR("ENTER");

    k.ENTER = 1;

    key_pub.publish(k);

    ros::spinOnce();

    ++count;
  }

  return 0;
}
