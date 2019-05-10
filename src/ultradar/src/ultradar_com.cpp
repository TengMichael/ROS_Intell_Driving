#include "ros/ros.h"
#include <serial/serial.h>
#include <std_msgs/String.h>
#include "std_msgs/UInt16MultiArray.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;

#define load_width 600
#define load_length 600
#define car_width 300
#define car_length 400

void ultradar_display(std_msgs::UInt16MultiArray serial_data){
  char window[] = "ultradar";
  Mat image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(image, Rect(load_width/2-car_width/2,load_length/2-car_length/2,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  char ch[10];String str;double font=0.5;
  sprintf(ch,"%d",serial_data.data[0]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2+car_width/2+10,load_length/2+car_length/2-car_length/6),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);
  sprintf(ch,"%d",serial_data.data[2]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2+car_width/2+10,load_length/2),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);
  sprintf(ch,"%d",serial_data.data[8]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2+car_width/2+10,load_length/2-car_length/2+car_length/6),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);

  sprintf(ch,"%d",serial_data.data[3]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2-car_width/2-80,load_length/2+car_length/2-car_length/6),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);
  sprintf(ch,"%d",serial_data.data[6]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2-car_width/2-80,load_length/2),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);
  sprintf(ch,"%d",serial_data.data[10]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2-car_width/2-80,load_length/2-car_length/2+car_length/6),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);

  sprintf(ch,"%d",serial_data.data[5]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2-car_width/2+car_width/6,load_length/2+car_length/2+20),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);
  sprintf(ch,"%d",serial_data.data[4]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2,load_length/2+car_length/2+20),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);
  sprintf(ch,"%d",serial_data.data[1]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2+car_width/2-car_width/6,load_length/2+car_length/2+20),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);

  sprintf(ch,"%d",serial_data.data[9]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2-car_width/4,load_length/2-car_length/2-10),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);
  sprintf(ch,"%d",serial_data.data[7]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2+car_width/4,load_length/2-car_length/2-10),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);

  sprintf(ch,"%d",serial_data.data[11]);str=ch;str+="mm";
  putText(image,str.c_str(),Point(load_width/2,load_length/2-car_length/2-40),FONT_HERSHEY_COMPLEX,font,Scalar(0,0,255),1,8);

  imshow(window, image);
  //moveWindow(window, 100,200);
  waitKey(10);
}
int main (int argc, char** argv){
  ros::init(argc, argv, "ultradar_com");
  ros::NodeHandle n;

  ros::Publisher sensor_pub = n.advertise<std_msgs::UInt16MultiArray>("ultradar_data", 1000);
  serial::Serial ros_ser;
  try
  {
    ros_ser.setPort("/dev/ttyUSB0");
    ros_ser.setBaudrate(9600);
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
  while(ros::ok()){
    ros::spinOnce();
    //ROS_INFO("Reading from serial port");
    std_msgs::UInt16MultiArray serial_data;
    uint8_t command[3]={0xe8,0x02,0x16};
    uint8_t arr[2];
    for(uint8_t i=0;i<12;i++){
      command[2]=0x16+i*0x08;
      ros_ser.write(command,3);
      usleep(100);
      ros_ser.read(arr,2);
      serial_data.data.push_back((uint16_t)arr[0]*256+arr[1]);
      ROS_INFO("Read ch%d: %d",i,serial_data.data[i]);
    }
    ultradar_display(serial_data);
    sensor_pub.publish(serial_data);
    loop_rate.sleep();
  }
}
