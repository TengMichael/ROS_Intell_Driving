#include "ros/ros.h"
#include "std_msgs/String.h"
#include <canbus/candata.h>
#include <canbus/candata_multi.h>
void chatterCallback(const canbus::candata_multi::ConstPtr& msg)
{
  for(uint8_t i=0;i<msg->frame.size();i++){
  boost::array<uint8_t, 8> arr=msg->frame[i].data;//fixed length array, need to use boost::array
  ROS_INFO("I heard: %d", arr[0]);
  ROS_INFO("I heard: %x", msg->frame[i].id);
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("chatter", 2000, chatterCallback);

  ros::spin();

  return 0;
}
