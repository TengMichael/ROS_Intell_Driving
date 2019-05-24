#pragma once
#include<iostream>
#include <vector>
#include "cartesian_frenet_conversion.h"
using namespace std;

class vec2d {//用于表示点或相对位置
public:
    vec2d();
    vec2d(double z_in,double x_in);
	double z;//longitudinal
	double x;//lateral
};


class lane_line {//车道线
public:
	double C0;//lane position
	double C1;//heading angle
	double C2;//lane curvature 
	double C3;//lane curvature derivative	
	int lane_line_type;//类型：虚线、实线等
    //type definition: 0-dashed,1-solid,2-none,3-road edge,4-double lane mark,5-bott's dots,6-invalid
	bool valid;//是否检测到了车道线，对于应该有但没有检测到的车道线，就将这个值设为false

public:
	lane_line();//默认构造函数
	lane_line(double C0_in, double C1_in, double C2_in, double C3_in, int line_type, bool line_valid);
    double distance_point_laneline(double z, double x);//计算与某一条车道线的距离
    double lateral_position_line(double z);//计算给定z处车道线横向坐标
};

class obstacle {//障碍物
public:
    bool pedestrian;
    bool vehicle;
    double pos_z;//longitudinal position相对于当前车辆航向和位置的笛卡尔坐标系
    double pos_x;//lateral position相对于当前车辆航向和位置的笛卡尔坐标系
    double pos_s;//longitudinal position-frenet坐标系
    double pos_l;//lateral position-frenet坐标系
    double height;
    double width;
    double v_z;//longitudinal speed相对于当前车辆航向和位置的笛卡尔坐标系
    double v_x;//lateral speed相对于当前车辆航向和位置的笛卡尔坐标系
    double v_s;//沿轨迹的运动速度frenet坐标系
    double v_l;//垂直于轨迹的运动速度frenet坐标系
    //缺少障碍物速度坐标转换的程序

public:
    obstacle();//默认构造函数
    obstacle(double z, double x, double vz, double vx, double width_in, double height_in, int type);
    void calculate_speed_frenet(const double rkappa, const double l, const double veh_spd_cur);//根据v_z和v_x计算v_s和v_l
};

class lane {//车道
public:
	lane_line left;
	lane_line right;
	lane_line next_left;
	lane_line next_right;
	double road_speed_limit;//道路限速m/s

public:
	lane();//默认构造函数
	lane(lane_line left_in, lane_line right_in, double road_speed_limit_in);//只检测到单车道的情况
	lane(lane_line left_in, lane_line right_in, lane_line next_left_in, lane_line next_right_in, double road_speed_limit_in);//检测到了两侧的车道
	double distance_point_lane_centerline(double z, double x);//计算障碍物与中心线距离
	double lateral_position_centerline(double z);//计算给定纵向距离处车道中心线的横向坐标
	double lateral_position_left_centerline(double z);//计算给定纵向距离处左侧车道中心线的横向坐标
	double lateral_position_right_centerline(double z);//计算给定纵向距离处右侧车道中心线的横向坐标
	lane_line center_line_cal();//计算当前车道中心线方程
	lane_line left_center_line_cal();//计算左侧车道中心线方程
	lane_line right_center_line_cal();//计算右侧车道中心线方程
	double lane_width();//计算当前车道宽度
    int obs_in_lane(obstacle obs);//判断障碍物是否在车道内
};


vec2d GPS_to_local_coordinate(vec2d origin_gps, vec2d obj_gps, double veh_path_angle);//将object的GPS坐标转换到以origin_GPS为中心的局部坐标系中
