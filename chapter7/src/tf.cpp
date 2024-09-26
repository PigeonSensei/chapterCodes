#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>

double x = 0.0;
double y = 0.0;

void TurtlePoseCallback(const turtlesim::Pose::ConstPtr& msg)
{
  x = msg->x;
  y = msg->y;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tf_node");
  ros::NodeHandle n;

  ros::Subscriber subscriber_turtle_pose;
  subscriber_turtle_pose = n.subscribe("turtle1/pose", 1000, TurtlePoseCallback);

  tf::TransformBroadcaster broadcaster;


  ros::Rate loop_rate(60);

  while (ros::ok())
  {

    broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::Quaternion(0.0, 0.0, 0.0, 1.0), tf::Vector3(x, y, 0.0)),
                                                   ros::Time::now(),
                                                   "base_link",
                                                   "turtle_link"));

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

