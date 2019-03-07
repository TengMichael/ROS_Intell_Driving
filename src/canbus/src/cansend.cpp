#include "ros/ros.h"
//#include "std_msgs/String.h"
#include <canbus/candata.h>
#include <canbus/candata_multi.h>
int main(int argc, char **argv)
{
  ros::init(argc, argv, "cansend");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub = nh.advertise<canbus::candata_multi>("can_device0_can0_send_chatter", 2000);
  uint8_t j=0;
  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    canbus::candata msg;
    canbus::candata_multi msg_multi;
    for(uint8_t i=0;i<8;i++)
      msg.data[i]=i;
    msg.id =j++;
    msg_multi.frame.push_back(msg);

    chatter_pub.publish(msg_multi);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
