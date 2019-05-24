#include "global.h"
#include "ros/ros.h"

extern int randnum(int num);

void mobileye_lane(const mobileye::mobileye_Lane msg){
  //memcpy(&(Lane),&(msg),sizeof(msg));
  lane_test.left.C0=msg.Left_Dist;
  lane_test.right.C0=msg.Right_Dist;
  lane_test.left.C1=msg.Heading;
  lane_test.right.C1=msg.Heading;
  lane_test.left.C2=msg.Curvature;
  lane_test.right.C2=msg.Curvature;
  lane_test.left.lane_line_type=msg.Left_Type;
  lane_test.right.lane_line_type=msg.Right_Type;
}

void obs_handle(const kf_radar_mobileye::radar_mobileye_data_multi msg){
  //memcpy(&(Lane),&(msg),sizeof(msg));
  obs_info.clear();
  int num=msg.objs.size();
  for(uint8_t i=0;i<num;i++){
    timestamp=msg.objs[i].timestamp;
    int z_temp = msg.objs[i].fusion_DistX;
    int x_temp = msg.objs[i].fusion_DistY;
    int vz_temp = msg.objs[i].fusion_VrelX;
    int vx_temp = msg.objs[i].fusion_VrelY;
    int type = 1;
    int width = 2;
    int height = 2;
    obstacle obs_temp = obstacle((double)z_temp, (double)x_temp,
                                 (double)vz_temp, (double)vx_temp, width, height, type);
    obs_info.insert(obs_info.begin() + i, obs_temp);
  }
}

//class SubscribeAndPublish
//{
//public:
//  SubscribeAndPublish()
//  {
//    ros::Publisher pub_planning = nh.advertise<decision_planning::traj_point_data_multi>("traj_point_data_multi", 1000);
//    ros::Subscriber sub0 = nh.subscribe("radar_mobileye_kf", 1000, &SubscribeAndPublish::obs_handle,this);
//    ros::Subscriber sub1 = nh.subscribe("mobileye_Lane", 1000, &SubscribeAndPublish::mobileye_lane,this);
//  }

//  void mobileye_lane(const mobileye::mobileye_Lane msg){
//    //memcpy(&(Lane),&(msg),sizeof(msg));
//    lane_test.left.C0=msg.Left_Dist;
//    lane_test.right.C0=msg.Right_Dist;
//    lane_test.left.C1=msg.Heading;
//    lane_test.right.C1=msg.Heading;
//    lane_test.left.C2=msg.Curvature;
//    lane_test.right.C2=msg.Curvature;
//    lane_test.left.lane_line_type=msg.Left_Type;
//    lane_test.right.lane_line_type=msg.Right_Type;
////    //send ROS message to control module
////    decision_planning::traj_point_data_multi msg1;
////    for(uint8_t i=0;i<out_path.size();i++){
////      msg1.objs.push_back(traj_temp[i]);
////    }
////    pub_planning.publish(msg1);
//  }

//  void obs_handle(const kf_radar_mobileye::radar_mobileye_data_multi msg){
//    //memcpy(&(Lane),&(msg),sizeof(msg));
//    obs_info.clear();
//    int num=msg.objs.size();
//    timestamp=msg.objs[0].timestamp;
//    for(uint8_t i=0;i<num;i++){
//      int z_temp = msg.objs[i].fusion_DistX;
//      int x_temp = msg.objs[i].fusion_DistY;
//      int vz_temp = msg.objs[i].fusion_VrelX;
//      int vx_temp = msg.objs[i].fusion_VrelY;
//      int type = 1;
//      int width = 2;
//      int height = 2;
//      obstacle obs_temp = obstacle((double)z_temp, (double)x_temp,
//                                   (double)vz_temp, (double)vx_temp, width, height, type);
//      obs_info.insert(obs_info.begin() + i, obs_temp);
//    }
//  }

//private:
//  ros::NodeHandle nh;
//  ros::Publisher pub_planning;
//  ros::Subscriber sub0;
//  ros::Subscriber sub1;
//};//End of class SubscribeAndPublish





int main(int argc, char *argv[])
{
  ros::init(argc, argv, "decision_planning");
  ros::NodeHandle nh;
  ros::Subscriber sub0 = nh.subscribe("radar_mobileye_kf", 1000, obs_handle);
  ros::Subscriber sub1 = nh.subscribe("mobileye_Lane", 1000, mobileye_lane);

  ros::Publisher pub_control = nh.advertise<decision_planning::traj_point_data_multi>("traj_point_data_multi", 1000);

  ros::Rate loop_rate(1);

  QApplication a(argc, argv);


  // window
  MainWindow w;
  w.show();//决策规划的主函数就写在mainwindow里面
  //w.repaint();
  //w.update();
  a.exec();

  while (ros::ok())
  {//其实这个while没有用
    ros::spinOnce();
    loop_rate.sleep();
    //send ROS message to control module
//    decision_planning::traj_point_data_multi msg;
//    for(uint8_t i=0;i<out_path.size();i++){
//      msg.objs.push_back(traj_temp[i]);
//    }
//    pub_planning.publish(msg);
  }
  return 0;
}
