#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_datatypes.h>

class rsj_robot_test_node
{
private:
    ros::Subscriber sub_odom;
    ros::Subscriber sub_scan;
    ros::Publisher pub_twist;

    void cb_odom(const nav_msgs::Odometry::ConstPtr &msg)
    {
    }
    void cb_scan(const sensor_msgs::LaserScan::ConstPtr &msg){
      int i = msg->ranges.size() / 2;
      if(msg->ranges[i] < msg->range_min ||
          msg->ranges[i] > msg->range_max||
          std::isnan(msg->ranges[i]))
      {
        ROS_INFO("front-range:measurement error");
      }
      else
      {
        ROS_INFO("front-range: %0.3f",msg->ranges[msg->ranges.size() / 2]);
      }
    }
public:
    int i=0;
    rsj_robot_test_node()
    {
        ros::NodeHandle nh("~");
        pub_twist = nh.advertise<geometry_msgs::Twist>(
                    "/ypspur_ros/cmd_vel", 5);
        sub_odom = nh.subscribe("/ypspur_ros/odom", 5,
                                &rsj_robot_test_node::cb_odom, this);
        sub_scan = nh.subscribe("/scan", 5, &rsj_robot_test_node::cb_scan,this);
    }
    void mainloop()
    {
        ROS_INFO("Hello ROS World!");

        ros::Rate rate(10.0);
        while(ros::ok())
        {
            ros::spinOnce();
            i++;
            printf("i = %d/n",i);
            // ここに速度指令の出力コード
            rate.sleep();
        }
        // ここに終了処理のコード
    }
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "rsj_robot_test_node");

    rsj_robot_test_node robot_test;

    robot_test.mainloop();
}

