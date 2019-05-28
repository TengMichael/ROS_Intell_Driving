#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <boost/regex.hpp>
#include <serial/serial.h>
#include <math.h>
#include <navi_posi/vehicle_posture.h>
#include <navi_posi/navi_info.h>
#include <global2local.h>
using namespace std;

static size_t downloadCallback(void *buffer, size_t sz, size_t nmemb, void *writer)
{
  string* psResponse = (string*) writer;
  size_t size = sz * nmemb;
  psResponse->append((char*) buffer, size);

  return sz * nmemb;
}
string degmin2deg(string degsec){
  string deg;
  float tem;
  char ch[20];
  strncpy(ch,degsec.c_str(),degsec.length()+1);
  sscanf(ch,"%f",&tem);
  tem=((tem/100)-(long)(tem/100))*10/6+(long)(tem/100);
  sprintf(ch,"%f",tem);
  deg=ch;
  return deg;

}
void extract_GPSdata(string strTmpStr,string *gps_coordinate,navi_posi::vehicle_posture *veh_pos){
  uint8_t i=0;
  /*************************gps**********************************/
  string str=strTmpStr;
  boost::regex r1(R"(GNRMC,\d+.\d+,A,-?\d+.\d+,N,-?\d+.\d+,E,-?\d+.\d+,-?\d+.\d+)");
  boost::regex r2(R"(-?\d+.\d+,N,-?\d+.\d+,E,-?\d+.\d+,-?\d+.\d+)");
  boost::regex r3(R"(-?\d+.\d+)");
  boost::smatch sm;
  string gps_str[4];
  if(boost::regex_search(str,sm,r1))
  {
    str=sm.str();
    //printf("%s\n", str.c_str());
    if(boost::regex_search(str, sm, r2))
    {
      str=sm.str();
      //printf("%s\n", str.c_str());
      while(boost::regex_search(str, sm, r3))
      {
        gps_str[i]=sm.str();
        //printf("%s\n", gps_str[i].c_str());
        i++;
        str=sm.suffix();
      }
    }
  }
  /************************vehicle posture************************************/
  i=0;
  str=strTmpStr;
  r1=(R"(GPATT,-?\d+.\d+,p,-?\d+.\d+,r,-?\d+.\d+,y)");
  r2=(R"(-?\d+.\d+)");
  string pos_str[3];
  char ch[20];
  if(boost::regex_search(str,sm,r1))
  {
    str=sm.str();
    //printf("%s\n", str.c_str());
    while(boost::regex_search(str, sm, r2))
    {
      pos_str[i]=sm.str();
      //printf("%s\n", pos_str[i].c_str());
      i++;
      str=sm.suffix();
    }
  }
  /************************vehicle posture************************************/
  *gps_coordinate=degmin2deg(gps_str[1])+","+degmin2deg(gps_str[0]);
  strncpy(ch,gps_str[2].c_str(),gps_str[2].length()+1);
  sscanf(ch,"%f",&(veh_pos->Speed));
  strncpy(ch,gps_str[3].c_str(),gps_str[3].length()+1);
  sscanf(ch,"%f",&(veh_pos->SpeedDirection));
  strncpy(ch,pos_str[0].c_str(),pos_str[0].length()+1);
  sscanf(ch,"%f",&(veh_pos->PitchAngle));
  strncpy(ch,pos_str[1].c_str(),pos_str[1].length()+1);
  sscanf(ch,"%f",&(veh_pos->RollAngle));
  strncpy(ch,pos_str[2].c_str(),pos_str[2].length()+1);
  sscanf(ch,"%f",&(veh_pos->YawAngle));
}
void extract_BDdata(string str,string *BD_coordinate,vec2d *BD_coords){
  uint8_t i=0;
  boost::regex r(R"(\d+.\d+)");
  boost::smatch sm;
  string BD_str[2];
  char ch[30];
  while(boost::regex_search(str, sm, r))
  {
    BD_str[i]=sm.str();
    i++;
    str=sm.suffix();
  }
  *BD_coordinate=BD_str[1]+","+BD_str[0];
  strncpy(ch,BD_str[0].c_str(),BD_str[0].length()+1);
  sscanf(ch,"%lf",&(BD_coords->lon));
  strncpy(ch,BD_str[1].c_str(),BD_str[1].length()+1);
  sscanf(ch,"%lf",&(BD_coords->lat));
}
void get_urldata(string strUrl,string *strTmpStr){
  *strTmpStr="";
  CURL *curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, strTmpStr);
  CURLcode res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  if (res != CURLE_OK)
  {
    *strTmpStr = "error";
  }
  //printf("strRsp is |%s|\n", (*strTmpStr).c_str());
}
void extract_navi_info(string str,navi_posi::navi_info *info){
  /*********************distance*****************************/
  boost::regex r(R"("distance":\d+,"duration":\d+,"direction":\d+,"turn":\d+)");
  boost::regex r1(R"(\d+)");
  boost::regex r2(R"("path":"(-?\d+.\d+,-?\d+.\d+(;)?)*")");
  boost::regex r3(R"(-?\d+.\d+)");
  boost::smatch sm;
  boost::smatch sm1;
  char ch[10];
  uint8_t i=0;
  uint32_t data[4];
  float fdata[100];
  string temp;
  if(boost::regex_search(str, sm, r))
  {
    /*****************distance/direction/turn**************************/
    temp=sm.str();
    //printf("strRsp is |%s|\n", temp.c_str());
    while(boost::regex_search(temp, sm1, r1))
    {
      strncpy(ch,sm1.str().c_str(),sm1.str().length()+1);
      sscanf(ch,"%d",&(data[i]));
      //printf("data %d\n", data[i]);
      i++;
      temp=sm1.suffix();
    }
    info->distance=data[0];
    info->direction=data[2];
    info->turn=data[3];
    /*****************RelX/RelY**************************/
    temp=sm.suffix();i=0;
    if(boost::regex_search(temp, sm, r2))
    {
      temp=sm.str();
      while(boost::regex_search(temp, sm1, r3))
      {
        strncpy(ch,sm1.str().c_str(),sm1.str().length()+1);
        sscanf(ch,"%f",&(fdata[i]));
        //printf("fdata %f\n", fdata[i]);
        if(i%2==0)info->RelX.push_back(fdata[i]);
        else info->RelY.push_back(fdata[i]);
        i++;
        temp=sm1.suffix();
      }
      /*****************Next RelX/RelY**************************/
      temp=sm.suffix();i=0;
      if(boost::regex_search(temp, sm1, r2))
      {
        temp=sm1.str();
        while(boost::regex_search(temp, sm1, r3))
        {
          strncpy(ch,sm1.str().c_str(),sm1.str().length()+1);
          sscanf(ch,"%f",&(fdata[i]));
          //printf("fdata %f\n", fdata[i]);
          if(i%2==0)info->Next_RelX.push_back(fdata[i]);
          else info->Next_RelY.push_back(fdata[i]);
          i++;
          temp=sm1.suffix();
        }
      }
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navi_position");
  ros::NodeHandle nh;
  ros::Publisher pub_veh_pos = nh.advertise<navi_posi::vehicle_posture>("vehicle_posture", 1000);
  ros::Publisher pub_navi_info = nh.advertise<navi_posi::navi_info>("navi_info", 1000);
  serial::Serial ros_ser;
  try
  {
    ros_ser.setPort("/dev/ttyUSB1");
    ros_ser.setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    ros_ser.setTimeout(to);
    ros_ser.open();
  }
  catch (serial::IOException& e)
  {
    ROS_ERROR("Unable to open port ");
    return -1;
  }
  if(ros_ser.isOpen()){
    ROS_INFO("Serial Port opened");
  }else{
    return -1;
  }

  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    /**************************get gps cooridinate and change to baidu cooridinate***************************************/
    string position_data;
    /*string position_data=R"($GNRMC,072124.80,A,3101.75505,N,12126.52014,E,0.03,0.000,100519,0.0,0,D*6B
                         $GNGGA,072124.80,3101.75505,N,12126.52014,E,2,10,0.88,8.600,M,9.900,M,3.80,0019*6C
                         $GNZDA,072124.80,10,05,2019,00,00*7C
                         $GPATT,-0.04,p,-0.06,r,0.000,y,20170425,s,002000425112333539343233,ID,1,INS,411,02,5,A,G,CAR,1,0.000*5E
                         $DEBUG,KIND,0,2,1,MEM,0,0,0.000,NEW,0,00,0.000*43
                         $GIRMC,072125.00,A,3101.75506,N,12126.52014,E,0.014,,100519,,,D*67
                         $GNRMC,072125.00,A,3101.75505,N,12126.52014,E,0.01,0.000,100519,0.0,0,D*60)";

    */ros_ser.read(position_data,10000);//read data from combined position module
    //printf("strRsp is |%s|\n", position_data.c_str());
    string gps_coordinate;
    navi_posi::vehicle_posture veh_pos;
    extract_GPSdata(position_data,&gps_coordinate,&veh_pos);
    printf("gps_coordinate %s\n", gps_coordinate.c_str());
    printf("veh_pos %f %f %f %f %f\n",veh_pos.Speed,veh_pos.SpeedDirection,veh_pos.PitchAngle,veh_pos.RollAngle,veh_pos.YawAngle);
    string strUrl = "http://api.map.baidu.com/geoconv/v1/?coords="+gps_coordinate+"&from=1&to=5&ak=eVGImzwg4qM0OpeRTlGtxrBSzkqwSiMG";//uU2bUqdqkaGO8CAosvNhyOPLgGBn1wdM
    string strTmpStr;
    get_urldata(strUrl,&strTmpStr);
    //printf("strRsp is |%s|\n", strTmpStr.c_str());
    string BD_coordinate;vec2d BD_coords;
    extract_BDdata(strTmpStr,&BD_coordinate,&BD_coords);
    printf("BD_coordinate %s\n", BD_coordinate.c_str());
    /*****************************get route planning information**********///sc 31.031728,121.433171/*************///sym 31.025422,121.43787///********
    strUrl = "http://api.map.baidu.com/directionlite/v1/driving?origin="+BD_coordinate+"&destination=31.03471,121.453651&ak=eVGImzwg4qM0OpeRTlGtxrBSzkqwSiMG";//121.433171,31.031728
    get_urldata(strUrl,&strTmpStr);
    //printf("strRsp is |%s|\n", strTmpStr.c_str());
    navi_posi::navi_info info,info_last;
    static uint8_t turn_last,turn_cnt;
    extract_navi_info(strTmpStr,&info);
    vec2d obj_coords;
    for(uint8_t i=0;i<info.RelX.size();i++){
      obj_coords.lon=info.RelX[i];
      obj_coords.lat=info.RelY[i];
      obj_coords=GPS_to_local_coordinate(BD_coords,obj_coords,veh_pos.YawAngle);
      info.RelX[i]=obj_coords.lat;
      info.RelY[i]=obj_coords.lon;
      printf("info[] %f,%f\n",info.RelX[i],info.RelY[i]);
    }
    for(uint8_t i=0;i<info.Next_RelX.size();i++){
      obj_coords.lon=info.Next_RelX[i];
      obj_coords.lat=info.Next_RelY[i];
      obj_coords=GPS_to_local_coordinate(BD_coords,obj_coords,veh_pos.YawAngle);
      info.Next_RelX[i]=obj_coords.lat;
      info.Next_RelY[i]=obj_coords.lon;
      printf("info Next[] %f,%f\n",info.Next_RelX[i],info.Next_RelY[i]);
    }
    info.BD_lon=BD_coords.lon;
    info.BD_lat=BD_coords.lat;
    if((info.turn!=turn_last)||(turn_cnt>=0&&info.newroad==1))
    {
      info.newroad=1;
      turn_cnt--;
    }
    else
    {
      info.newroad=0;
      turn_cnt++;
      if(turn_cnt>=5)turn_cnt=5;//send newroad state continuously at the approaching 5 periods
     }
    if(info.turn==0&&info.distance==0&&info.direction==0)
      pub_navi_info.publish(info_last);//do not update when can not get navigation information from the Baidu API
    else
      pub_navi_info.publish(info);
    info_last=info;//The ROS message can be valued directly
    turn_last=info.turn;
    pub_veh_pos.publish(veh_pos);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
