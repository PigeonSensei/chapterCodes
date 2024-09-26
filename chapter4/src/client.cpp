#include <ros/ros.h>
#include "chapter4/Command.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "client_node");
  ros::NodeHandle n;

  ros::ServiceClient service_client_command;
  service_client_command = n.serviceClient<chapter4::Command>("command");

  chapter4::Command command;

  command.request.linearX = 10.0;
  command.request.angularZ = 10.0;

  service_client_command.call(command);

  return 0;

}

