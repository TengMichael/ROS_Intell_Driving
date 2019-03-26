#include "ros/ros.h"
#include "std_msgs/String.h"
#include <opencv2/opencv.hpp>
#include <milradar/obj208_multi.h>
#include <milradar/obj408_multi.h>
using namespace cv;

#define Win_height 400
#define Win_width 800

void display208(const milradar::obj208_multi::ConstPtr& msg)
{
        char objects_window[] = "Object208";
        Mat objects_image = Mat(Win_height, Win_width, CV_8UC3, Scalar(205, 205, 205));
        line(objects_image, Point(0, Win_height / 2 - 50), Point(Win_width, Win_height / 2 - 50),Scalar(0, 255, 255), 2, LINE_8);//left lane
        line(objects_image, Point(0, Win_height / 2 + 50), Point(Win_width, Win_height / 2 + 50),Scalar(0, 255, 255), 2, LINE_8);//right lane
        for (uint8_t i = 0; i < msg->objs.size(); i++) {
            if ((msg->objs[i].DistX != 0)&&(msg->objs[i].RCS>= 0))
            {
                rectangle(objects_image, Rect(msg->objs[i].DistX*10, msg->objs[i].DistY*10+ Win_height / 2, 10, 10),
                          Scalar(0, 0, 255),//B G R
                          -1, LINE_8);
            }
        }
        imshow(objects_window, objects_image);
        //moveWindow(objects_window, 100, 200);
        waitKey(10);
}
void display408(const milradar::obj408_multi::ConstPtr& msg)
{
        char objects_window[] = "Object408";
        Mat objects_image = Mat(Win_height, Win_width, CV_8UC3, Scalar(205, 205, 205));
        line(objects_image, Point(0, Win_height / 2 - 50), Point(Win_width, Win_height / 2 - 50),Scalar(0, 255, 255), 2, LINE_8);//left lane
        line(objects_image, Point(0, Win_height / 2 + 50), Point(Win_width, Win_height / 2 + 50),Scalar(0, 255, 255), 2, LINE_8);//right lane
        for (uint8_t i = 0; i < msg->objs.size(); i++) {
                rectangle(objects_image, Rect(msg->objs[i].DistX*10, msg->objs[i].DistY*10+ Win_height / 2, 10, 10),
                          Scalar(0, 0, 255),//B G R
                          -1, LINE_8);
        }
        imshow(objects_window, objects_image);
        //moveWindow(objects_window, 100, 200);
        waitKey(10);
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "milradar_display");
    ros::NodeHandle nh;

    ros::Subscriber sub1 = nh.subscribe("milradar_obj208_1", 1000, display208);
    ros::Subscriber sub2 = nh.subscribe("milradar_obj408", 1000, display408);
    ros::spin();

    return 0;
}
