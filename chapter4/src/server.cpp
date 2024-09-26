#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "chapter4/Command.h"

double linear_x_ = 0.0;
double angular_z_ = 0.0;

bool CommandServiceCallback(chapter4::Command::Request &req,
                                    chapter4::Command::Response &res)
{
  linear_x_ = req.linearX;
  angular_z_ = req.angularZ;

  res.result = "Receive";

  return true;

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "server_node");

  ros::NodeHandle n;

  geometry_msgs::Twist cmd_vel;
  ros::Publisher publisher_cmd_vel = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

  ros::ServiceServer service_server;
  service_server = n.advertiseService("command", CommandServiceCallback);


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

