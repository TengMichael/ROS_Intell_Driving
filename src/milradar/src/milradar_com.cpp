#include "ros/ros.h"
#include "std_msgs/String.h"
#include <canbus/candata_multi.h>
#include <milradar.h>

namespace Radar {
milradar::obj208 objs208[Sensors_208Num][Object_208Num]={};
milradar::obj208 objs208_out[Sensors_208Num][Object_208Num]={};

milradar::obj408 objs408[Object_408Num]={};
milradar::obj408 objs408_out[Object_408Num]={};

uint8_t Obj208_ID_Total[Sensors_208Num]={0};
uint8_t Obj208_ID_Total_out[Sensors_208Num];

uint8_t Obj408_ID_Total=0;
}
using namespace Radar;
/**********data preprocessing for the radar 408 by comparing two times sampling values************/
void Radar408_dataprocess2(void){
  uint8_t k=0;
  static uint8_t Obj408_ID_Total_last=0;
  static milradar::obj408 objs408_last[Object_408Num]={};
  milradar::obj408 objs408_temp[Object_408Num]={};

  for(uint8_t i=0;i<Obj408_ID_Total;i++){
    for(uint8_t j=0;j<Obj408_ID_Total_last;j++)
    {
      if((objs408_out[i].ID==objs408_last[j].ID)){
        if((fabs(objs408_out[i].DistX-objs408_last[j].DistX)<DistX_threshold)&&(fabs(objs408_out[i].DistY-objs408_last[j].DistY)<DistY_threshold)&&
           (fabs(objs408_out[i].VrelX-objs408_last[j].VrelX)<VrelX_threshold)&&(fabs(objs408_out[i].VrelY-objs408_last[j].VrelY)<VrelY_threshold))
        {
          memcpy(&(objs408_temp[k]),&(objs408_out[i]),sizeof(objs408[i]));
          k++;
        }
        break;
      }
      else
        continue;
    }
  }
  Obj408_ID_Total_last=Obj408_ID_Total;
  Obj408_ID_Total=k;
  memcpy(&(objs408_last),&(objs408_out),sizeof(objs408_out));
  memcpy(&(objs408_out),&(objs408_temp),sizeof(objs408_temp));
}
/**********data preprocessing for the radar 408 by setting threshold************/
void Radar408_dataprocess1(void){
  uint8_t k=0;
  milradar::obj408 objs408_temp[Object_408Num]={};
  for(uint8_t i=0;i<Obj408_ID_Total;i++){
    if((objs408[i].RCS<=RCS_threshold)||(objs408[i].ProbOfExist<=ProbOfExist_threshold)||
       (objs408[i].DistX<=0)||(objs408[i].DistY==0))
      continue;
    else
    {
      memcpy(&(objs408_temp[k]),&(objs408[i]),sizeof(objs408[i]));
      k++;
    }
  }
  Obj408_ID_Total=k;
  memcpy(&(objs408_out),&(objs408_temp),sizeof(objs408_temp));
}
/**********data preprocessing for the radar 408 by comparing two times sampling values************/
void Radar208_dataprocess2(void){
  uint8_t k=0;
  static uint8_t ID_Total_last[Sensors_208Num]={0};
  static milradar::obj208 objs208_last[Sensors_208Num][Object_208Num]={};
  milradar::obj208 objs208_temp[Sensors_208Num][Object_208Num]={};

  for(uint8_t s=0;s<Sensors_208Num;s++){
    k=0;
    for(uint8_t i=0;i<Obj208_ID_Total_out[s];i++){
      for(uint8_t j=0;j<ID_Total_last[s];j++)
      {
        if((objs208_out[s][i].ID==objs208_last[s][j].ID)){
          if((fabs(objs208_out[s][i].DistX-objs208_last[s][j].DistX)<DistX_threshold)&&(fabs(objs208_out[s][i].DistY-objs208_last[s][j].DistY)<DistY_threshold)&&
             (fabs(objs208_out[s][i].VrelX-objs208_last[s][j].VrelX)<VrelX_threshold)&&(fabs(objs208_out[s][i].VrelY-objs208_last[s][j].VrelY)<VrelY_threshold))
          {
            memcpy(&(objs208_temp[s][k]),&(objs208_out[s][i]),sizeof(objs208_out[s][i]));
            k++;
          }
          break;
        }
        else
          continue;
      }
    }
    ID_Total_last[s]=Obj208_ID_Total_out[s];
    Obj208_ID_Total_out[s]=k;
    ROS_INFO("Obj208_ID_Total_out[%d]:%d step2",s,Obj208_ID_Total_out[s]);

  }
  memcpy(&(objs208_last),&(objs208_out),sizeof(objs208_out));
  memcpy(&(objs208_out),&(objs208_temp),sizeof(objs208_temp));
}
/**********data preprocessing for the radar 408 by setting threshold************/
void Radar208_dataprocess1(void){
  uint8_t k=0;
  milradar::obj208 objs208_temp[Sensors_208Num][Object_208Num]={};

  for(uint8_t j=0;j<Sensors_208Num;j++){
    k=0;
    for(uint8_t i=0;i<Obj208_ID_Total_out[j];i++){
      if((objs208[j][i].RCS<=RCS_threshold)||(objs208[j][i].Lifetime<=Lifetime_threshold)||
         (objs208[j][i].DistX<=0)||(objs208[j][i].DistY==0))
      continue;
      else
      {
        memcpy(&(objs208_temp[j][k]),&(objs208[j][i]),sizeof(objs208[j][i]));
        k++;
      }
    }
    Obj208_ID_Total_out[j]=k;
    ROS_INFO("Obj208_ID_Total_out[%d]:%d step1",j,Obj208_ID_Total_out[j]);
  }
  memcpy(&(objs208_out),&(objs208_temp),sizeof(objs208_temp));
}
/*Receive and analysis radar208 CAN data to objects information*/
void Radar208_extract(const canbus::candata_multi::ConstPtr& CanData,uint8_t s1,uint8_t s2){
  uint8_t Obj_index;
  uint8_t Data[8];
  uint8_t j=0;
  uint8_t sensor_num[2];
  sensor_num[0]=s1-1;
  sensor_num[1]=s2-1;
  //memset(objs208,0,sizeof(objs208));
  for (uint16_t i = 0; i < CanData->frame.size(); i++) {
    memcpy(Data,&(CanData->frame[i].data),sizeof(CanData->frame[i].data));
    for(uint8_t s=0;s<2;s++){
      j=sensor_num[s];
      if (CanData->frame[i].id==(uint16_t)(0x61B+0x10*j)){
        Obj208_ID_Total[j]= Data[0];
      }
      else if (CanData->frame[i].id==(uint16_t)(0x61C+0x10*j)){
        Obj_index =Data[3]%32;
        //ROS_INFO("Obj_index: %d",Obj_index);
        objs208[j][Obj_index].index=Obj_index;
        objs208[j][Obj_index].ID = (uint16_t)Data[0]*256+Data[1];
        objs208[j][Obj_index].DistX = ((float)(Data[2] % 64) *8 + Data[3]/32)*0.1;
        objs208[j][Obj_index].DistY = ((float)Data[4] * 4 + Data[5] / 64)*0.1-51.1;
        objs208[j][Obj_index].VrelX = ((float)(Data[5] % 64)*64 + Data[6] / 4)*0.02 - 35;
        objs208[j][Obj_index].VrelY = (float)Data[7] *0.25 -32;
      }
      else if (CanData->frame[i].id==(uint16_t)(0x61D+0x10*j)){
        Obj_index = Data[3]%32;
        objs208[j][Obj_index].RCS = (float)Data[0]*0.5-50;
        objs208[j][Obj_index].Lifetime = (float)(Data[1]*256+Data[2])*0.1;
      }
      else{}
    }
  }
  memcpy(Obj208_ID_Total_out,Obj208_ID_Total,sizeof(Obj208_ID_Total));
  //memcpy(&(objs208_out),&(objs208),sizeof(objs208));
}
/*Receive and analysis radar408 CAN data to objects information*/
void Radar408_extract(const canbus::candata_multi CanData){
  uint8_t Obj_ID;
  uint8_t Obj_index=0;
  uint8_t Data[8];
  uint8_t objs408_mask[Object_408Num*4];//Four times to deal with repeated data
  milradar::obj408 objs408_temp[Object_408Num]={};

  for (uint16_t i= 0; i < CanData.frame.size(); i++) {
    memcpy(Data,&(CanData.frame[i].data),sizeof(CanData.frame[i].data));
    switch (CanData.frame[i].id) {
    case 0x60A:
      Obj408_ID_Total = Data[0];
      break;
    case 0x60B:
      Obj_ID = Data[0];
      objs408_mask[Obj_index]=Obj_ID;
      Obj_index++;
      objs408_temp[Obj_ID].ID = Obj_ID;
      objs408_temp[Obj_ID].DistX = ((float)Data[1] * 32 + Data[2] / 8)*0.2 - 500;
      objs408_temp[Obj_ID].DistY = ((float)(Data[2] % 8) * 256 + Data[3])*0.2 - 204.6;
      objs408_temp[Obj_ID].VrelX = ((float)Data[4] * 4 + Data[5] / 64)*0.25 - 128;
      objs408_temp[Obj_ID].VrelY = ((float)(Data[5] % 64) * 8 + Data[6] / 32)*0.25 - 64;
      objs408_temp[Obj_ID].DynProp = Data[6] % 8;
      objs408_temp[Obj_ID].RCS = (float)(Data[7])*0.5 - 64;
      break;
    case 0x60C:
      Obj_ID = Data[0];
      objs408_temp[Obj_ID].MeasState = (Data[6] & 0x1C) / 4;
      objs408_temp[Obj_ID].ProbOfExist = Data[6] / 32;
      break;
    case 0x60D:
      Obj_ID = Data[0];
      objs408_temp[Obj_ID].ArelX = ((float)Data[1] * 8 + Data[2] / 32)*0.01 - 10;
      objs408_temp[Obj_ID].ArelY = ((float)(Data[2] % 32) * 16 + Data[3] / 16)*0.01 - 2.5;
      objs408_temp[Obj_ID].Class = Data[3] % 8;
      objs408_temp[Obj_ID].OrientationAngel = ((float)Data[4] * 4 + Data[5] / 64)*0.4 - 180;
      objs408_temp[Obj_ID].Length = (float)Data[6] * 0.2;
      objs408_temp[Obj_ID].Width = (float)Data[7] * 0.2;
      break;
    default: break;
    }
  }
  memset(objs408,0,sizeof(objs408));
  /***************rank the objects matrix by index other than random object ID****************/
  for (uint16_t i= 0; i< Obj408_ID_Total; i++)
    memcpy(&(objs408[i]),&(objs408_temp[objs408_mask[i]]),sizeof(objs408[i]));
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "milradar_com");
  ros::NodeHandle nh;

  ros::Subscriber sub0 = nh.subscribe ("can_device0_can1_receive", 1000,Radar408_extract);
  ros::Subscriber sub1 = nh.subscribe<canbus::candata_multi>("can_device0_can2_receive", 1000,boost::bind(&Radar208_extract,_1,1,2));//1#,2#
  ros::Subscriber sub2 = nh.subscribe<canbus::candata_multi>("can_device1_can1_receive", 1000,boost::bind(&Radar208_extract,_1,4,6));//4#,6#
  ros::Subscriber sub3 = nh.subscribe<canbus::candata_multi>("can_device1_can2_receive", 1000,boost::bind(&Radar208_extract,_1,3,5));//3#,5#

  ros::Publisher pub408= nh.advertise<milradar::obj408_multi>("milradar_obj408", 1000);
  ros::Publisher pub208_1= nh.advertise<milradar::obj208_multi>("milradar_obj208_1", 1000);
  ros::Publisher pub208_2= nh.advertise<milradar::obj208_multi>("milradar_obj208_2", 1000);
  ros::Publisher pub208_3= nh.advertise<milradar::obj208_multi>("milradar_obj208_3", 1000);
  ros::Publisher pub208_4= nh.advertise<milradar::obj208_multi>("milradar_obj208_4", 1000);
  ros::Publisher pub208_5= nh.advertise<milradar::obj208_multi>("milradar_obj208_5", 1000);
  ros::Publisher pub208_6= nh.advertise<milradar::obj208_multi>("milradar_obj208_6", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    milradar::obj208_multi objs208multiarray[Sensors_208Num];
    milradar::obj408_multi objs408multiarray;
    //ROS_INFO("Obj408_ID_Total: %d",Obj408_ID_Total);9009099
    //ROS_INFO("objs408[i].ID: %d",objs408[0].ID);
    Radar208_dataprocess1();
    Radar208_dataprocess2();
    Radar408_dataprocess1();
    Radar408_dataprocess2();
    for(uint16_t i=0;i<Obj408_ID_Total;i++)
      objs408multiarray.objs.push_back(objs408[i]);
    for(uint16_t j=0;j<Sensors_208Num;j++){
      for(uint16_t i=0;i<Obj208_ID_Total_out[j];i++)
        objs208multiarray[j].objs.push_back(objs208_out[j][i]);
    }
    pub408.publish(objs408multiarray);
    pub208_1.publish(objs208multiarray[0]);
    pub208_2.publish(objs208multiarray[1]);
    pub208_3.publish(objs208multiarray[2]);
    pub208_4.publish(objs208multiarray[3]);
    pub208_5.publish(objs208multiarray[4]);
    pub208_6.publish(objs208multiarray[5]);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
