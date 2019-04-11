#include "ros/ros.h"
#include <serial/serial.h>
#include <std_msgs/String.h>
#include "std_msgs/UInt16MultiArray.h"
//回调函数
/*void callback(const std_msgs::String::ConstPtr& msg){
     ROS_INFO_STREAM("Write to serial port" << msg->data);
     serial::Serial ros_ser;
     ros_ser.write(msg->data);
 }*/
int main (int argc, char** argv){
     ros::init(argc, argv, "ultradar_com");
     ros::NodeHandle n;
     //订阅主题command
     //ros::Subscriber command_sub = n.subscribe("command", 1000, callback);
     //发布主题sensor
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
         //if(ros_ser.available()){
             ROS_INFO("Reading from serial port");
             std_msgs::UInt16MultiArray serial_data;
             //获取串口数据
             uint8_t command[3]={0xe8,0x02,0x16};
             uint8_t arr[2];
             for(uint8_t i=0;i<12;i++){
               command[2]=0x16+i*0x08;
               ros_ser.write(command,3);
               usleep(15);
               ros_ser.read(arr,2);
               serial_data.data.push_back((uint16_t)arr[0]*256+arr[1]);
               ROS_INFO("Read ch%d: %d",i,serial_data.data[i]);
             }
             //serial_data.data = ros_ser.read(ros_ser.available());
             //ROS_INFO_STREAM("Read: "<<serial_data.data);
             //将串口数据发布
             sensor_pub.publish(serial_data);
        // }
         loop_rate.sleep();
     }
 }
