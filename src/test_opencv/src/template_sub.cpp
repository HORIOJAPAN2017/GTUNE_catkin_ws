#include "ros/ros.h"
#include "std_msgs/String.h"

void Callback(const std_msgs::String::ConstPtr& msg){
  ROS_INFO("hogehoge%s",msg->data.c_str());
}

int main(int argc, char **argv){
  ros::init(argc,argv,"listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscriber("chatter",1,Callback);

  ros::spin();

  return 0;
}
