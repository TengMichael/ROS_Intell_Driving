#include "ros/ros.h"
#include <opencv2/opencv.hpp>
#include <mobileye/mobileye_Lane.h>
#include <mobileye/mobileye_LKA_Lane_multi.h>
#include <mobileye/mobileye_Obstacle_multi.h>

using namespace cv;

#define load_width 20*10
#define load_length 60*10
#define car_length 2*10
#define car_width 1*10

void mobileye_display_lane(const mobileye::mobileye_Lane msg)
{
  char window[] = "Mobileye_Lane";
  float c0_left,c0_right,c1,c2;
  std::vector<Point> Left_Points;
  std::vector<Point> Right_Points;

  c1=msg.Heading;
  c2=msg.Curvature;
  c0_left=msg.Left_Dist;
  c0_right=msg.Right_Dist;

  if((msg.Left_Conf!=0)||(msg.Right_Conf!=0)){
    for(uint16_t i=0;i<load_length;i++){
      float x=i*0.1;
      float y1=(c0_left+c1*x+c2*pow(x,2))*10;
      float y2=(c0_right+c1*x+c2*pow(x,2))*10;
      Left_Points.push_back(Point((int16_t)y1+load_width/2,load_length-x*10));
      Right_Points.push_back(Point((int16_t)y2+load_width/2,load_length-x*10));
    }
  }
  Mat image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(image, Rect(load_width/2-car_width/2,load_length-car_length,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  line(image,Point(load_width/2,load_length),Point(load_width/2,0),Scalar(255, 0, 0),1,LINE_8,0);
  polylines(image,Left_Points,false,Scalar(0,0,255),2,LINE_8,0);
  polylines(image,Right_Points,false,Scalar(0,0,255),2,LINE_8,0);

  imshow(window, image);
  //moveWindow(window, 100,200);
  waitKey(10);
}
void mobileye_display_LKA(const mobileye::mobileye_LKA_Lane_multi msg)
{
  char window[] = "Mobileye_LKA";
  float c0_left,c0_right,c1_left,c1_right,c2_left,c2_right,c3_left,c3_right;
  std::vector<Point> Left_Points;
  std::vector<Point> Right_Points;

  c0_left=msg.Left.Position;
  c1_left=msg.Left.Heading;
  c2_left=msg.Left.Curvature;
  c3_left=msg.Left.Curvature_deriv;

  c0_right=msg.Right.Position;
  c1_right=msg.Right.Heading;
  c2_right=msg.Right.Curvature;
  c3_right=msg.Right.Curvature_deriv;

  if((msg.Left.Quality!=0)||(msg.Right.Quality!=0)){
    for(uint16_t i=0;i<load_length;i++){
      float x=i*0.1;
      float y1=(c0_left+c1_left*x+c2_left*pow(x,2)+c3_left*pow(x,3))*10;
      float y2=(c0_right+c1_right*x+c2_right*pow(x,2)+c3_right*pow(x,3))*10;
      Left_Points.push_back(Point((int16_t)y1+load_width/2,load_length-x*10));
      Right_Points.push_back(Point((int16_t)y2+load_width/2,load_length-x*10));
    }
  }
  Mat image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(image, Rect(load_width/2-car_width/2,load_length-car_length,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  line(image,Point(load_width/2,load_length),Point(load_width/2,0),Scalar(255, 0, 0),1,LINE_8,0);
  polylines(image,Left_Points,false,Scalar(0,0,255),2,LINE_8,0);
  polylines(image,Right_Points,false,Scalar(0,0,255),2,LINE_8,0);

  imshow(window, image);
  //moveWindow(window, 100,200);
  waitKey(10);
}
void mobileye_display_obstacles(const mobileye::mobileye_Obstacle_multi msg)
{
  char window[] = "Mobileye_Obstacles";

  Mat image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));
  rectangle(image, Rect(load_width/2-car_width/2,load_length/2,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  line(image,Point(load_width/2,load_length),Point(load_width/2,0),Scalar(255, 0, 0),1,LINE_8,0);
  for (uint8_t i = 0; i < msg.Obstacles.size(); i++) {
    //0 vehicle;1 truck;2 bike;3 ped;4 bicyle;5-7 unused
    if(msg.Obstacles[i].MType==3)
      rectangle(image, Rect(load_width/2-msg.Obstacles[i].PosY,load_length/2-msg.Obstacles[i].PosX*2,msg.Obstacles[i].Width*5, msg.Obstacles[i].Length*5),
                Scalar(0,0,255),-1, LINE_8);//B G R
    else if(msg.Obstacles[i].MType<=1)
      rectangle(image, Rect(load_width/2-msg.Obstacles[i].PosY,load_length/2-msg.Obstacles[i].PosX*2,msg.Obstacles[i].Width*5, msg.Obstacles[i].Length*5),
                Scalar(255,0,0),-1, LINE_8);
    else if((msg.Obstacles[i].MType==2)||(msg.Obstacles[i].MType==4))
      rectangle(image, Rect(load_width/2-msg.Obstacles[i].PosY,load_length/2-msg.Obstacles[i].PosX*2,msg.Obstacles[i].Width*5, msg.Obstacles[i].Length*5),
                Scalar(255,0,255),-1, LINE_8);
    else
      rectangle(image, Rect(load_width/2-msg.Obstacles[i].PosY,load_length/2-msg.Obstacles[i].PosX*2,msg.Obstacles[i].Width*5, msg.Obstacles[i].Length*5),
                Scalar(0,0,0),-1, LINE_8);
  }
  imshow(window, image);
  //moveWindow(window, 100,200);
  waitKey(10);
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "mobileye_display");
  ros::NodeHandle nh;

  ros::Subscriber sub0 = nh.subscribe("mobileye_Lane", 1000, mobileye_display_lane);
  ros::Subscriber sub1 = nh.subscribe("mobileye_Obstacle", 1000, mobileye_display_obstacles);
  //ros::Subscriber sub2 = nh.subscribe("mobileye_LKA", 1000, mobileye_display_LKA);

  ros::spin();

  return 0;
}
