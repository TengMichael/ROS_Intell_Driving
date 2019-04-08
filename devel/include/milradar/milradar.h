#ifndef MILRADAR_H
#define MILRADAR_H

#include <math.h>
#include <canbus/candata_multi.h>
#include <milradar/obj208.h>
#include <milradar/obj208_multi.h>
#include <milradar/obj408.h>
#include <milradar/obj408_multi.h>

#define Object_408Num 100
#define Object_208Num 25
#define Sensors_208Num 6
#define RCS_threshold 0 //dBm^2
#define ProbOfExist_threshold 1 //0x01:<25%;0x02:<50%;
#define Lifetime_threshold 1 //s
#define DistX_threshold 5//2.5m for 20hz, 5m for 10hz
#define DistY_threshold 5
#define VrelX_threshold 2//1m/s for 20hz, 2m/s for 10hz
#define VrelY_threshold 2

namespace Radar408 {
milradar::obj408 objs408[Object_408Num]={};
uint8_t Obj408_ID_Total=0;
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
    memcpy(&(objs408),&(objs408_temp),sizeof(objs408_temp));
}
/**********data preprocessing for the radar 408 by comparing two times sampling values************/
void Radar408_dataprocess2(void){
    uint8_t k=0;
    static uint8_t Obj408_ID_Total_last=0;
    static milradar::obj408 objs408_last[Object_408Num]={};
    milradar::obj408 objs408_temp[Object_408Num]={};

    for(uint8_t i=0;i<Obj408_ID_Total;i++){
        for(uint8_t j=0;j<Obj408_ID_Total_last;j++)
        {
            if((objs408[i].ID==objs408_last[j].ID)){
                if((fabs(objs408[i].DistX-objs408_last[j].DistX)<DistX_threshold)&&(fabs(objs408[i].DistY-objs408_last[j].DistY)<DistY_threshold)&&
                        (fabs(objs408[i].VrelX-objs408_last[j].VrelX)<VrelX_threshold)&&(fabs(objs408[i].VrelY-objs408_last[j].VrelY)<VrelY_threshold))
                {
                    memcpy(&(objs408_temp[k]),&(objs408[i]),sizeof(objs408[i]));
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
    memcpy(&(objs408_last),&(objs408),sizeof(objs408));
    memcpy(&(objs408),&(objs408_temp),sizeof(objs408_temp));
}
/*Coordinate exchange for 408radars*/
void Coordinate_Exc_408(float delta_x, float delta_y, float angle) {
    float px, py, vx, vy,ax,ay;
    for(uint8_t i=0;i<Obj408_ID_Total;i++){
        px = objs408[i].DistX;
        py = objs408[i].DistY;
        vx = objs408[i].VrelX;
        vy = objs408[i].VrelY;
        ax = objs408[i].ArelX;
        ay = objs408[i].ArelY;

        objs408[i].DistX = px*cos(angle) - py*sin(angle) + delta_x;//Euler rotation+Offset
        objs408[i].DistY = px*sin(angle) + py*cos(angle) + delta_y;
        objs408[i].VrelX= vx*cos(angle) - vy*sin(angle);//Euler rotation
        objs408[i].VrelY= vx*sin(angle) + vy*cos(angle);
        objs408[i].ArelX= ax*cos(angle) - ay*sin(angle);//Euler rotation
        objs408[i].ArelY= ax*sin(angle) + ay*cos(angle);
    }
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
    Radar408_dataprocess1();
    Radar408_dataprocess2();
    Coordinate_Exc_408(0,0,0);
}
}
/****************************************************************************/
namespace Radar208 {
milradar::obj208 objs208[2][Object_208Num]={};
uint8_t Obj208_ID_Total[2]={0};
/**********data preprocessing for the radar 408 by setting threshold************/
void Radar208_dataprocess1(void){
    uint8_t k=0;
    milradar::obj208 objs208_temp[2][Object_208Num]={};

    for(uint8_t j=0;j<2;j++){
        k=0;
        for(uint8_t i=0;i<Obj208_ID_Total[j];i++){
            if((objs208[j][i].RCS<=RCS_threshold)||(objs208[j][i].Lifetime<=Lifetime_threshold)||
                    (objs208[j][i].DistX<=0)||(objs208[j][i].DistY==0))
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
}
/**********data preprocessing for the radar 408 by comparing two times sampling values************/
void Radar208_dataprocess2(void){
    uint8_t k=0;
    static uint8_t ID_Total_last[2]={0};
    static milradar::obj208 objs208_last[2][Object_208Num]={};
    milradar::obj208 objs208_temp[2][Object_208Num]={};

    for(uint8_t s=0;s<2;s++){
        k=0;
        for(uint8_t i=0;i<Obj208_ID_Total[s];i++){
            for(uint8_t j=0;j<ID_Total_last[s];j++)
            {
                if((objs208[s][i].ID==objs208_last[s][j].ID)){
                    if((fabs(objs208[s][i].DistX-objs208_last[s][j].DistX)<DistX_threshold)&&(fabs(objs208[s][i].DistY-objs208_last[s][j].DistY)<DistY_threshold)&&
                            (fabs(objs208[s][i].VrelX-objs208_last[s][j].VrelX)<VrelX_threshold)&&(fabs(objs208[s][i].VrelY-objs208_last[s][j].VrelY)<VrelY_threshold))
                    {
                        memcpy(&(objs208_temp[s][k]),&(objs208[s][i]),sizeof(objs208[s][i]));
                        k++;
                    }
                    break;
                }
                else
                    continue;
            }
        }
        ID_Total_last[s]=Obj208_ID_Total[s];
        Obj208_ID_Total[s]=k;
    }
    memcpy(&(objs208_last),&(objs208),sizeof(objs208));
    memcpy(&(objs208),&(objs208_temp),sizeof(objs208_temp));
}
/*Coordinate exchange for 208radars*/
void Coordinate_Exc_208(uint8_t s, float delta_x, float delta_y, float angle) {
    float px, py, vx, vy;
    for(uint8_t i=0;i<Obj208_ID_Total[s];i++){
        px = objs208[s][i].DistX;
        py = objs208[s][i].DistY;
        vx = objs208[s][i].VrelX;
        vy = objs208[s][i].VrelY;

        objs208[s][i].DistX = px*cos(angle) - py*sin(angle) + delta_x;//Euler rotation+Offset
        objs208[s][i].DistY = px*sin(angle) + py*cos(angle) + delta_y;
        objs208[s][i].VrelX = vx*cos(angle) - vy*sin(angle);//Euler rotation
        objs208[s][i].VrelY = vx*sin(angle) + vy*cos(angle);
    }
}
/*Receive and analysis radar208 CAN data to objects information*/
void Radar208_extract(const canbus::candata_multi::ConstPtr& CanData,uint8_t s1,uint8_t s2){
    uint8_t Obj_index;
    uint8_t Data[8];
    uint8_t j=0;
    uint8_t sensor_num[2];
    sensor_num[0]=s1-1;
    sensor_num[1]=s2-1;
    memset(objs208,0,sizeof(objs208));
    memset(Obj208_ID_Total,0,sizeof(Obj208_ID_Total));
    for (uint16_t i = 0; i < CanData->frame.size(); i++) {
        memcpy(Data,&(CanData->frame[i].data),sizeof(CanData->frame[i].data));
        for(uint8_t s=0;s<2;s++){
            j=sensor_num[s];
            if (CanData->frame[i].id==(uint16_t)(0x61B+0x10*j)){
                Obj208_ID_Total[s]= Data[0];
            }
            else if (CanData->frame[i].id==(uint16_t)(0x61C+0x10*j)){
                Obj_index =Data[3]%32;
                //ROS_INFO("Obj_index: %d",Obj_index);
                objs208[s][Obj_index].index=Obj_index;
                objs208[s][Obj_index].ID = (uint16_t)Data[0]*256+Data[1];
                objs208[s][Obj_index].DistX = ((float)(Data[2] % 64) *8 + Data[3]/32)*0.1;
                objs208[s][Obj_index].DistY = ((float)Data[4] * 4 + Data[5] / 64)*0.1-51.1;
                objs208[s][Obj_index].VrelX = ((float)(Data[5] % 64)*64 + Data[6] / 4)*0.02 - 35;
                objs208[s][Obj_index].VrelY = (float)Data[7] *0.25 -32;
            }
            else if (CanData->frame[i].id==(uint16_t)(0x61D+0x10*j)){
                Obj_index = Data[3]%32;
                objs208[s][Obj_index].RCS = (float)Data[0]*0.5-50;
                objs208[s][Obj_index].Lifetime = (float)(Data[1]*256+Data[2])*0.1;
            }
            else{}
        }
    }
    Radar208_dataprocess1();
    Radar208_dataprocess2();
    if((s1==1)&&(s2==2)){
        Coordinate_Exc_208(0,0,0,0);
        Coordinate_Exc_208(1,0,0,0);
    }
    else if((s1==3)&&(s2==5)){
        Coordinate_Exc_208(0,0,0,0);
        Coordinate_Exc_208(1,0,0,0);
    }
    else if((s1==4)&&(s2==6)){
        Coordinate_Exc_208(0,0,0,0);
        Coordinate_Exc_208(1,0,0,0);
    }
    else{}
}
}


#endif // MILRADAR_H
