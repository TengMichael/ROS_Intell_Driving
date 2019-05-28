#include "ros/ros.h"
#include <fusion.h>
#include <opencv2/opencv.hpp>
#include <fusion/fusion_milradar_obj.h>

milradar::obj408 objs408[Object_408Num]={};
milradar::obj208 objs208[Sensors_208Num][Object_208Num]={};
mobileye::mobileye_Obstacle Obstacle[Obstacle_Num]={};
fusion::fusion_obj fobjs[Obstacle_Num]={};
fusion::fusion_milradar_obj milradar_objs[Milradar_Object_Num]={};
kalman::radar_mobileye_data rmobjs[Obstacle_Num]={};
mobileye::mobileye_Lane Lane;
mobileye::vehicle_info Carinfo;

uint8_t Obj408_ID_Total=0;
uint16_t mobileye_ID_Total=0;
uint8_t Obj208_ID_Total[Sensors_208Num]={0};
uint8_t radar_ID_Total = 0;
uint8_t Invalid_ArelX = 0;
uint8_t Invalid_ArelY = 0;

using namespace cv;
#define load_width 80*10
#define load_length 100*10
#define car_length 2*10
#define car_width 1*10
#define speed_threshold 2
#define default_milradar208_Length 1
#define default_milradar208_Width 1

void fusion_display()
{
  char window[] = "fusion";
  Mat image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(image, Rect(load_width/2-car_width/2,load_length/2,car_width, car_length), Scalar(0,255,0),2,8,0);
  for (uint8_t i = 0; i < Obj408_ID_Total; i++) {
    //if(fabs(objs408[i].VrelX+Carinfo.Speed)>=speed_threshold)
    rectangle(image, Rect(load_width/2-objs408[i].DistY,load_length/2-objs408[i].DistX*4,4,4),
              Scalar(0,0,255),-1, 8);//B G R
  }
  for (uint8_t i = 0; i < Sensors_208Num; i++) {
    for (uint8_t j = 0; j < Obj208_ID_Total[i]; j++)
      if((i==0)||(i==4)){
        //if(fabs(objs208[i][j].VrelX+Carinfo.Speed)>=speed_threshold)
        rectangle(image, Rect(load_width/2-objs208[i][j].DistY,load_length/2-objs208[i][j].DistX*4,4,4),
                  Scalar(255,0,0),-1, 8);
      }
      else if((i==1)||(i==5)){
        //if(fabs(objs208[i][j].VrelX+Carinfo.Speed)>=speed_threshold)
        rectangle(image, Rect(load_width/2-objs208[i][j].DistY,load_length/2-objs208[i][j].DistX*4,4,4),
                  Scalar(0,255,0),-1, 8);
      }
      else if((i==2)||(i==3)){
        //if(fabs(objs208[i][j].VrelX+Carinfo.Speed)>=speed_threshold)
        rectangle(image, Rect(load_width/2-objs208[i][j].DistY,load_length/2-objs208[i][j].DistX*4,4,4),
                  Scalar(0,0,255),-1, 8);
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
  line(image,Point(load_width/2,load_length),Point(load_width/2,0),Scalar(255, 0, 0),1,8,0);
  polylines(image,Left_Points,false,Scalar(0,255,255),2,8,0);
  polylines(image,Right_Points,false,Scalar(0,255,255),2,8,0);


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
  // Initiation. Set the entire memory pointed by objs408 that contains data of last cycle to value 0
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

// fusion of radar208_1, radar208_2 and radar408
void fusion_front_radar208_radar408(){
  uint8_t j_min = -1;
  uint8_t k_min = -1;
  uint8_t l = 0;
  double dist_max1 = 100000;
  double dist_max2 = 100000;
  VectorXd x1(4);
  VectorXd x2(4);
  MatrixXd S(4, 4);
  S << 1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 2, 0,
      0, 0, 0, 2;
  MatrixXd Si = S.inverse();
  for (uint8_t i = 0; i < Obj408_ID_Total; i++){ // 1st for
    for (uint8_t j = 0; j < Obj208_ID_Total[0]; j++){ // 2nd for
      // radar208_1 is in defined gate
      if ((fabs(objs408[i].DistX - objs208[0][j].DistX) < gate_X / 2) && (fabs(objs408[i].DistY - objs208[0][j].DistY) < gate_Y / 2)){ // if radar208_1 is in defined gate
        x1(0) = objs408[i].DistX - objs208[0][j].DistX;
        x1(1) = objs408[i].DistY - objs208[0][j].DistY;
        x1(2) = objs408[i].VrelX - objs208[0][j].VrelX;
        x1(3) = objs408[i].VrelX - objs208[0][j].VrelY;
        MatrixXd xt1 = x1.transpose();
        MatrixXd dist1 = xt1 * Si * x1;
        if (dist1(0) < dist_max1){
          dist_max1 = dist1(0);
          j_min = j;
        }
      } // if radar208_1 is in defined gate
      for (uint8_t k = 0; k < Obj208_ID_Total[1]; k++){ // 3rd for
        // radar208_2 is in defined gate
        if ((fabs(objs408[i].DistX - objs208[1][k].DistX) < gate_X / 2) && (fabs(objs408[i].DistY - objs208[1][k].DistY) < gate_Y / 2)){
          x2(0) = objs408[i].DistX - objs208[1][k].DistX;
          x2(1) = objs408[i].DistY - objs208[1][k].DistY;
          x2(2) = objs408[i].VrelX - objs208[1][k].VrelX;
          x2(3) = objs408[i].VrelX - objs208[1][k].VrelY;
          MatrixXd xt2 = x2.transpose();
          MatrixXd dist2 = xt2 * Si * x2;
          if (dist2(0) < dist_max2){
            dist_max2 = dist2(0);
            k_min = k;
          }
        }
      } // 3rd for

    }// 2nd for

    // no radar208 detected in defined gate
    if ((dist_max1 == 100000) && (dist_max2 == 100000)){
      milradar_objs[l].DistX = objs408[i].DistX;
      milradar_objs[l].DistY = objs408[i].DistY;
      milradar_objs[l].VrelX = objs408[i].VrelX;
      milradar_objs[l].VrelY = objs408[i].VrelY;
      milradar_objs[l].ArelX = objs408[i].ArelX;
      milradar_objs[l].ArelY = objs408[i].ArelY;
      milradar_objs[l].ID = objs408[i].ID;
      milradar_objs[l].Length = objs408[i].Length;
      milradar_objs[l].Width = objs408[i].Width;
      l++;
    }

    // fuse radar408 and radar208_1
    else if ((dist_max1 < 100000) && (dist_max2 == 100000)){
      //milradar_objs[l].radar208_1_ID = objs208[0][j_min].ID;
      milradar_objs[l].DistX = 0.6 * objs408[i].DistX + 0.4 * objs208[0][j_min].DistX;
      milradar_objs[l].DistY = 0.6 * objs408[i].DistY + 0.4 * objs208[0][j_min].DistY;
      milradar_objs[l].VrelX = 0.6 * objs408[i].VrelX + 0.4 * objs208[0][j_min].VrelX;
      milradar_objs[l].VrelY = 0.6 * objs408[i].VrelY + 0.4 * objs208[0][j_min].VrelY;
      milradar_objs[l].ArelX = objs408[i].ArelX;
      milradar_objs[l].ArelY = objs408[i].ArelY;
      milradar_objs[l].ID = objs408[i].ID;
      milradar_objs[l].Length = objs408[i].Length;
      milradar_objs[l].Width = objs408[i].Width;
      memset(&objs208[0][j_min], 0, sizeof(objs208[0][j_min]));
      l++;
    }

    // fuse radar408 and radar208_2
    else if ((dist_max1 = 100000) && (dist_max2 < 100000)){
      //milradar_objs[l].radar208_2_ID = objs208[1][k_min].ID;
      milradar_objs[l].DistX = 0.6 * objs408[i].DistX + 0.4 * objs208[1][k_min].DistX;
      milradar_objs[l].DistY = 0.6 * objs408[i].DistY + 0.4 * objs208[1][k_min].DistY;
      milradar_objs[l].VrelX = 0.6 * objs408[i].VrelX + 0.4 * objs208[1][k_min].VrelX;
      milradar_objs[l].VrelY = 0.6 * objs408[i].VrelY + 0.4 * objs208[1][k_min].VrelY;
      milradar_objs[l].ArelX = objs408[i].ArelX;
      milradar_objs[l].ArelY = objs408[i].ArelY;
      milradar_objs[l].ID = objs408[i].ID;
      milradar_objs[l].Length = objs408[i].Length;
      milradar_objs[l].Width = objs408[i].Width;
      memset(&objs208[1][k_min], 0, sizeof(objs208[1][k_min]));
      l++;
    }

    // fuse radar408, radar208_1 and radar208_2
    else {
      milradar_objs[l].DistX = 0.6 * objs408[i].DistX + 0.2 * objs208[1][k_min].DistX + 0.2 * objs208[0][j_min].DistX;
      milradar_objs[l].DistY = 0.6 * objs408[i].DistY + 0.2 * objs208[1][k_min].DistY + 0.2 * objs208[0][j_min].DistY;
      milradar_objs[l].VrelX = 0.6 * objs408[i].VrelX + 0.2 * objs208[1][k_min].VrelX + 0.2 * objs208[0][j_min].VrelX;
      milradar_objs[l].VrelY = 0.6 * objs408[i].VrelY + 0.2 * objs208[1][k_min].VrelY + 0.2 * objs208[0][j_min].VrelY;
      milradar_objs[l].ID = objs408[i].ID;
      milradar_objs[l].Length = objs408[i].Length;
      milradar_objs[l].Width = objs408[i].Width;
      memset(&objs208[0][j_min], 0, sizeof(objs208[0][j_min]));
      memset(&objs208[1][k_min], 0, sizeof(objs208[1][k_min]));
      l++;
    }
  } // 1st for
  /*
  // collect independent radar208_1 and radar208_2 into radar_objs
  for (uint8_t j = 0; j < Obj208_ID_Total[0]; j++){
    if ((objs208[0][j].DistX != 0) && (objs208[0][j].DistY != 0)){
      milradar_objs[l].DistX = objs208[0][j].DistX;
      milradar_objs[l].DistY = objs208[0][j].DistY;
      milradar_objs[l].VrelX = objs208[0][j].VrelX;
      milradar_objs[l].VrelY = objs208[0][j].VrelY;
      milradar_objs[l].ArelX = Invalid_ArelX;
      milradar_objs[l].ArelY = Invalid_ArelY;
      milradar_objs[l].Length = default_milradar208_Length;
      milradar_objs[l].Width = default_milradar208_Width;
      milradar_objs[l].ID = objs208[0][j].ID%25+256;
      l++;
    }

    for (uint8_t k = 0; l < Obj208_ID_Total[1]; k++){
      if ((objs208[1][k].DistX != 0) && (objs208[1][k].DistY != 0)){
        milradar_objs[l].DistX = objs208[1][k].DistX;
        milradar_objs[l].DistY = objs208[1][k].DistY;
        milradar_objs[l].VrelX = objs208[1][k].VrelX;
        milradar_objs[l].VrelY = objs208[1][k].VrelY;
        milradar_objs[l].ArelX = Invalid_ArelX;
        milradar_objs[l].ArelY = Invalid_ArelY;
        milradar_objs[l].Length = default_milradar208_Length;
        milradar_objs[l].Width = default_milradar208_Width;
        milradar_objs[l].ID = objs208[1][k].ID%25+256+25;
        l++;
      }
    }

  }*/
  radar_ID_Total = l;
}

void fusion_radar_mobileye(){
  uint8_t j_min=0;
  uint16_t k = 0;
  double dist_max=100000;
  VectorXd x(4);
  MatrixXd S(4,4);
  S << 1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 2, 0,
      0, 0, 0, 2;
  MatrixXd Si = S.inverse();
  memset(rmobjs,0,sizeof(rmobjs));

  /*
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
    rmobjs[i].mobileye_Width=Obstacle[i].Width;
    rmobjs[i].mobileye_Length=Obstacle[i].Length;

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
  */
  for (uint8_t i = 0; i < mobileye_ID_Total; i++ ){
    for (uint8_t j = 0; j < radar_ID_Total; j++){
      if((fabs(Obstacle[i].PosX - milradar_objs[j].DistX) < gate_X / 2) && (fabs(Obstacle[i].PosY - milradar_objs[j].DistY) < gate_Y / 2)){
        x(0)=Obstacle[i].PosX - milradar_objs[j].DistX;
        x(1)=Obstacle[i].PosY - milradar_objs[j].DistY;
        x(2)=Obstacle[i].VrelX - milradar_objs[j].VrelX;
        if (milradar_objs[j].ArelX == Invalid_ArelX){
          x(3) = 0; // milradar_objs[i].ArelX = Obstacle[i].ArelX
        }
        else {
          x(3)=Obstacle[i].ArelX - milradar_objs[j].ArelX;
        }
        MatrixXd xt =x.transpose();
        MatrixXd dist=xt*Si*x;
        if(dist(0)<dist_max){
          dist_max=dist(0);
          j_min=j;
        }
      }
    }  // 2nd for

    rmobjs[k].mobileye_DistX=Obstacle[i].PosX;
    rmobjs[k].mobileye_DistY=Obstacle[i].PosY;
    rmobjs[k].mobileye_VrelX=Obstacle[i].VrelX;
    rmobjs[k].mobileye_ArelX=Obstacle[i].ArelX;
    rmobjs[k].fusion_Length = Obstacle[i].Length;
    rmobjs[k].fusion_Width = Obstacle[i].Width;
    if (dist_max == 100000){
      rmobjs[k].radar_DistX=Obstacle[i].PosX;
      rmobjs[k].radar_DistY=Obstacle[i].PosY;
      rmobjs[k].radar_VrelX=Obstacle[i].VrelX;
      rmobjs[k].radar_ArelX=Obstacle[i].ArelX;
      k++;
    }
    else {
      rmobjs[k].fusion_flag = 1;
      rmobjs[k].ID = milradar_objs[j_min].ID;
      rmobjs[k].radar_DistX = milradar_objs[j_min].DistX;
      rmobjs[k].radar_DistY = milradar_objs[j_min].DistY;
      rmobjs[k].radar_VrelX = milradar_objs[j_min].VrelX;
      rmobjs[k].radar_VrelY = milradar_objs[j_min].VrelY;
      rmobjs[k].radar_ArelX = milradar_objs[j_min].ArelX;
      rmobjs[k].radar_ArelY = milradar_objs[j_min].ArelY;
      memset(&milradar_objs[j_min], 0, sizeof(milradar_objs[j_min]));
      k++;
    }
  }  // 1st for

  //  collect milradar_objs[] into rmobjs[]
  for (uint8_t l = 0; l < radar_ID_Total; l++){
    if ((milradar_objs[l].DistX != 0) && (milradar_objs[l].DistY != 0)){
      rmobjs[k].fusion_flag = 0;
      rmobjs[k].ID = milradar_objs[l].ID;
      rmobjs[k].radar_DistX = milradar_objs[l].DistX;
      rmobjs[k].radar_DistY = milradar_objs[l].DistY;
      rmobjs[k].radar_VrelX = milradar_objs[l].VrelX;
      rmobjs[k].radar_VrelY = milradar_objs[l].VrelY;
      rmobjs[k].radar_ArelX = milradar_objs[l].ArelX;
      rmobjs[k].radar_ArelY = milradar_objs[l].ArelY;
      rmobjs[k].mobileye_DistX = milradar_objs[l].DistX;
      rmobjs[k].mobileye_DistY = milradar_objs[l].DistY;
      rmobjs[k].mobileye_VrelX = milradar_objs[l].VrelX;
      rmobjs[k].mobileye_ArelX = milradar_objs[l].ArelX;
      rmobjs[k].fusion_Length = milradar_objs[l].Length;
      rmobjs[k].fusion_Width = milradar_objs[l].Width;
      k++;
    }
  }
  mobileye_ID_Total = k;
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

  ros::Publisher chatter_pub = nh.advertise<kalman::radar_mobileye_data_multi>("radar_mobileye_data_multi", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    kalman::radar_mobileye_data_multi msg;
    fusion_front_radar208_radar408();
    fusion_radar_mobileye();
    for(uint16_t i=0;i<mobileye_ID_Total;i++){
      //ROS_INFO("fusion_Num %i",mobileye_ID_Total);
      if((rmobjs[i].radar_DistX < 50) && (fabs(rmobjs[i].radar_DistY) < 20)){
        if((fabs(rmobjs[i].radar_VrelX+Carinfo.Speed)>1.5)||(rmobjs[i].fusion_flag==1)){
          msg.objs.push_back(rmobjs[i]);
          rmobjs[i].timestamp=rmobjs[i].timestamp+100;
        }
      }
    }
    chatter_pub.publish(msg);
    //fusion_display();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
