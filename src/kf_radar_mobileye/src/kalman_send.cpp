#include "ros/ros.h"
#include <kf_radar_mobileye/radar_mobileye_data_multi.h>
#include <random>
int main(int argc, char **argv)
{
  ros::init(argc, argv, "kalman_send");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub = nh.advertise<kf_radar_mobileye::radar_mobileye_data_multi>("radar_mobileye_data_multi", 1000);

  kf_radar_mobileye::radar_mobileye_data msg;
  memset(&msg,0,sizeof(&msg));

  std::default_random_engine generate;
  std::normal_distribution<> norm_noise;
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    kf_radar_mobileye::radar_mobileye_data_multi msgsend;
    msgsend.objs.push_back(msg);
    chatter_pub.publish(msgsend);
    msg.timestamp=msg.timestamp+100;
    msg.ID=0;
    msg.radar_DistX=msg.radar_DistX+msg.radar_VrelX*0.1+norm_noise(generate)*4;
    msg.radar_DistY=msg.radar_DistY+msg.radar_VrelY*0.1+norm_noise(generate)*1;
    msg.radar_VrelX=20+norm_noise(generate)*4;
    msg.radar_VrelY=0+norm_noise(generate)*2;

    msg.mobileye_DistX=msg.mobileye_DistX+msg.mobileye_VrelX*0.1+norm_noise(generate)*4;
    msg.mobileye_DistY=msg.radar_DistY;
    msg.mobileye_VrelX=20+norm_noise(generate)*4;

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
