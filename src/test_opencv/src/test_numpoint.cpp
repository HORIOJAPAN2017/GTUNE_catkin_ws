#include "ros/ros.h"
#include "std_msgs/String.h"
#include "test_opencv/now_num.h"

#include <sstream>

int main(int argc, char **argv){
  ros::init(argc,argv,"test_now");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<test_opencv::now_num>("now_num",1);

  ros::Rate loop_rate(10);

  int count = 0;
  while(ros::ok()){
    test_opencv::now_num num;
    
    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
