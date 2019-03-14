#include "ros/ros.h"
#include "std_msgs/String.h"
#include <canbus/candata_multi.h>
#include <milradar/obj208.h>
#include <milradar/obj208_multi.h>
#include <milradar/obj408.h>
#include <milradar/obj408_multi.h>

namespace Radar {
#define Object_408Num 100
#define Object_208Num 25
#define Sensors_208Num 6
#define RCS_threshold 0 //dBm^2
#define ProbOfExist_threshold 1 //0x01:<25%;0x02:<50%;
#define Lifetime_threshold 1 //s
#define DistX_threshold 6
#define DistY_threshold 6
#define VrelX_threshold 6
#define VrelY_threshold 6
milradar::obj208 objs208[Sensors_208Num][Object_208Num];
milradar::obj408 objs408[Object_408Num];

uint8_t Obj208_ID_Total[Sensors_208Num]={0};
uint8_t Obj408_ID_Total=0;
}
using namespace Radar;
/**********data processing for the radar 408 when the index of array is objects ID************/
void Radar408_dataprocess1(milradar::obj408 objs408[],uint8_t *ID_Total_Prt){
    static uint8_t start_flag=0;
    static milradar::obj408 objs408_last[Object_408Num]={};
    milradar::obj408 objs408_temp[Object_408Num]={};
    uint8_t j=0;

    if(start_flag){
        for(uint8_t i=0;i<Object_408Num;i++){
            if((fabs(objs408[i].DistX-objs408_last[i].DistX)>DistX_threshold)||(fabs(objs408[i].DistY-objs408_last[i].DistY)>DistY_threshold)||
                    (fabs(objs408[i].VrelX-objs408_last[i].VrelX)>VrelX_threshold)||(fabs(objs408[i].VrelY-objs408_last[i].VrelY)>VrelY_threshold))
                continue;
            else
                memcpy(&(objs408_temp[j]),&(objs408[i]),sizeof(objs408[i]));
            j++;
        }
        *ID_Total_Prt=j;
        for(uint8_t i=0;i<*ID_Total_Prt;i++)
            memcpy(&(objs408[j]),&(objs408_temp[i]),sizeof(objs408_temp[i]));
    }
    memcpy(&(objs408_last),&(objs408),sizeof(objs408));
    start_flag=1;
}
/**********data processing for the radar 408 ************/
void Radar408_dataprocess(void){
    uint8_t k=0;
    milradar::obj408 objs408_temp[Object_408Num]={};
    for(uint8_t i=0;i<Obj408_ID_Total;i++){
        if((objs408[i].RCS<=RCS_threshold)||(objs408[i].ProbOfExist<=ProbOfExist_threshold)||
                (objs408[i].DistX==0)||(objs408[i].DistY==0))
            continue;
        else
        {
            memcpy(&(objs408_temp[k]),&(objs408[i]),sizeof(objs408[i]));
            k++;
        }
        Obj408_ID_Total=k;
    }
    memcpy(&(objs408),&(objs408_temp),sizeof(objs408_temp));
}
/**********data processing for the radar 208************/
void Radar208_dataprocess(void){
    uint8_t k=0;
    milradar::obj208 objs208_temp[Sensors_208Num][Object_208Num]={};
    for(uint8_t j=0;j<Sensors_208Num;j++){
        k=0;
        for(uint8_t i=0;i<Obj208_ID_Total[j];i++){
            if((objs208[j][i].RCS<=RCS_threshold)||(objs208[j][i].Lifetime<=Lifetime_threshold)||
                    (objs208[j][i].DistX==0)||(objs208[j][i].DistY==0))
                continue;
            else
            {
                memcpy(&(objs208_temp[j][k]),&(objs208[j][i]),sizeof(objs208[j][i]));
                k++;
            }
        }
        Obj208_ID_Total[j]=k;
    }
    memcpy(&(objs208),&(objs208_temp),sizeof(objs208_temp));
    //ROS_INFO("objs208_temp[0][0].ID: %d",objs208_temp[0][0].ID);
    //ROS_INFO("objs208[0][0].ID: %d",objs208[0][0].ID);
}
/*Receive and analysis radar208 CAN data to objects information*/
void Radar208_extract(const canbus::candata_multi CanData){
    uint8_t Obj_index;
    uint8_t Obj_ID_Total[Sensors_208Num]={0};
    uint8_t *Data;
    memset(objs208,0,sizeof(objs208));
    for (uint16_t i = 0; i < CanData.frame.size(); i++) {
        memcpy(Data,&(CanData.frame[i].data),sizeof(CanData.frame[i].data));
        for(uint16_t j=0;j<Sensors_208Num;j++){
            if (CanData.frame[i].id==(uint16_t)(0x61B+0x10*j)){
                Obj_ID_Total[j] = Data[0];
                Obj208_ID_Total[j]=Obj_ID_Total[j];
            }
            else if (CanData.frame[i].id==(uint16_t)(0x61C+0x10*j)){
                Obj_index =Data[3]%32;
                //ROS_INFO("Obj_index: %d",Obj_index);
                objs208[j][Obj_index].index=Obj_index;
                objs208[j][Obj_index].ID = (uint16_t)Data[0]*256+Data[1];
                objs208[j][Obj_index].DistX = ((float)(Data[2] % 64) *8 + Data[3]/32)*0.1;
                objs208[j][Obj_index].DistY = ((float)Data[4] * 4 + Data[5] / 64)*0.1-51.1;
                objs208[j][Obj_index].VrelX = ((float)(Data[5] % 64)*64 + Data[6] / 4)*0.02 - 35;
                objs208[j][Obj_index].VrelY = (float)Data[7] *0.25 -32;
            }
            else if (CanData.frame[i].id==(uint16_t)(0x61D+0x10*j)){
                Obj_index = Data[3]%32;
                objs208[j][Obj_index].RCS = (float)Data[0]*0.5-50;
                objs208[j][Obj_index].Lifetime = (float)(Data[1]*256+Data[2])*0.1;
            }
            else{}
        }
    }
    Radar208_dataprocess();
}
/*Receive and analysis radar408 CAN data to objects information*/
void Radar408_extract(const canbus::candata_multi CanData){
    uint8_t Obj_ID,Obj_index,Obj_ID_Total;
    uint8_t *Data;
    uint8_t objs408_mask[Object_408Num];
    milradar::obj408 objs408_temp[Object_408Num]={};

    for (uint16_t i= 0; i < CanData.frame.size(); i++) {
        memcpy(Data,&(CanData.frame[i].data),sizeof(CanData.frame[i].data));
        switch (CanData.frame[i].id) {
        case 0x60A:
            Obj_ID_Total = Data[0];
            Obj408_ID_Total = Obj_ID_Total;
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
    for (uint16_t i= 0; i< Obj_ID_Total; i++)
        /***************rank the objects matrix by index other than random object ID****************/
        memcpy(&(objs408[i]),&(objs408_temp[objs408_mask[i]]),sizeof(objs408[i]));
    Radar408_dataprocess();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "milradar_com");
    ros::NodeHandle nh;

    ros::Subscriber sub1 = nh.subscribe ("can_device0_can1_receive", 1000,Radar408_extract);
    ros::Subscriber sub2 = nh.subscribe ("can_device0_can2_receive", 1000,Radar208_extract);

    ros::Publisher pub408= nh.advertise<milradar::obj408_multi>("milradar_obj408", 1000);
    ros::Publisher pub208_1= nh.advertise<milradar::obj208_multi>("milradar_obj208_1", 1000);
    ros::Publisher pub208_2= nh.advertise<milradar::obj208_multi>("milradar_obj208_2", 1000);
    ros::Publisher pub208_3= nh.advertise<milradar::obj208_multi>("milradar_obj208_3", 1000);
    ros::Publisher pub208_4= nh.advertise<milradar::obj208_multi>("milradar_obj208_4", 1000);
    ros::Publisher pub208_5= nh.advertise<milradar::obj208_multi>("milradar_obj208_5", 1000);
    ros::Publisher pub208_6= nh.advertise<milradar::obj208_multi>("milradar_obj208_6", 1000);

    //ros::Publisher pub208= nh.advertise<milradar::obj208>("milradar_obj208", 1000);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        milradar::obj208_multi objs208multiarray[Sensors_208Num];
        milradar::obj408_multi objs408multiarray;

        for(uint16_t i=0;i<Obj408_ID_Total;i++)
            objs408multiarray.objs.push_back(objs408[i]);
        for(uint16_t j=0;j<Sensors_208Num;j++){
            for(uint16_t i=0;i<Obj208_ID_Total[j];i++)
                objs208multiarray[j].objs.push_back(objs208[j][i]);
        }
        pub408.publish(objs408multiarray);
        pub208_1.publish(objs208multiarray[0]);
        pub208_2.publish(objs208multiarray[1]);
        pub208_3.publish(objs208multiarray[2]);
        pub208_4.publish(objs208multiarray[3]);
        pub208_5.publish(objs208multiarray[4]);
        pub208_6.publish(objs208multiarray[5]);
        //pub208.publish(objs208[0][0]);


        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
