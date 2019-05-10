#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <boost/regex.hpp>
#include <serial/serial.h>
#include <math.h>
using namespace std;

static size_t downloadCallback(void *buffer, size_t sz, size_t nmemb, void *writer)
{
  string* psResponse = (string*) writer;
  size_t size = sz * nmemb;
  psResponse->append((char*) buffer, size);

  return sz * nmemb;
}
string degsec2deg(string degsec){
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
void extract_GPSdata(string str,string *gps_coordinate){
  uint8_t i=0;
  boost::regex r1(R"(GNGGA,\d*.\d*,\d*.\d*,N,\d*.\d*,E)");
  boost::regex r2(R"(\d*.\d*,N,\d*.\d*,E)");
  boost::regex r3(R"(\d+.\d+)");
  boost::smatch sm;
  string gps_str[2];
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
  *gps_coordinate=degsec2deg(gps_str[1])+","+degsec2deg(gps_str[0]);
}
void extract_BDdata(string str,string *BD_coordinate){
  uint8_t i=0;
  boost::regex r(R"(\d+.\d+)");
  boost::smatch sm;
  string BD_str[2];
  while(boost::regex_search(str, sm, r))
  {
    BD_str[i]=sm.str();
    i++;
    str=sm.suffix();
  }
  *BD_coordinate=BD_str[1]+","+BD_str[0];
}
void get_urldata(string strUrl,string *strTmpStr){
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

void extract_mapdata(string strTmpStr,string distance[],string direction[],string turn[],string path[]){
  uint8_t i=0;
  string str=strTmpStr;
  /*********************distance*****************************/
  boost::regex r(R"("distance":\d*)");
  boost::smatch sm;
  while(boost::regex_search(str, sm, r))
  {
    distance[i]=sm.str();
    printf("%s\n", distance[i].c_str());
    i++;
    str=sm.suffix();
  }
  /*********************direction*****************************/
  str=strTmpStr;i=0;
  r=R"("direction":\d*)";
  while(boost::regex_search(str, sm, r))
  {
    direction[i]=sm.str();
    printf("%s\n", direction[i].c_str());
    i++;
    str=sm.suffix();
  }
  /*********************turn*****************************/
  str=strTmpStr;i=0;
  r=R"("turn":\d*)";
  while(boost::regex_search(str, sm, r))
  {
    turn[i]=sm.str();
    printf("%s\n", turn[i].c_str());
    i++;
    str=sm.suffix();
  }
  /**********************path****************************/
  str=strTmpStr;i=0;
  r=R"("path":"(\d*.\d*,\d*.\d*(;)?)*")";
  while(boost::regex_search(str, sm, r))
  {
    path[i]=sm.str();
    printf("%s\n", path[i].c_str());
    i++;
    str=sm.suffix();
  }
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "navi_position");
  ros::NodeHandle nh;
  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

  /*serial::Serial ros_ser;
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
  }*/

  ros::Rate loop_rate(5);
  while (ros::ok())
  {
   /**************************get gps cooridinate and change to baidu cooridinate***************************************/
    string position_data=R"($GNRMC,072124.80,A,3101.75505,N,12126.52014,E,0.03,0.000,100519,0.0,0,D*6B
                         $GNGGA,072124.80,3101.75505,N,12126.52014,E,2,10,0.88,8.600,M,9.900,M,3.80,0019*6C
                         $GNZDA,072124.80,10,05,2019,00,00*7C
                         $GPATT,-0.04,p,-0.06,r,0.000,y,20170425,s,002000425112333539343233,ID,1,INS,411,02,5,A,G,CAR,1,0.000*5E
                         $DEBUG,KIND,0,2,1,MEM,0,0,0.000,NEW,0,00,0.000*43
                         $GIRMC,072125.00,A,3101.75506,N,12126.52014,E,0.014,,100519,,,D*67
                         $GNRMC,072125.00,A,3101.75505,N,12126.52014,E,0.01,0.000,100519,0.0,0,D*60)";
    //ros_ser.read(position_data,1);//read data from combined position module
    string gps_coordinate;
    extract_GPSdata(position_data,&gps_coordinate);
    printf("%s\n", gps_coordinate.c_str());
    string strUrl = "http://api.map.baidu.com/geoconv/v1/?coords="+gps_coordinate+"&from=1&to=5&ak=uU2bUqdqkaGO8CAosvNhyOPLgGBn1wdM";
    string strTmpStr;
    get_urldata(strUrl,&strTmpStr);
    printf("strRsp is |%s|\n", strTmpStr.c_str());
    string BD_coordinate;
    extract_BDdata(strTmpStr,&BD_coordinate);
    printf("%s\n", BD_coordinate.c_str());
/*****************************get route planning information***********************************/
    strUrl = "http://api.map.baidu.com/directionlite/v1/driving?origin="+BD_coordinate+"&destination=31.029497,121.451617&ak=uU2bUqdqkaGO8CAosvNhyOPLgGBn1wdM";
    strTmpStr;
    get_urldata(strUrl,&strTmpStr);
    printf("strRsp is |%s|\n", strTmpStr.c_str());
    string distance[10],direction[10],turn[10],path[10];
    extract_mapdata(strTmpStr,distance,direction,turn,path);
    //printf("%s\n", path[0].c_str());

    //chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
