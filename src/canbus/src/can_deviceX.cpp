#include "ros/ros.h"
#include <canbus/controlcan.h>
#include <canbus/candata.h>
#include <canbus/candata_multi.h>
#include <sstream>

UINT8 CAN_Init(UINT8 DevInd) {

  VCI_INIT_CONFIG initconfig;
  initconfig.AccCode = 0x00000000;
  initconfig.AccMask = 0xffffffff;
  initconfig.Filter = 0;
  initconfig.Timing0 = 0x00;//500kbps
  initconfig.Timing1 = 0x1c;
  initconfig.Mode = 0;

  if (VCI_OpenDevice(DevType, DevInd, 0)==1);
  else
    ROS_INFO("CAN Open error!\n");

  if (VCI_InitCAN(DevType, DevInd, Can1, &initconfig)==1){
    if (VCI_StartCAN(DevType, DevInd, Can1)==1){
      if (VCI_InitCAN(DevType, DevInd, Can2, &initconfig)==1){
        if (VCI_StartCAN(DevType, DevInd, Can2)==1){
          if(VCI_ClearBuffer(DevType, DevInd, Can1)&&VCI_ClearBuffer(DevType, DevInd, Can2)==1){
            return(1);
          }else
            ROS_INFO("ClearBuffer error!\n");
        }else
          ROS_INFO("CAN2 Start error!\n");
      }else
        ROS_INFO("CAN2 Init error!\n");
    }else
      ROS_INFO("CAN1 Start error!\n");
  }else
    ROS_INFO("CAN1 Init error!\n");
}
UINT16 CAN_Receive(VCI_CAN_OBJ *CanData,UINT8 DevInd,UINT8 CanNum, UINT16 Num){
  INT16 CAN_BuffNum=0;
  if (VCI_GetReceiveNum(DevType, DevInd, CanNum)) {
    CAN_BuffNum = VCI_Receive(DevType, DevInd, CanNum, CanData, Num, 0);
    if(CAN_BuffNum<0)ROS_INFO("Receive error!\n");
  }
  return CAN_BuffNum;
}
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
  if(VCI_Transmit(DevType, DevInd, CanNum, CanData, Num)<0)
    ROS_INFO("Transmit error!\n");
  else
    ROS_INFO("Transmit OK!\n");
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "can_deviceX");
  ros::NodeHandle nh;

  std::stringstream rec1,rec2;
  rec1 << "can_device" << argv[1]<<"_can1_receive";
  ROS_INFO("%s", rec1.str().c_str());
  ros::Publisher rec1_pub = nh.advertise<canbus::candata_multi>(rec1.str().c_str(), 1000);
  rec2 << "can_device" << argv[1]<<"_can2_receive";
  ROS_INFO("%s", rec2.str().c_str());
  ros::Publisher rec2_pub = nh.advertise<canbus::candata_multi>(rec2.str().c_str(), 1000);

  UINT8 DevInd;//need to change
  DevInd=argv[1][0]-48;//from str to dec
  UINT16 i, CAN_RecNum;
  VCI_CAN_OBJ CanData1[CAN_BuffMax]= {};
  VCI_CAN_OBJ CanData2[CAN_BuffMax]= {};
  if(CAN_Init(DevInd)==1)
    ROS_INFO("can_device%s_init succuss!",argv[1]);
  else
    ROS_INFO("can_device%s_init fail!",argv[1]);
  /*******************Subscribe specific message,and send through can1 or can2**********************/
  std::stringstream send1,send2;
  send1 << "can_device" << argv[1]<<"_can1_send";
  ROS_INFO("%s", send1.str().c_str());
  send2 << "can_device" << argv[1]<<"_can2_send";
  ROS_INFO("%s", send2.str().c_str());
  ros::Subscriber send1_sub = nh.subscribe<canbus::candata_multi> (send1.str().c_str(), 1000, boost::bind(&chatterCallback,_1,DevInd,Can1));
  ros::Subscriber send2_sub = nh.subscribe<canbus::candata_multi> (send2.str().c_str(), 1000, boost::bind(&chatterCallback,_1,DevInd,Can2));

  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    canbus::candata msg;
    canbus::candata_multi msg_multi1,msg_multi2;
    /**************CAN1 received data publish***************************/
    CAN_RecNum=CAN_Receive(CanData1,DevInd,Can1,CAN_BuffMax);
    //ROS_INFO("CAN_RecNum: %d",CAN_RecNum);
    for(i=0;i<CAN_RecNum;i++){
      msg.id=CanData1[i].ID;
      memcpy(&(msg.data),&(CanData1[i].Data),sizeof(CanData1[i].Data));
      msg_multi1.frame.push_back(msg);
      ROS_INFO("Rec ID: %x %d %d %d %d %d %d %d %d",msg.id,msg.data[0],msg.data[1]
          ,msg.data[2],msg.data[3],msg.data[4],msg.data[5],msg.data[6],msg.data[7]);
    }
    rec1_pub.publish(msg_multi1);
    /**************CAN2 received data publish***************************/
    CAN_RecNum=CAN_Receive(CanData2,DevInd,Can2,CAN_BuffMax);
    //ROS_INFO("CAN_RecNum: %d",CAN_RecNum);
    for(i=0;i<CAN_RecNum;i++){
      msg.id=CanData2[i].ID;
      memcpy(&(msg.data),&(CanData2[i].Data),sizeof(CanData2[i].Data));
      msg_multi2.frame.push_back(msg);
      ROS_INFO("Rec ID: %x %d %d %d %d %d %d %d %d",msg.id,msg.data[0],msg.data[1]
          ,msg.data[2],msg.data[3],msg.data[4],msg.data[5],msg.data[6],msg.data[7]);
    }
    rec2_pub.publish(msg_multi2);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
