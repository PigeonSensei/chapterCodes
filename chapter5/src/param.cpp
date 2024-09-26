#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "param_node");

  ros::NodeHandle n;

  geometry_msgs::Twist cmd_vel;
  ros::Publisher publisher_cmd_vel = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

  double linear_x;
  double angular_z;

  n.param<double>("LinearX", linear_x, 0.0);
  n.param<double>("AngularZ", angular_z, 0.0);



  ros::Rate loop_rate(60);

  while (ros::ok())
  {

    cmd_vel.linear.x = linear_x;
    cmd_vel.angular.z = angular_z;
    publisher_cmd_vel.publish(cmd_vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
