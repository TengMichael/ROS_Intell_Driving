#include "ros/ros.h"
#include <fusion.h>
#include <opencv2/opencv.hpp>

milradar::obj408 objs408[Object_408Num]={};
milradar::obj208 objs208[Sensors_208Num][Object_208Num]={};
mobileye::mobileye_Obstacle Obstacle[Obstacle_Num]={};
fusion::fusion_obj fobjs[Obstacle_Num]={};
kf_radar_mobileye::radar_mobileye_data rmobjs[Obstacle_Num]={};
mobileye::mobileye_Lane Lane;
mobileye::vehicle_info Carinfo;

uint8_t Obj408_ID_Total=0;
uint8_t mobileye_ID_Total=0;
uint8_t Obj208_ID_Total[Sensors_208Num]={0};

using namespace cv;
#define load_width 80*10
#define load_length 100*10
#define car_length 2*10
#define car_width 1*10
#define speed_threshold 2

void fusion_display()
{
  char window[] = "fusion";
  Mat image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(image, Rect(load_width/2-car_width/2,load_length/2,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  for (uint8_t i = 0; i < Obj408_ID_Total; i++) {
    //if(fabs(objs408[i].VrelX+Carinfo.Speed)>=speed_threshold)
      rectangle(image, Rect(load_width/2-objs408[i].DistY,load_length/2-objs408[i].DistX*4,4,4),
                Scalar(0,0,255),-1, LINE_8);//B G R
  }
  for (uint8_t i = 0; i < Sensors_208Num; i++) {
    for (uint8_t j = 0; j < Obj208_ID_Total[i]; j++)
      if((i==0)||(i==4)){
        //if(fabs(objs208[i][j].VrelX+Carinfo.Speed)>=speed_threshold)
          rectangle(image, Rect(load_width/2-objs208[i][j].DistY,load_length/2-objs208[i][j].DistX*4,4,4),
                    Scalar(255,0,0),-1, LINE_8);
      }
      else if((i==1)||(i==5)){
        //if(fabs(objs208[i][j].VrelX+Carinfo.Speed)>=speed_threshold)
          rectangle(image, Rect(load_width/2-objs208[i][j].DistY,load_length/2-objs208[i][j].DistX*4,4,4),
                    Scalar(0,255,0),-1, LINE_8);
      }
      else if((i==2)||(i==3)){
        //if(fabs(objs208[i][j].VrelX+Carinfo.Speed)>=speed_threshold)
          rectangle(image, Rect(load_width/2-objs208[i][j].DistY,load_length/2-objs208[i][j].DistX*4,4,4),
                    Scalar(0,0,255),-1, LINE_8);
      }
  }

  float c0_left,c0_right,c1,c2;
  std::vector<Point> Left_Points;
  std::vector<Point> Right_Points;

  c1=Lane.Heading;
  c2=Lane.Curvature;
  c0_left=Lane.Left_Dist;
  c0_right=Lane.Right_Dist;

  if((Lane.Left_Conf!=0)||(Lane.Right_Conf!=0)){
    for(uint16_t i=0;i<load_length/2;i++){
      float x=i*0.1;
      float y1=(c0_left+c1*x+c2*pow(x,2))*10;
      float y2=(c0_right+c1*x+c2*pow(x,2))*10;
      Left_Points.push_back(Point((int16_t)y1+load_width/2,load_length/2-x*10));
      Right_Points.push_back(Point((int16_t)y2+load_width/2,load_length/2-x*10));
    }
  }
  line(image,Point(load_width/2,load_length),Point(load_width/2,0),Scalar(255, 0, 0),1,LINE_8,0);
  polylines(image,Left_Points,false,Scalar(0,255,255),2,LINE_8,0);
  polylines(image,Right_Points,false,Scalar(0,255,255),2,LINE_8,0);


  imshow(window, image);
  //moveWindow(window,load_width*(ch-1),0);
  waitKey(10);
}
void car_information(const mobileye::vehicle_info msg){
  Carinfo.Speed=msg.Speed;
}
void mobileye_lane(const mobileye::mobileye_Lane msg){
  memcpy(&(Lane),&(msg),sizeof(msg));
}
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
  memset(objs208[ch-1],0,sizeof(objs208[ch-1]));
  Obj208_ID_Total[ch-1]=msg->objs.size();
  for(uint8_t i=0;i<Obj208_ID_Total[ch-1];i++)
    memcpy(&(objs208[ch-1][i]),&(msg->objs[i]),sizeof(msg->objs[i]));
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
      if((fabs(Obstacle[i].PosX-objs408[j].DistX)<gate_X/2)&&(fabs(Obstacle[i].PosY-objs408[j].DistY)<gate_Y/2)){
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
    }

    rmobjs[i].mobileye_DistX=Obstacle[i].PosX;
    rmobjs[i].mobileye_DistY=Obstacle[i].PosY;
    rmobjs[i].mobileye_VrelX=Obstacle[i].VrelX;
    rmobjs[i].mobileye_ArelX=Obstacle[i].ArelX;
    if(dist_max==100000)
    {
      rmobjs[i].radar_DistX=Obstacle[i].PosX;
      rmobjs[i].radar_DistY=Obstacle[i].PosY;
      rmobjs[i].radar_VrelX=Obstacle[i].VrelX;
      rmobjs[i].radar_ArelX=Obstacle[i].ArelX;
    }
    else{
      rmobjs[i].ID=objs408[j_min].ID;
      rmobjs[i].radar_DistX=objs408[j_min].DistX;
      rmobjs[i].radar_DistY=objs408[j_min].DistY;
      rmobjs[i].radar_VrelX=objs408[j_min].VrelX;
      rmobjs[i].radar_VrelY=objs408[j_min].VrelY;
      rmobjs[i].radar_ArelX=objs408[j_min].ArelX;
      rmobjs[i].radar_ArelY=objs408[j_min].ArelY;
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "fusion");
  ros::NodeHandle nh;

  ros::Subscriber sub0 = nh.subscribe("milradar_obj408", 1000, sensor408);
  ros::Subscriber sub1 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_1", 1000, boost::bind(&sensor208,_1,1));
  ros::Subscriber sub2 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_2", 1000, boost::bind(&sensor208,_1,2));
  ros::Subscriber sub3 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_3", 1000, boost::bind(&sensor208,_1,3));
  ros::Subscriber sub4 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_4", 1000, boost::bind(&sensor208,_1,4));
  ros::Subscriber sub5 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_5", 1000, boost::bind(&sensor208,_1,5));
  ros::Subscriber sub6 = nh.subscribe<milradar::obj208_multi>("milradar_obj208_6", 1000, boost::bind(&sensor208,_1,6));

  ros::Subscriber sub7 = nh.subscribe("mobileye_Obstacle", 1000, mobileye_obstacles);
  ros::Subscriber sub8 = nh.subscribe("mobileye_Lane", 1000, mobileye_lane);
  ros::Subscriber sub9 = nh.subscribe<mobileye::vehicle_info>("vehicle_info", 1000, car_information);

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
    fusion_display();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
