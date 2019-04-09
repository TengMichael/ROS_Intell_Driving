#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <kf_radar_mobileye/radar_mobileye_data.h>
using namespace cv;

#define load_width 100*10
#define load_length 80*10
#define car_length 2*10
#define car_width 1*10

char window[] = "kalman_fusion";
Mat kf_image = Mat(load_length,load_width,CV_8UC3, Scalar(205, 205, 205));

void kf_fusion_display(const kf_radar_mobileye::radar_mobileye_data msg){
  rectangle(kf_image, Rect(load_width/2-msg.radar_DistY,load_length-msg.radar_DistX*2,4,4),
            Scalar(255,0,0),-1, LINE_8);//B G R
  rectangle(kf_image, Rect(load_width/2-msg.mobileye_DistY,load_length-msg.mobileye_DistX*2,4,4),
            Scalar(0,255,0),-1, LINE_8);//B G R
  rectangle(kf_image, Rect(load_width/2-msg.fusion_DistY,load_length-msg.fusion_DistX*2,4,4),
            Scalar(0,0,255),-1, LINE_8);//B G R
  imshow(window, kf_image);
  //moveWindow(window,load_width*(ch-1),0);
  waitKey(10);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "kalman_display");
  ros::NodeHandle nh;

  rectangle(kf_image, Rect(load_width/2-car_width/2,load_length-car_length,car_width, car_length), Scalar(0,255,0),2,LINE_8,0);
  line(kf_image, Point(load_width/4,0), Point(load_width/4,load_length),Scalar(0, 255, 255), 2, LINE_8);//left lane
  line(kf_image, Point(load_width/4*3,0), Point(load_width/4*3,load_length),Scalar(0, 255, 255), 2, LINE_8);//right lane

  ros::Subscriber sub0 = nh.subscribe("radar_mobileye_kf", 1000, kf_fusion_display);

  ros::spin();

  return 0;
}
