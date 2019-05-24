#include "global.h"

//数据定义及初始化
lane lane_test = lane(lane_line(-2, 0, 0, 0, 1, true), lane_line(2, 0, 0, 0, 1, true), 10);
vehicle veh_test = vehicle(4, 2, 0, 2, 3, 3, PI / 4, 0.0,121.0,31.0);
navi navi_test=navi();
vector<obstacle> obs_info;
path path_test;
vector<path_point> out_path1;
decision_planning::traj_point_data traj_temp[1000]={};
uint timestamp=0;
double front_dis=1000;
