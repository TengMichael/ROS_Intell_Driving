#include "ros/ros.h"
#include "std_msgs/String.h"
#include <canbus/candata_multi.h>
#include <milradar/obj208.h>
#include <milradar/obj408.h>
/*Analysis radar408 CAN data to objects information*/

namespace Radar {
#define Object_408Num 100
#define Object_208Num 25
#define Sensors_208Num 6

milradar::obj208 objs208[Sensors_208Num][Object_208Num];
milradar::obj408 objs408[Object_408Num];
}

using namespace Radar;
/*Receive and analysis radar208 CAN data to objects information*/
void Radar208_process(const canbus::candata_multi CanData){
  uint8_t Obj_ID;
  uint8_t Obj_ID_Total[Sensors_208Num]={0};
  uint16_t i,j;
  uint8_t *Data;
  for (i = 0; i < CanData.frame.size(); i++) {
    memcpy(Data,&(CanData.frame[i].data),sizeof(CanData.frame[i].data));
    for(j=0;j<Sensors_208Num;j++){
      if (CanData.frame[i].id==(uint16_t)(0x61B+0x10*j)){
        Obj_ID_Total[j] = Data[0];
      }
      else if (CanData.frame[i].id==(uint16_t)(0x61C+0x10*j)){
        Obj_ID =Data[3]%32;
        //ROS_INFO("Obj_ID: %d",Obj_ID);
        objs208[j][Obj_ID].index=Obj_ID;
        objs208[j][Obj_ID].ID = (uint16_t)Data[0]*256+Data[1];
        objs208[j][Obj_ID].DistX = ((float)(Data[2] % 64) *8 + Data[3]/32)*0.1;
        objs208[j][Obj_ID].DistY = ((float)Data[4] * 4 + Data[5] / 64)*0.1-51.1;
        objs208[j][Obj_ID].VrelX = ((float)(Data[5] % 64)*64 + Data[6] / 4)*0.02 - 35;
        objs208[j][Obj_ID].VrelY = (float)Data[7] *0.25 -32;
      }
      else if (CanData.frame[i].id==(uint16_t)(0x61D+0x10*j)){
        Obj_ID = Data[3]%32;
        objs208[j][Obj_ID].RCS = (float)Data[0]*0.5-50;
        objs208[j][Obj_ID].Lifetime = (float)(Data[1]*256+Data[2])*0.1;
      }
      else{}
    }
  }
}
/*Receive and analysis radar408 CAN data to objects information*/
void Radar408_process(const canbus::candata_multi CanData){
  uint8_t Obj_ID;
  uint8_t Obj_ID_Total=0;
  uint16_t i;
  uint8_t *Data;
  for (i = 0; i < CanData.frame.size(); i++) {
    memcpy(Data,&(CanData.frame[i].data),sizeof(CanData.frame[i].data));
    switch (CanData.frame[i].id) {
    case 0x60A:
      Obj_ID_Total = Data[0];
      break;
    case 0x60B:
      Obj_ID = Data[0];
      objs408[Obj_ID].ID = Obj_ID;
      objs408[Obj_ID].DistX = ((float)Data[1] * 32 + Data[2] / 8)*0.2 - 500;
      objs408[Obj_ID].DistY = ((float)(Data[2] % 8) * 256 + Data[3])*0.2 - 204.6;
      objs408[Obj_ID].VrelX = ((float)Data[4] * 4 + Data[5] / 64)*0.25 - 128;
      objs408[Obj_ID].VrelY = ((float)(Data[5] % 64) * 8 + Data[6] / 32)*0.25 - 64;
      objs408[Obj_ID].DynProp = Data[6] % 8;
      objs408[Obj_ID].RCS = (float)(Data[7])*0.5 - 64;
      break;
    case 0x60C:
      Obj_ID = Data[0];
      objs408[Obj_ID].MeasState = (Data[6] & 0x1C) / 4;
      objs408[Obj_ID].ProbOfExist = Data[6] / 32;
      break;
    case 0x60D:
      Obj_ID = Data[0];
      objs408[Obj_ID].ArelX = ((float)Data[1] * 8 + Data[2] / 32)*0.01 - 10;
      objs408[Obj_ID].ArelY = ((float)(Data[2] % 32) * 16 + Data[3] / 16)*0.01 - 2.5;
      objs408[Obj_ID].Class = Data[3] % 8;
      objs408[Obj_ID].OrientationAngel = ((float)Data[4] * 4 + Data[5] / 64)*0.4 - 180;
      objs408[Obj_ID].Length = (float)Data[6] * 0.2;
      objs408[Obj_ID].Width = (float)Data[7] * 0.2;
      break;
    default: break;
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "milradar_com");
  ros::NodeHandle nh;

  ros::Publisher pub1 = nh.advertise<milradar::obj208>("milradar_obj208", 1000);

  ros::Subscriber sub1 = nh.subscribe<canbus::candata_multi> ("can_device0_can1_receive", 1000,Radar408_process);
  ros::Subscriber sub2 = nh.subscribe<canbus::candata_multi> ("can_device0_can2_receive", 1000,Radar208_process);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {

    pub1.publish(objs208[0][0]);
    pub1.publish(objs208[0][1]);
    pub1.publish(objs208[0][2]);
    pub1.publish(objs208[0][3]);
    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
