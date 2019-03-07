#include "ros/ros.h"
//#include "std_msgs/String.h"
#include <canbus/controlcan.h>
#include <canbus/candata.h>
#include <canbus/candata_multi.h>
#include <sstream>
#include <boost/bind.hpp>

void chatterCallback(const canbus::candata_multi::ConstPtr& msg,UINT8 DevInd,UINT8 CanNum)
{
  UINT16 Num=msg->frame.size();
  VCI_CAN_OBJ CanData[CAN_BuffMax]={0};
  for(uint8_t i=0;i<Num;i++){
    //boost::array<uint8_t, 8> arr=msg->frame[i].data;//fixed length array, need to use boost::array
    //CanData[i].ID=msg->frame[i].id;
    memcpy(&(CanData[i].ID),&(msg->frame[i].id),sizeof(msg->frame[i].id));
    memcpy(&(CanData[i].Data),&(msg->frame[i].data),sizeof(msg->frame[i].data));
    ROS_INFO("I heard: %x", CanData[i].ID);
    ROS_INFO("I heard: %d", CanData[i].Data[0]);
    ROS_INFO("I heard: %d", CanData[i].Data[7]);
  }
  ROS_INFO("DevInd: %d",DevInd);
  ROS_INFO("CanNum: %d",CanNum);
  ROS_INFO("Num: %d",Num);
  int16_t testnum;
  testnum=VCI_Transmit(DevType, DevInd, CanNum, CanData, Num);
  ROS_INFO("testnum: %d",testnum);
  if(testnum<0)
    ROS_INFO("Transmit error!\n");
  else
    ROS_INFO("Transmit OK!\n");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "can_deviceX_canX_send");
  ros::NodeHandle nh;

  std::stringstream ss;
  ss << "can_device" << argv[1]<<"_can"<<argv[2]<<"_send_chatter";
  ROS_INFO("%s", ss.str().c_str());

  UINT8 DevInd,CanNum;//need to change

  DevInd=argv[1][0]-48;//from str to dec
  CanNum=argv[2][0]-48;//from str to dec
  //VCI_OpenDevice(DevType, DevInd, 0);//necesssary for UABCAN2!

  ros::Subscriber sub = nh.subscribe<canbus::candata_multi> (ss.str().c_str(), 2000, boost::bind(&chatterCallback,_1,DevInd,CanNum));

  ros::spin();

  return 0;
}
