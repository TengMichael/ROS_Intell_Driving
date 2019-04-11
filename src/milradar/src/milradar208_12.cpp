#include "ros/ros.h"
#include "std_msgs/String.h"
#include <milradar.h>

using namespace Radar208;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "milradar208_12");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe<canbus::candata_multi>("can_device0_can2_receive", 1000,boost::bind(&Radar208_extract,_1,1,2));//1#,2#

  ros::Publisher pub208_1= nh.advertise<milradar::obj208_multi>("milradar_obj208_1", 1000);
  ros::Publisher pub208_2= nh.advertise<milradar::obj208_multi>("milradar_obj208_2", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    milradar::obj208_multi objs208multiarray[2];
    for(uint16_t j=0;j<2;j++){
      for(uint16_t i=0;i<Obj208_ID_Total[j];i++)
        objs208multiarray[j].objs.push_back(objs208[j][i]);
    }
    pub208_1.publish(objs208multiarray[0]);
    pub208_2.publish(objs208multiarray[1]);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
