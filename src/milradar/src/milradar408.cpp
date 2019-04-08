#include "ros/ros.h"
#include "std_msgs/String.h"
#include <milradar/milradar.h>


using namespace Radar408;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "milradar408");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe ("can_device0_can1_receive", 1000,Radar408_extract);

  ros::Publisher pub408= nh.advertise<milradar::obj408_multi>("milradar_obj408", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    milradar::obj408_multi objs408multiarray;
    for(uint16_t i=0;i<Obj408_ID_Total;i++)
      objs408multiarray.objs.push_back(objs408[i]);

    pub408.publish(objs408multiarray);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
