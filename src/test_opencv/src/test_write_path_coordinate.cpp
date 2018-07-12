#include "ros/ros.h"
#include "std_msgs/String.h"
#include "test_opencv/coordinate.h"

#include <sstream>

int main(int argc, char **argv){
  ros::init(argc,argv,"pub_coordinate");

  ros::NodeHandle n;

  ros::Publisher coordinate_pub = n.advertise<test_opencv::coordinate>("coordinate",1);

  ros::Rate loop_rate(10);

  int count = 0;
  while(ros::ok()){
    test_opencv::coordinate now_coordinate;
///    std_msgs::String msg;

//    std::stringstream ss;
//    ss << "hello world" << count;
//    msg.data = ss.str();
    now_coordinate.gridX = 1+count;
    now_coordinate.gridY = -1-count;
    now_coordinate.height = 80;
    now_coordinate.width = 120;

    ROS_INFO("%d,%d,%d,%d", now_coordinate.gridX,now_coordinate.gridY,now_coordinate.height,now_coordinate.width);

//    chatter_pub.publish(msg);
    coordinate_pub.publish(now_coordinate); 

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
