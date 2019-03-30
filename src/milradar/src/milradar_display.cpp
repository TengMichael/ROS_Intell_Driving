#include "ros/ros.h"
#include "std_msgs/String.h"
#include <opencv2/opencv.hpp>
#include <milradar/obj208_multi.h>
#include <milradar/obj408_multi.h>
#include <sstream>

using namespace cv;

#define Win_height 200
#define Win_width 400

void display208(const milradar::obj208_multi::ConstPtr& msg,uint8_t ch)
{
  uint8_t i=0;
  std::stringstream objects_window;
  objects_window<<"Objs208_sensor"<<(ch+10);
  Mat objects_image = Mat(Win_height, Win_width, CV_8UC3, Scalar(205, 205, 205));
  line(objects_image, Point(0, Win_height / 2 - 50), Point(Win_width, Win_height / 2 - 50),Scalar(0, 255, 255), 2, LINE_8);//left lane
  line(objects_image, Point(0, Win_height / 2 + 50), Point(Win_width, Win_height / 2 + 50),Scalar(0, 255, 255), 2, LINE_8);//right lane
  for (i = 0; i < msg->objs.size(); i++) {
    if ((msg->objs[i].DistX != 0)&&(msg->objs[i].RCS>= 0))
    {
      rectangle(objects_image, Rect(msg->objs[i].DistX*2, msg->objs[i].DistY*2+ Win_height / 2, 4, 4),
                Scalar(0, 0, 255),//B G R
                -1, LINE_8);
    }
  }
  imshow(objects_window.str(), objects_image);
  moveWindow(objects_window.str(), Win_width*((ch-1)%2),Win_height*((ch-1)/2));
  waitKey(10);
}

void display408(const milradar::obj408_multi::ConstPtr& msg)
{
  uint8_t i=0;
  char objects_window[] = "Objs408";
  Mat objects_image = Mat(Win_height, Win_width, CV_8UC3, Scalar(205, 205, 205));
  line(objects_image, Point(0, Win_height / 2 - 50), Point(Win_width, Win_height / 2 - 50),Scalar(0, 255, 255), 2, LINE_8);//left lane
  line(objects_image, Point(0, Win_height / 2 + 50), Point(Win_width, Win_height / 2 + 50),Scalar(0, 255, 255), 2, LINE_8);//right lane
  for ( i = 0; i < msg->objs.size(); i++) {
    rectangle(objects_image, Rect(msg->objs[i].DistX*2, msg->objs[i].DistY*2+ Win_height / 2, 4, 4),
              Scalar(255, 0, 0),//B G R
              -1, LINE_8);
  }
  imshow(objects_window, objects_image);
  //moveWindow(objects_window, 100, 200);
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

  ros::Subscriber sub0 = nh.subscribe("milradar_obj408", 1000, display408);
  ros::spin();

  return 0;
}
