#include "global.h"
using namespace std;

vec2d::vec2d(){
  z=0;
  x=0;
}

vec2d::vec2d(double z_in,double x_in){
  z=z_in;
  x=x_in;
}


lane_line::lane_line() {
  C0 = 0;
  C1 = 0;
  C2 = 0;
  C3 = 0;
  lane_line_type = 1;
  valid = false;
}

lane_line::lane_line(double C0_in, double C1_in, double C2_in, double C3_in, 
                     int line_type, bool line_valid) {
  C0 = C0_in;
  C1 = C1_in;
  C2 = C2_in;
  C3 = C3_in;
  lane_line_type = line_type;
  valid = line_valid;
}

double lane_line::distance_point_laneline(double z, double x){
  //x:point lateral position, z:point longitudinal position
  //计算与某一条车道线的距离，在左为负，在右为正
  double x_lane = C0 + C1 * z + C2 * z*z + C3 * z*z*z;
  return x-x_lane;//z<0时也是相同的方程吗？
}

double lane_line::lateral_position_line(double z) {
  //x:point lateral position, z:point longitudinal position
  //计算给定z处车道线横向坐标
  double x_lane = C0 + C1 * z + C2 * z*z + C3 * z*z*z;
  return x_lane;
}

lane::lane() {
  lane_line left_temp = lane_line(-1.75, 0, 0, 0, 1, true);
  lane_line right_temp = lane_line(1.75, 0, 0, 0, 1, true);
  lane_line next_left_temp = lane_line(-5.25, 0, 0, 0, 1, true);
  lane_line next_right_temp = lane_line(5.25, 0, 0, 0, 1, true);
  left = left_temp;
  right = right_temp;
  next_left = next_left_temp;
  next_right = next_right_temp;
  road_speed_limit = 60;
}

lane::lane(lane_line left_in, lane_line right_in, double road_speed_limit_in){
  //会不会出现车辆不在检测到的左右车道线之间的情况?
  if(left_in.C0>1.75 && right_in.C0>1.75){//检测到的左侧车道线在车辆右边
    left=left_in;
    left.C0=2*left_in.C0-right_in.C0;
    left.valid=false;
    right=left_in;
    next_right=right_in;
    next_left = lane_line(2*left.C0-right.C0, left.C1,
                          left.C2, left.C3, left.lane_line_type, false);
  }
  else if(left_in.C0<-1.75 && right_in.C0<-1.75){//检测到的右侧车道线在车辆左边
    right=right_in;
    right.C0=2*left_in.C0-right_in.C0;
    right.valid=false;
    left=right_in;
    next_left=left_in;
    next_right = lane_line(2*right.C0-left.C0, right.C1,
                           right.C2, right.C3, right.lane_line_type, false);
  }
  else{//正常情况
    left = left_in;
    right = right_in;
    next_left = lane_line(2*left.C0-right.C0, left.C1,
                          left.C2, left.C3, left.lane_line_type, false);
    next_right = lane_line(2*right.C0-left.C0, right.C1,
                           right.C2, right.C3, right.lane_line_type, false);
  }
  road_speed_limit = road_speed_limit_in;
}

lane::lane(lane_line left_in, lane_line right_in, lane_line next_left_in, 
           lane_line next_right_in, double road_speed_limit_in) {
  //会不会出现车辆不在检测到的左右车道线之间的情况?
  if(left_in.C0>1.75 && right_in.C0>1.75){//检测到的左侧车道线在车辆右边
    left=next_left_in;
    right=left_in;
    next_right=right_in;
    next_left = lane_line(2*left.C0-right.C0, left.C1,
                          left.C2, left.C3, left.lane_line_type, false);
  }
  else if(left_in.C0<-1.75 && right_in.C0<-1.75){//检测到的右侧车道线在车辆左边
    right=next_right_in;
    left=right_in;
    next_left=left_in;
    next_right = lane_line(2*right.C0-left.C0, right.C1,
                           right.C2, right.C3, right.lane_line_type, false);
  }
  else{//正常情况
    left = left_in;
    right = right_in;
    next_left = next_left_in;
    next_right = next_right_in;
  }
  road_speed_limit = road_speed_limit_in;
}

double lane::distance_point_lane_centerline(double z, double x) {
  //x:point lateral position, z:point longitudinal position
  //计算与左右车道线的距离
  double distance_left=left.distance_point_laneline(z, x);
  double distance_right=right.distance_point_laneline(z, x);
  double distance_center = (distance_left + distance_right) / 2;
  return distance_center;
}

double lane::lateral_position_centerline(double z) {
  //x:point lateral position, z:point longitudinal position
  //计算车道中心线横向位置
  double x_left = left.lateral_position_line(z);
  double x_right = right.lateral_position_line(z);
  double x_center = (x_left + x_right) / 2;
  return x_center;
}

double lane::lateral_position_left_centerline(double z) {
  //x:point lateral position, z:point longitudinal position
  //计算左侧车道中心线横向位置
  if (next_left.valid == true) {//直接求左侧车道中心线
    double x_left = next_left.lateral_position_line(z);
    double x_right = left.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2;
    return x_center;
  }
  else {//根据当前车道中心线和车道宽度求左侧车道中心线位置
    double x_left = left.lateral_position_line(z);
    double x_right = right.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2 - abs(x_right-x_left);
    return x_center;
  }
}

double lane::lateral_position_right_centerline(double z) {
  //x:point lateral position, z:point longitudinal position
  //计算右侧车道中心线横向位置
  if (next_right.valid == true) {//直接求右侧车道中心线
    double x_left = right.lateral_position_line(z);
    double x_right = next_right.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2;
    return x_center;
  }
  else {//根据当前车道中心线和车道宽度求右侧车道中心线位置
    double x_left = left.lateral_position_line(z);
    double x_right = right.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2 + abs(x_right - x_left);
    return x_center;
  }
}

lane_line lane::center_line_cal(void) {//如果当前车道线没检测出来怎么办
  lane_line center_line=lane_line(0,0,0,0,0,true);
  center_line.C0 = (left.C0 + right.C0) / 2;
  center_line.C1 = (left.C1 + right.C1) / 2;
  center_line.C2 = (left.C2 + right.C2) / 2;
  center_line.C3 = (left.C3 + right.C3) / 2;
  return center_line;
}

lane_line lane::left_center_line_cal(void) {
  lane_line center_line = lane_line(0, 0, 0, 0, 0, true);
  if (next_left.valid == true) {//直接求左侧车道中心线
    center_line.C0 = (left.C0 + next_left.C0) / 2;
    center_line.C1 = (left.C1 + next_left.C1) / 2;
    center_line.C2 = (left.C2 + next_left.C2) / 2;
    center_line.C3 = (left.C3 + next_left.C3) / 2;
  }
  else {//根据车道宽度推算左侧车道中心线
    center_line.C0 = (left.C0 + right.C0) / 2-abs(right.C0 - left.C0);
    center_line.C1 = (left.C1 + right.C1) / 2;
    center_line.C2 = (left.C2 + right.C2) / 2;
    center_line.C3 = (left.C3 + right.C3) / 2;
  }
  return center_line;
}

lane_line lane::right_center_line_cal(void) {
  lane_line center_line = lane_line(0, 0, 0, 0, 0, true);
  if (next_right.valid == true) {//直接求右侧车道中心线
    center_line.C0 = (right.C0 + next_right.C0) / 2;
    center_line.C1 = (right.C1 + next_right.C1) / 2;
    center_line.C2 = (right.C2 + next_right.C2) / 2;
    center_line.C3 = (right.C3 + next_right.C3) / 2;
  }
  else {//根据车道宽度推算右侧车道中心线
    center_line.C0 = (left.C0 + right.C0) / 2 + abs(right.C0 - left.C0);
    center_line.C1 = (left.C1 + right.C1) / 2;
    center_line.C2 = (left.C2 + right.C2) / 2;
    center_line.C3 = (left.C3 + right.C3) / 2;
  }
  return center_line;
}

double lane::lane_width() {
  //计算车道宽度
  return abs(right.C0-left.C0);
}

int lane::obs_in_lane(obstacle obs){
    //判断障碍物在哪一条车道内
    //在左边车道为-2，同时占左边和当前车道为-1，在当前车道为0，同时占右边和当前车道为1，在右边车道为2，同时占三条车道为3，不在任何车道内为-3
    int lane_no=-3;
    double z = sqrt(pow(obs.pos_z,2)+pow(obs.pos_x,2));//前方＞0,后方＜0
    //计算障碍物与当前车道偏离的横向距离
    double frenet_x = distance_point_lane_centerline(obs.pos_z,obs.pos_x);
    double lane_wid=lane_width();

    //判断该车在目标车道还是当前车道，或者在其他车道，不影响当前车行驶
    //首先判断在不在车道，再判断在哪个车道
    if(frenet_x+obs.width/2<-lane_wid *3 / 2){
        lane_no=-3;
    }
    else if(frenet_x-obs.width/2>lane_wid *3 / 2){
        lane_no=-3;
    }
    else if (frenet_x >= -lane_wid / 2 && frenet_x <= lane_wid / 2 && z>0) {
        //障碍物中心在中间车道
        lane_no=0;
        if (frenet_x+obs.width/2>lane_wid / 2+0.5){
            //占了右边车道
            lane_no=1;
            if(frenet_x-obs.width/2<-lane_wid / 2-0.5){
                //占了左边车道
                lane_no=3;
            }
        }
    }
    else if (frenet_x >= -lane_wid*3 / 2 && frenet_x <= -lane_wid/ 2) {
        //若在左侧车道
        lane_no=-2;
        if (frenet_x+obs.width/2>-lane_wid / 2+0.5){
            //占了中间车道
            lane_no=-1;
            if(frenet_x+obs.width/2>lane_wid / 2+0.5){
                //占了右边车道
                lane_no=3;
            }
        }
    }
    else if (frenet_x >= lane_wid / 2 && frenet_x <= lane_wid *3 / 2) {
        //若在右侧车道
        lane_no=-2;
        if (frenet_x-obs.width/2<lane_wid / 2-0.5){
            //占了中间车道
            lane_no=1;
            if(frenet_x-obs.width/2<-lane_wid / 2-0.5){
                //占了左边车道
                lane_no=3;
            }
        }
    }
    return lane_no;
}


#define pi  3.14159265358979323846
double EARTH_RADIUS = 6378137;

double rad(double d)
{
  return d * pi / 180.0;
}

double degree(double d)
{
  return d * 180 / pi;
}


vec2d GPS_to_local_coordinate(vec2d origin_gps, vec2d obj_gps, double veh_path_angle) {
  //将object的GPS坐标转换到以origin_GPS为中心的局部坐标系中
  //latitude对应vec2d中的z，longitude对应vec2d中的x
  //veh_path_angle是车辆行驶方向与北极的夹角，范围[0,2pi]

  //计算两点距离
  double radLat1 = rad(origin_gps.z);
  double radLat2 = rad(obj_gps.z);
  double a = radLat1 - radLat2;
  double b = rad(origin_gps.x) - rad(obj_gps.x);
  double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
                           cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
  s = s * EARTH_RADIUS;
  s = round(s * 10000) / 10000;
  //计算obj_gps相对于origin_gps航向角
  double x = sin(obj_gps.x - origin_gps.x) * cos(obj_gps.z);
  double y = cos(origin_gps.z)*sin(obj_gps.z)
      - sin(origin_gps.z)*cos(obj_gps.z)*cos(obj_gps.x - origin_gps.x);
  double bearing;
  if (x >=  0 && y >= 0) {
    bearing = atan2(x, y);
  }
  else if(x >=0 && y<=0){
    bearing = atan2(x, y)+pi;
  }
  else if (x <= 0 && y <= 0) {
    bearing = atan2(x, y) + pi;
  }
  else {
    bearing = atan2(x, y) + pi*2;
  }
  //根据当前航向角计算出obj的坐标
  vec2d obj_pos;
  double a1 = bearing - veh_path_angle;
  double a2 = bearing + 2 * pi - veh_path_angle;
  double a0;
  if (a1 >= 0) {
    a0 = a1;
  }
  else {
    a0 = a2;
  }
  obj_pos.x = sin(a0)*s;
  obj_pos.z = cos(a0)*s;
  return obj_pos;
}

void obstacle::calculate_speed_frenet(const double rkappa, const double l, const double veh_spd_cur) {
  //根据v_z和v_x求theta
  double theta=0;
  if (v_x >= 0 && v_z >= 0) {
    theta = atan2(v_z, v_x);
  }
  else if (v_x <= 0 && v_z >= 0) {
    theta = atan2(v_z, v_x) + pi;
  }
  else if (v_x <= 0 && v_z <= 0) {
    theta = atan2(v_z, v_x) + pi;
  }
  else {
    theta = atan2(v_z, v_x) + pi * 2;
  }
  double rtheta = pi / 2;
  //计算frenet坐标系下的分解车速
  v_s=CalculateLongitudinalDerivative(rtheta, theta, l, rkappa, veh_spd_cur);
  v_l=CalculateLateralDerivative(rtheta, theta, l, rkappa);
}

obstacle::obstacle() {
  pos_z = 100;
  pos_x = 0;
  v_z = 0;
  v_x = 0;
  width = 4;
  height = 2;
  vehicle = true;
  pedestrian = false;
}

obstacle::obstacle(double z, double x, double vz, double vx, double width_in, double height_in, int type) {
  pos_z = z;
  pos_x = x;
  v_z = vz;
  v_x = vx;
  width = width_in;
  height = height_in;
  if (type == 1) {
    vehicle = true;
    pedestrian = false;
  }
  else if (type == 2) {
    vehicle = false;
    pedestrian = true;
  }
  else {
    vehicle = false;
    pedestrian = false;
  }
}

