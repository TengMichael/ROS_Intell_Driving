#ifndef GLOBAL2LOCAL_H
#define GLOBAL2LOCAL_H
#include <math.h>
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
typedef struct vec2d{
double lat;
double lon;
}_vec2d;

vec2d GPS_to_local_coordinate(vec2d origin_gps, vec2d obj_gps, double veh_path_angle) {
  //将object的GPS坐标转换到以origin_GPS为中心的局部坐标系中
  //latitude对应vec2d中的lat，longitude对应vec2d中的lon
  //veh_path_angle是车辆行驶方向与北极的夹角，范围[0,2pi]

  //计算两点距离
  double radLat1 = rad(origin_gps.lat);
  double radLat2 = rad(obj_gps.lat);
  double a = radLat1 - radLat2;
  double b = rad(origin_gps.lon) - rad(obj_gps.lon);
  double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
                           cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
  s = s * EARTH_RADIUS;
  s = round(s * 10000) / 10000;
  //计算obj_gps相对于origin_gps航向角
  double x = sin(obj_gps.lon - origin_gps.lon) * cos(obj_gps.lat);
  double y = cos(origin_gps.lat)*sin(obj_gps.lat)
      - sin(origin_gps.lat)*cos(obj_gps.lat)*cos(obj_gps.lon - origin_gps.lon);
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
  veh_path_angle=rad(veh_path_angle);
  double a1 = bearing - veh_path_angle;
  double a2 = bearing + 2 * pi - veh_path_angle;
  double a0;
  if (a1 >= 0) {
    a0 = a1;
  }
  else {
    a0 = a2;
  }
  obj_pos.lon = sin(a0)*s;
  obj_pos.lat = cos(a0)*s;
  return obj_pos;
}



#endif // GLOBAL2LOCAL_H
