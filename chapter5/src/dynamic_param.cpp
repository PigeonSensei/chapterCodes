#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "dynamic_reconfigure/server.h"
#include "chapter5/DynamicParamConfig.h"

double linear_x_ = 0.0;
double angular_z_ = 0.0;

void DynamicReconfigureCallback(chapter5::DynamicParamConfig &config, uint32_t level)
{
  linear_x_ = config.linear_x;
  angular_z_ = config.angular_z;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamic_param_node");

  ros::NodeHandle n;

  geometry_msgs::Twist cmd_vel;
  ros::Publisher publisher_cmd_vel = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

  dynamic_reconfigure::Server<chapter5::DynamicParamConfig> server;
  dynamic_reconfigure::Server<chapter5::DynamicParamConfig>::CallbackType f;

  f = boost::bind(&DynamicReconfigureCallback, _1, _2);
  server.setCallback(f);


  ros::Rate loop_rate(60);

  while (ros::ok())
  {

    cmd_vel.linear.x = linear_x_;
    cmd_vel.angular.z = angular_z_;
    publisher_cmd_vel.publish(cmd_vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

