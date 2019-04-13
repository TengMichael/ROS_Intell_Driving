#include "ros/ros.h"
#include <fusion.h>

milradar::obj408 objs408[Object_408Num]={};
milradar::obj208 objs208[Sensors_208Num][Object_208Num]={};
mobileye::mobileye_Obstacle Obstacle[Obstacle_Num]={};
fusion::fusion_obj fobjs[Obstacle_Num]={};
kf_radar_mobileye::radar_mobileye_data rmobjs[Obstacle_Num]={};

uint8_t Obj408_ID_Total=0;
uint8_t mobileye_ID_Total=0;

void mobileye_obstacles(const mobileye::mobileye_Obstacle_multi msg)
{
  memset(Obstacle,0,sizeof(Obstacle));
  mobileye_ID_Total=msg.Obstacles.size();
  for(uint8_t i=0;i<mobileye_ID_Total;i++)
  memcpy(&(Obstacle[i]),&(msg.Obstacles[i]),sizeof(msg.Obstacles[i]));
}
void sensor408(const milradar::obj408_multi msg)
{
  memset(objs408,0,sizeof(objs408));
  Obj408_ID_Total=msg.objs.size();
  for(uint8_t i=0;i<Obj408_ID_Total;i++)
  memcpy(&(objs408[i]),&(msg.objs[i]),sizeof(msg.objs[i]));
}
void sensor208(const milradar::obj208_multi::ConstPtr& msg,uint8_t ch)
{
  memcpy(&(objs208[ch-1]),&(msg),sizeof(msg));
}
void fusion_radar_mobileye(){
  uint8_t j_min=0;
  double dist_max=100000;
  VectorXd x(4);
  MatrixXd S(4,4);
  S << 1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 2, 0,
      0, 0, 0, 2;
  MatrixXd Si = S.inverse();
  memset(rmobjs,0,sizeof(rmobjs));
  for(uint8_t i=0;i<mobileye_ID_Total;i++){
    for(uint8_t j=0;j<Obj408_ID_Total;j++){
      x(0)=Obstacle[i].PosX-objs408[j].DistX;
      x(1)=Obstacle[i].PosY-objs408[j].DistY;
      x(2)=Obstacle[i].VrelX-objs408[j].VrelX;
      x(3)=Obstacle[i].ArelX-objs408[j].ArelX;
      MatrixXd xt =x.transpose();
      MatrixXd dist=xt*Si*x;
      if(dist(0)<dist_max){
        dist_max=dist(0);
        j_min=j;
      }
    }
    rmobjs[i].mobileye_DistX=Obstacle[i].PosX;
    rmobjs[i].mobileye_DistY=Obstacle[i].PosY;
    rmobjs[i].mobileye_VrelX=Obstacle[i].VrelX;
    rmobjs[i].mobileye_ArelX=Obstacle[i].ArelX;
    rmobjs[i].radar_DistX=objs408[j_min].DistX;
    rmobjs[i].radar_DistY=objs408[j_min].DistY;
    rmobjs[i].radar_VrelX=objs408[j_min].VrelX;
    rmobjs[i].radar_VrelY=objs408[j_min].VrelY;
    rmobjs[i].radar_ArelX=objs408[j_min].ArelX;
    rmobjs[i].radar_ArelY=objs408[j_min].ArelY;
  }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "fusion");
  ros::NodeHandle nh;

  ros::Subscriber sub0 = nh.subscribe("milradar_obj408", 1000, sensor408);
  /*ros::Subscriber sub1 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_1", 1000, boost::bind(&sensor208,_1,1));
  ros::Subscriber sub2 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_2", 1000, boost::bind(&sensor208,_1,2));
  ros::Subscriber sub3 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_3", 1000, boost::bind(&sensor208,_1,3));
  ros::Subscriber sub4 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_4", 1000, boost::bind(&sensor208,_1,4));
  ros::Subscriber sub5 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_5", 1000, boost::bind(&sensor208,_1,5));
  ros::Subscriber sub6 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_6", 1000, boost::bind(&sensor208,_1,6));
  */
  ros::Subscriber sub7 = nh.subscribe("mobileye_Obstacle", 1000, mobileye_obstacles);
  //ros::Subscriber sub7 = nh.subscribe<mobileye::vehicle_info>("vehicle_info", 1000, car_information);

  ros::Publisher chatter_pub = nh.advertise<kf_radar_mobileye::radar_mobileye_data_multi>("radar_mobileye_data_multi", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    kf_radar_mobileye::radar_mobileye_data_multi msg;
    fusion_radar_mobileye();
    for(uint8_t i=0;i<mobileye_ID_Total;i++){
      msg.objs.push_back(rmobjs[i]);
      rmobjs[i].timestamp=rmobjs[i].timestamp+100;
    }
    chatter_pub.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
