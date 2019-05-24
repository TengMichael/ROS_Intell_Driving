#pragma once

#include <vector>
#include "environment/environment.h"
#include "planning/astar.hpp"
#include "planning/rrt/utils.hpp"
#include "planning/rrt/RRT.hpp"
//#include "planning/rrt/RRT_implementation.hpp"
using namespace std;
using namespace AStar;

class navi {//导航数据
public:
  double BD_lon;//经度
  double BD_lat;//纬度
  int distance_from_road_seg_end;//路段终点距离
  int direction_road;//路相对于北极的角度
  int turn;//转向信息
  int turn_for_intersection;//用于路口的转向信息
  vector<double> RelX;//当前路段坐标点串x
  vector<double> RelY;//当前路段坐标点串y
  int newroad;//是否进入新的道路，置1表示进入

public:
  navi();//默认构造函数
};

struct path_point{
    double t;
    double v;
    double z;
    double x;
};

class vehicle {//用于定义车辆自身特性
public:
  double veh_len;//车身长度
  double veh_width;//车宽
  double cur_speed;//当前车速m/s
  double yaw_angle;//航向角
  double veh_preferred_speed;//偏好的车速m/s
  double max_acc;//最高加速度m/s2
  double max_dec;//最高减速度m/s2(绝对值)
  double max_steering_angle;//最大转向角rad
  double lon;//经度
  double lat;//纬度

public:
  vehicle();//默认构造函数
  vehicle(double len,double width, double cur_spd,double preferred_speed, double max_a,double max_d,
          double max_angle, double yaw_ang, double lon_in, double lat_in);//构造函数
  double safety_steering_angle_cal(void);//返回单位为rad的角度
};

class path_segment {//用于定义直线和圆弧，但是对于车道线等不规则曲线，则需要单独定义
public:
  vec2d init_point;//起点
  vec2d end_point;//终点
  double init_speed;//起点车速
  double end_speed;//终点车速
  double kappa;//起点到终点的过渡圆弧曲率 //不超过180°的圆弧，否则不好判断
  int direction;//用于计算圆心位置（left-0,right-1）
  int is_lane_driving;//是否是在车道线内行驶，若是，则使用车道线方程，若不是，则使用上面定义的起止点和曲率
  double C0, C1, C2, C3;//车道线方程
  double path_segment_length;//片段长度（m）
public:
  bool path_segment_collision(obstacle obs);
  double path_segment_distance_with_obstacle(obstacle obs);//貌似最好返回一个带正负号的值，以免不相干的障碍物影响行车路线
  double path_segment_length_cal(void);//返回长度
};


class path
{
public:
  vector<path_segment> path_series;//规划片段序列
  vec2d GPS_pos_init;//起始点的GPS位置
  double path_angle_init;//起始航向角

public:
  bool path_collision(obstacle obs);//计算沿当前路径行驶是否会与障碍物相撞（适用于静止障碍物）
};

class shortrange_planning {
public:
  lane lane_info;//车道信息
  vehicle veh_info;//车辆信息
  vector<obstacle> obstacle_info;//障碍物详细信息
  int driving_intention;//短程驾驶意图（列表：0-直行，1-左变道，2-右变道等等）
  path previous_path;
  vec2d GPS_position_cur;
  double veh_path_angle;
  int obstacle_map_temporal_spatio[100][100];//障碍物时空栅格地图（时间*空间），先预定义一个数组大小
  //地图的单位是s*m
  path planned_path;
  vector<path_point> out_path;

public:
  shortrange_planning();
  shortrange_planning(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                      int driving_intention_in,vec2d GPS_cur, double path_angle);
  void planned_path_cal();//根据初步的规划得到插值点
  void obstacle_path_temporal_spatio_figure(void);//计算障碍物在ST图上的分布
};

class straight : public shortrange_planning {
public:
  straight():shortrange_planning(){;}
  straight(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
           int driving_intention_in,vec2d GPS_cur, double path_angle);
  path generate_path_free_driving();
  path generate_path_following();
  path generate_path_braking(int brake_distance);

  //path speed_planning(void);
  //CoordinateList speed_planning_astar(void);
};

class change_lane : public shortrange_planning {
public:
  int change_lane_direction;//0-不变道，1-左变道，2-右变道
  change_lane():shortrange_planning(){change_lane_direction=0;}
  change_lane(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
              int driving_intention_in,vec2d GPS_cur, double path_angle, int change_lane_direction_in);
  path generate_path(void);
  //CoordinateList speed_planning_astar(void);
};

class intersection : public shortrange_planning {
public:
  int intersection_type;//0-路口直行，1-路口左转，2-路口右转
  vec2d GPS_in_road_section;//下一路段入口处GPS位置（输入已转换成自车坐标）
  vec2d GPS_out_road_section;//当前路段出口GPS位置（输入已转换成自车坐标）
  intersection():shortrange_planning(){intersection_type=0;}
  int traffic_light_state;//红绿灯状态，1-绿灯，2-黄灯，3-红灯
  int traffic_light_time_remaining;//当前状态剩余时长

public:
  intersection(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
               int driving_intention_in, vec2d GPS_cur, double path_angle,
               int intersection_type_in, vec2d gps_out, vec2d gps_in, int traffic_light_state_in,
               int traffic_light_time_remaining_in);
  //path generate_path(void);
  //path speed_planning(void);
  //CoordinateList generate_path_astar(void);
  vector<path_point> generate_path_rrt(void);//rrt规划
  vector<path_point> generate_path_brake(void);
};

vec2d circle_center(vec2d init_point,vec2d end_point,double kappa,int direction);
