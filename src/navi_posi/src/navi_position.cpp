#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <boost/regex.hpp>
using namespace std;

static size_t downloadCallback(void *buffer, size_t sz, size_t nmemb, void *writer)
{
  string* psResponse = (string*) writer;
  size_t size = sz * nmemb;
  psResponse->append((char*) buffer, size);

  return sz * nmemb;
}
void get_mapdata(string strUrl,string *strTmpStr){
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

  string strUrl = "http://api.map.baidu.com/directionlite/v1/driving?origin=31.03126,121.451869&destination=31.029497,121.451617&ak=uU2bUqdqkaGO8CAosvNhyOPLgGBn1wdM";
  string strTmpStr;
  get_mapdata(strUrl,&strTmpStr);
  printf("strRsp is |%s|\n", strTmpStr.c_str());
  string distance[10],direction[10],turn[10],path[10];
  extract_mapdata(strTmpStr,distance,direction,turn,path);
  printf("%s\n", path[0].c_str());

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std_msgs::String msg;
    msg.data = "hello world";

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
