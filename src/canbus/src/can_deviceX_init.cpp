#include <ros/ros.h>
#include <canbus/controlcan.h>

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
int main(int argc, char **argv)
{
  ros::init(argc, argv, "can_deviceX_init");
  ros::NodeHandle nh;
  if(CAN_Init(argv[1][0]-48)==1)
    ROS_INFO("can_device%s_init succuss!",argv[1]);
  else
    ROS_INFO("can_device%s_init fail!",argv[1]);
}
