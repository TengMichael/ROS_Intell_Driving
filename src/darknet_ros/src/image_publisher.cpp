/**************************************************************************
 * @author z.h
 * @date 2019.1.4
 * @usage:image_publisher.cpp
 * @brief:@params[IN]:@return:
 **************************************************************************/
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/usb_cam/image_raw", 1);

  cv::Mat image = cv::imread("/home/michael/Desktop/11.jpg", CV_LOAD_IMAGE_COLOR);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8",image).toImageMsg();

  ros::Rate loop_rate(1);
    while (nh.ok()) {
      pub.publish(msg);
      ros::spinOnce();
      loop_rate.sleep();
  }
  return 0;
}


