#include "global.h"
#include "ros/ros.h"

extern int randnum(int num);

ros::Subscriber sub0;//obs
ros::Subscriber sub1;//lane
ros::Subscriber sub2;//navi
ros::Subscriber sub3;//ego vehicle info

ros::Publisher pub_planning;
ros::Publisher pub_decision;

void mobileye_lane(const mobileye::mobileye_Lane msg){
  //当前车道信息
  lane_test.left.C0=msg.Left_Dist;
  lane_test.right.C0=msg.Right_Dist;
  lane_test.left.C1=msg.Heading;
  lane_test.right.C1=msg.Heading;
  lane_test.left.C2=msg.Curvature;
  lane_test.right.C2=msg.Curvature;
  lane_test.left.lane_line_type=msg.Left_Type;
  lane_test.right.lane_line_type=msg.Right_Type;
  lane_test.left.valid=true;
  lane_test.right.valid=true;
  //没有发送相邻车道信息，是否需要补充?
  lane_test.next_left.valid=false;
  lane_test.next_right.valid=false;
//  //send ROS message to control module
//  decision_planning::traj_point_data_multi msg1;
//  for(uint8_t i=0;i<out_path.size();i++){
//    msg1.objs.push_back(traj_temp[i]);
//  }
//  pub_planning.publish(msg1);
//  //send ROS message (decision_result)
//  decision_planning::decision_result msg2;
//  msg2.upper_state=upper_state;
//  msg2.timestamp=timestamp;
//  msg2.E1=E1;
//  msg2.E2=E2;
//  msg2.lane_driving_C1=lane_driving_C1;
//  msg2.lane_driving_C2=lane_driving_C2;
//  msg2.lane_driving_C3=lane_driving_C3;
//  msg2.lane_driving_C4=lane_driving_C4;
//  msg2.lane_driving_E1=lane_driving_E1;
//  msg2.lane_driving_E2=lane_driving_E2;
//  msg2.lane_driving_F=lane_driving_F;
//  msg2.lane_driving_state=lane_driving_state;
//  msg2.upper_state=upper_state;
//  pub_decision.publish(msg2);
}

void obs_handle(const kalman::radar_mobileye_data_multi msg){
  obs_info.clear();
  int num=msg.objs.size();
  for(uint8_t i=0;i<num;i++){
    timestamp=msg.objs[i].timestamp;
    int z_temp = msg.objs[i].fusion_DistX-1;
    int x_temp = msg.objs[i].fusion_DistY;
    int vz_temp = msg.objs[i].fusion_VrelX+veh_test.cur_speed;
    int vx_temp = msg.objs[i].fusion_VrelY;
    int type = 1;
    int width = 2;
    int height = 2;
    obstacle obs_temp = obstacle((double)z_temp, (double)x_temp,
                                 (double)vz_temp, (double)vx_temp, width, height, type);
    obs_info.insert(obs_info.begin() + i, obs_temp);
  }
}

void navi_handle(const navi_posi::navi_info msg){
  //导航信息
  veh_test.lon=msg.BD_lon;//自车经度
  veh_test.lat=msg.BD_lat;//自车纬度
  navi_test.BD_lon=msg.BD_lon;//经度
  navi_test.BD_lat=msg.BD_lat;//纬度
  navi_test.distance_from_road_seg_end=msg.distance;//路段终点距离
  navi_test.direction_road=msg.direction;//路相对于北极的角度
  navi_test.turn=msg.turn;//转向信息
  cout<<"turn"<<msg.turn<<endl;
  if(msg.turn==1){
    navi_test.turn_for_intersection=0;//用于路口的转向信息-直行
  }
  else if(msg.turn==7){
    navi_test.turn_for_intersection=1;//用于路口的转向信息-左转
  }
  else if(msg.turn==3){
    navi_test.turn_for_intersection=2;//用于路口的转向信息-右转
  }
  navi_test.RelX.clear();//当前路段坐标点串x
  navi_test.RelY.clear();//当前路段坐标点串y
  int num=msg.RelX.size();
  for(uint8_t i=0;i<num;i++){
    navi_test.RelX.push_back(msg.RelX[i]);
    navi_test.RelY.push_back(msg.RelY[i]);
  }
  navi_test.newroad=msg.newroad;//是否进入新的道路，置1表示进入
  cout<<"distance_from_road_seg_end:"<<navi_test.distance_from_road_seg_end<<endl;
}

void veh_pos_handle(const mobileye::vehicle_info msg){
  //自车姿态
  veh_test.cur_speed=msg.Speed;
  veh_test.yaw_angle=msg.YawAngle;
  //cout<<"veh spd:"<<veh_test.cur_speed<<endl;
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
  sub0 = nh.subscribe("radar_mobileye_kf", 1000, obs_handle);
  sub1 = nh.subscribe("mobileye_Lane", 1000, mobileye_lane);
  sub2 = nh.subscribe("navi_info", 1000, navi_handle);
  sub3 = nh.subscribe("vehicle_info", 1000, veh_pos_handle);
  //sub3 = nh.subscribe("vehicle_posture", 1000, veh_pos_handle);

  pub_planning = nh.advertise<decision_planning::traj_point_data_multi>("traj_point_data_multi", 1000);
  pub_decision = nh.advertise<decision_planning::decision_result>("decision_result", 1000);

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
