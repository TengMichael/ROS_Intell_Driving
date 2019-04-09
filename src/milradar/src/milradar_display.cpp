#include "ros/ros.h"
#include "std_msgs/String.h"
#include <opencv2/opencv.hpp>
#include <milradar/obj208_multi.h>
#include <milradar/obj408_multi.h>
#include <sstream>
#include <mobileye/vehicle_info.h>

using namespace cv;

#define load_width 20*10
#define load_length 60*10
#define car_length 2*10
#define car_width 1*10
#define speed_threshold 3
mobileye::vehicle_info Carinfo;

void car_information(const mobileye::vehicle_info msg){
  Carinfo.Speed=msg.Speed;
}
void display208(const milradar::obj208_multi::ConstPtr& msg,uint8_t ch)
{
  uint8_t i=0;
  std::stringstream window;
  window<<"Objs208_sensor"<<(ch+10);
  Mat radar_image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(radar_image, Rect(load_width/2-car_width/2,load_length/2,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  line(radar_image, Point(load_width/4,0), Point(load_width/4,load_length),Scalar(0, 255, 255), 2, LINE_8);//left lane
  line(radar_image, Point(load_width/4*3,0), Point(load_width/4*3,load_length),Scalar(0, 255, 255), 2, LINE_8);//right lane
  for (i = 0; i < msg->objs.size(); i++) {
    if(fabs(msg->objs[i].VrelX+Carinfo.Speed)<=speed_threshold)
    rectangle(radar_image, Rect(load_width/2-msg->objs[i].DistY,load_length/2-msg->objs[i].DistX*2,4,4),
              Scalar(255,0,0),-1, LINE_8);//B G R
    else
    rectangle(radar_image, Rect(load_width/2-msg->objs[i].DistY,load_length/2-msg->objs[i].DistX*2,4,4),
              Scalar(0,0,255),-1, LINE_8);
  }
  imshow(window.str(), radar_image);
  moveWindow(window.str(),50+load_width*(ch-1),0);
  waitKey(10);
}

void display408(const milradar::obj408_multi::ConstPtr& msg)
{
  uint8_t i=0;
  char window[] = "Objs408";
  Mat radar_image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(radar_image, Rect(load_width/2-car_width/2,load_length/2,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  line(radar_image, Point(load_width/4,0), Point(load_width/4,load_length),Scalar(0, 255, 255), 2, LINE_8);//left lane
  line(radar_image, Point(load_width/4*3,0), Point(load_width/4*3,load_length),Scalar(0, 255, 255), 2, LINE_8);//right lane
  for (i = 0; i < msg->objs.size(); i++) {
    if(fabs(msg->objs[i].VrelX+Carinfo.Speed)<=speed_threshold)
    rectangle(radar_image, Rect(load_width/2-msg->objs[i].DistY,load_length/2-msg->objs[i].DistX*2,4,4),
              Scalar(255,0,0),-1, LINE_8);//B G R
    else
    rectangle(radar_image, Rect(load_width/2-msg->objs[i].DistY,load_length/2-msg->objs[i].DistX*2,4,4),
              Scalar(0,0,255),-1, LINE_8);
  }
  imshow(window, radar_image);
  //moveWindow(window,load_width*(ch-1),0);
  waitKey(10);
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "milradar_display");
  ros::NodeHandle nh;


  ros::Subscriber sub1 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_1", 1000, boost::bind(&display208,_1,1));
  ros::Subscriber sub2 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_2", 1000, boost::bind(&display208,_1,2));
  ros::Subscriber sub3 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_3", 1000, boost::bind(&display208,_1,3));
  ros::Subscriber sub4 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_4", 1000, boost::bind(&display208,_1,4));
  ros::Subscriber sub5 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_5", 1000, boost::bind(&display208,_1,5));
  ros::Subscriber sub6 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_6", 1000, boost::bind(&display208,_1,6));

  ros::Subscriber sub7 = nh.subscribe<mobileye::vehicle_info>("vehicle_info", 1000, car_information);

  ros::Subscriber sub0 = nh.subscribe("milradar_obj408", 1000, display408);


  ros::spin();

  return 0;
}
