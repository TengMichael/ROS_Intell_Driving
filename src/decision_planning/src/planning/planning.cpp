#include "global.h"
using namespace AStar;
using namespace std;
using namespace rrt;

navi::navi() {
  BD_lon=121.0;//经度
  BD_lat=31.0;//纬度
  distance_from_road_seg_end=100;//路段终点距离
  direction_road=0;//路相对于北极的角度
  turn=0;//转向信息
  turn_for_intersection=0;//用于路口的转向信息
  RelX.clear();//当前路段坐标点串x
  RelY.clear();//当前路段坐标点串y
  newroad=0;//是否进入新的道路，置1表示进入
}

vehicle::vehicle() {
    veh_len = 3;
    veh_width =2;
    cur_speed = 0;
    veh_preferred_speed = 10;
    max_acc = 3;
    max_dec = 3;
    max_steering_angle = PI/4;
    yaw_angle=0;
    lon=121;
    lat=31;
}

vehicle::vehicle(double len, double width, double cur_spd, double preferred_speed, double max_a,
                 double max_d, double max_angle, double yaw_ang, double lon_in, double lat_in) {
    veh_len = len;
    veh_width = width;
    cur_speed = cur_spd;
    veh_preferred_speed = preferred_speed;
    max_acc = max_a;
    max_dec = max_d;
    max_steering_angle = max_angle;
    yaw_angle=yaw_ang;
    lon=lon_in;
    lon=lat_in;
}

double vehicle::safety_steering_angle_cal(void){
    //返回单位为rad的角度
    //目前是参考值,具体要查找文献
    if(cur_speed>20){
        return (double)2/180*PI;
    }
    else if(cur_speed>15){
        return (double)4/180*PI;//车速20m/s时最大转向角2°
    }
    else if(cur_speed>10){
        return (double)10/180*PI;//车速15m/s时最大转向角10°
    }
    else if(cur_speed>5){
        return (double)15/180*PI;
    }
    else if(cur_speed>2){
        return (double)20/180*PI;
    }
    else{
        return (double)45/180*PI;
    }
}

bool path_segment::path_segment_collision(obstacle obs) {
    double distance;
    if (is_lane_driving) {//车道
        distance = abs(C0 + C1 * obs.pos_z + C2 * obs.pos_z*obs.pos_z
                       + C3 * obs.pos_z*obs.pos_z*obs.pos_z - obs.pos_x);
        if (distance < obs.width) {
            return true;//干涉
        }
    }
    else {//非车道

        if (kappa == 0) {//非车道的直线
            //求点到直线的距离
            double A, B, C;//Ax+Bz+C=0;
            A = (end_point.z - init_point.z) / (end_point.x - init_point.x);
            B = -1;
            C = init_point.z - init_point.x * A;
            distance = abs(A * obs.pos_x + B * obs.pos_z + C) / sqrt(A * A + B * B);
            if (distance < obs.width) {
                return true;//干涉
            }
        }
        else {//非车道的圆弧
            //求点到圆心的距离，与圆半径之差就是点到圆弧的距离
            //求圆心
            vec2d center=circle_center(init_point,end_point,kappa,direction);
            double x0,z0,A,B,C;
            x0=center.x;
            z0=center.z;
            distance = 1000;
            //判断在不在弧线角度范围内
            double k1[2], k2[2], k3[2], k4[2];
            k1[0] = (init_point.z + end_point.z - 2 * z0);//扇形中心线
            k1[1] = (init_point.x + end_point.x - 2 * x0);
            k2[0] = (init_point.z - z0);//扇形起始线
            k2[1] = (init_point.x - x0);
            k3[0] = (end_point.z - z0);//扇形终止线
            k3[1] = (end_point.x - x0);
            k4[0] = (obs.pos_z - z0);
            k4[1] = (obs.pos_x - x0);
            A = k1[0] * k4[0] + k1[1] * k4[1];//A>0表示与中心线的夹角为锐角，点积大于0
            B = k2[0] * k4[0] + k2[1] * k4[1];
            C = k3[0] * k4[0] + k3[1] * k4[1];
            if (A > 0) {//判断与各条线的夹角是否是锐角
                if (B > 0 || C > 0) {
                    //计算距离(与圆心的距离-半径)
                    distance = abs(sqrt(pow(obs.pos_x - x0, 2) + pow(obs.pos_z - z0, 2)) - 1 / kappa);
                }
            }
            if (distance < obs.width) {
                return true;//干涉
            }
        }
    }
    return false;
}

double path_segment::path_segment_distance_with_obstacle(obstacle obs) {
    double distance;
    if (is_lane_driving) {//车道
        distance = abs(C0 + C1 * obs.pos_z + C2 * obs.pos_z*obs.pos_z
                       + C3 * obs.pos_z*obs.pos_z*obs.pos_z - obs.pos_x);
        return distance;
    }
    else {//非车道
        if (kappa == 0) {//非车道的直线
            //求点到直线的距离
            double A, B, C;//Ax+Bz+C=0;
            A = (end_point.z - init_point.z) / (end_point.x - init_point.x);
            B = -1;
            C = init_point.z - init_point.x * A;
            distance = abs(A * obs.pos_x + B * obs.pos_z + C) / sqrt(A * A + B * B);
            return distance;
        }
        else {//非车道的圆弧
            //求点到圆心的距离，与圆半径之差就是点到圆弧的距离
            //求圆心
            double c1 = 0, c2 = 0, A = 0, B = 0, C = 0, z01 = 0, x01 = 0, x02 = 0, z02 = 0;
            c1 = (pow(end_point.x, 2) - pow(init_point.x, 2) + pow(end_point.z, 2)
                  - pow(init_point.z, 2)) / 2 / (end_point.x - init_point.x);
            c2 = (end_point.z - init_point.z) / (end_point.x - init_point.x);
            A = 1.0 + pow(c2, 2);
            B = 2 * (init_point.x - c1) * c2 - 2 * init_point.z;
            C = pow((init_point.x - c1), 2) + pow(init_point.z, 2) - pow(1 / kappa, 2);
            z01 = (-B + sqrt(B*B - 4 * A * C)) / 2 / A;
            x01 = c1 - c2 * z01;
            z02 = (-B - sqrt(B*B - 4 * A * C)) / 2 / A;
            x02 = c1 - c2 * z02;
            cout << "圆心坐标1为: (" << x01 << ", " << z01 << ")" << endl;
            cout << "圆心坐标2为: (" << x02 << ", " << z02 << ")" << endl;
            double x0, z0;
            if (direction == 0) {//left
                if (x01 < x02) {
                    x0 = x01;
                    z0 = z01;
                }
                else {
                    x0 = x02;
                    z0 = z02;
                }
            }
            else {//right
                if (x01 > x02) {
                    x0 = x01;
                    z0 = z01;
                }
                else {
                    x0 = x02;
                    z0 = z02;
                }
            }
            distance = 1000;
            //判断在不在弧线角度范围内
            double k1[2], k2[2], k3[2], k4[2];
            k1[0] = (init_point.z + end_point.z - 2 * z0);//扇形中心线
            k1[1] = (init_point.x + end_point.x - 2 * x0);
            k2[0] = (init_point.z - z0);//扇形起始线
            k2[1] = (init_point.x - x0);
            k3[0] = (end_point.z - z0);//扇形终止线
            k3[1] = (end_point.x - x0);
            k4[0] = (obs.pos_z - z0);
            k4[1] = (obs.pos_x - x0);
            A = k1[0] * k4[0] + k1[1] * k4[1];//A>0表示与中心线的夹角为锐角，点积大于0
            B = k2[0] * k4[0] + k2[1] * k4[1];
            C = k3[0] * k4[0] + k3[1] * k4[1];
            if (A > 0) {//判断与各条线的夹角是否是锐角
                if (B > 0 || C > 0) {
                    //计算距离(与圆心的距离-半径)
                    distance = abs(sqrt(pow(obs.pos_x - x0, 2) + pow(obs.pos_z - z0, 2)) - 1 / kappa);
                }
            }
            return distance;
        }
    }
    return distance;
}

double path_segment::path_segment_length_cal(void) {
    //积分((1+f'(x)^2))^0.5dx
    if (is_lane_driving) {//车道
        double z1 = init_point.z;
        double z2 = end_point.z;
        double temp1 = C1 + 2 * C2*z1 + 3 * C3*z1*z1;
        double temp2 = C1 + 2 * C2*z2 + 3 * C3*z2*z2;
        path_segment_length = sqrt((z1-z2)*(z1-z2)+(temp1-temp2)*(temp1-temp2));
        //path_segment_length = 0.5*temp2*sqrt(1 + temp2 * temp2)
         //       + 0.5*log(abs(temp2 + sqrt(1 + temp2 * temp2)))
         //       - 0.5*temp1*sqrt(1 + temp1 * temp1) + 0.5*log(abs(temp1 + sqrt(1 + temp1 * temp1)));
    }
    else if (kappa == 0) {//直线
        path_segment_length = sqrt(pow(init_point.z - end_point.z, 2)
                                   + pow(init_point.x - end_point.x, 2));
    }
    else {//圆弧
        //不想算角度啦估算一下吧,就当是90度啦
        path_segment_length = (3.1415/2/1.414)*sqrt(pow(init_point.z - end_point.z, 2)
                                                    + pow(init_point.x - end_point.x, 2));
    }
    return path_segment_length;
}

bool path::path_collision(obstacle obs) {
    for (int i = 0; i < path_series.size(); i++) {
        if (path_series[i].path_segment_collision(obs)) {
            return true;
            break;
        }
    }
}

path straight::generate_path_free_driving(void) {
    //如果车道线有效就更新规划点，无效就沿用之前的规划轨迹
    if (lane_info.left.valid == true && lane_info.right.valid == true) {
        //更新路径规划起始GPS和航向角
        path straight_path;
        straight_path.GPS_pos_init = GPS_position_cur;
        straight_path.path_angle_init = veh_path_angle;
        double z_temp1=10;
        double z_temp2=100;
        //根据当前车速计算减速时间和减速距离
        z_temp1=max(10.0,0.5*(veh_info.cur_speed*veh_info.veh_preferred_speed)*abs(veh_info.cur_speed-veh_info.veh_preferred_speed)/2);
        z_temp2=max(z_temp1+1,100.0);
        //沿车道线行驶，车道方程
        //path_segment1  变速
        path_segment path_segment_temp;
        path_segment_temp.init_point.z = 0;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(0);
        path_segment_temp.end_point.z = z_temp1;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp1);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        path_segment_temp.init_speed = veh_info.cur_speed;
        path_segment_temp.end_speed = min(lane_info.road_speed_limit, veh_info.veh_preferred_speed);
        straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
        //path_segment2  匀速
        path_segment_temp.init_point.z = z_temp1;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(z_temp1);
        path_segment_temp.end_point.z = z_temp2;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp2);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        path_segment_temp.init_speed = min(lane_info.road_speed_limit, veh_info.veh_preferred_speed);
        path_segment_temp.end_speed = min(lane_info.road_speed_limit, veh_info.veh_preferred_speed);
        straight_path.path_series.insert(straight_path.path_series.begin()+1, path_segment_temp);
        planned_path= straight_path;
        return straight_path;
    }
    else {
        planned_path = previous_path;
        return previous_path;
    }
}

path straight::generate_path_following(void) {
    //如果车道线有效就更新规划点，无效就沿用之前的规划轨迹
    if (lane_info.left.valid == true && lane_info.right.valid == true) {
        //更新路径规划起始GPS和航向角
        path straight_path;
        straight_path.GPS_pos_init = GPS_position_cur;
        straight_path.path_angle_init = veh_path_angle;
        double z_temp1=10;
        double z_temp2=100;
        z_temp1=max(10.0,0.5*(veh_info.cur_speed*veh_info.veh_preferred_speed)*abs(veh_info.cur_speed-veh_info.veh_preferred_speed)/2);
        z_temp2=max(z_temp1+1,100.0);

        double car_follow_gap=200;//跟车距离（初始化为200m）
        double lead_veh_speed = 10;//m/s
        //计算跟车距离、前车车速等
        for (int i = 0; i < obstacle_info.size(); i++) {
            if (abs(obstacle_info[i].pos_x) < lane_info.lane_width()/2
                    && obstacle_info[i].pos_z>0) {//即在当前车道内，且在本车前方
                if (car_follow_gap > obstacle_info[i].pos_z) {
                    car_follow_gap = obstacle_info[i].pos_z;
                    lead_veh_speed = obstacle_info[i].v_z;
                }
            }
        }
        if (car_follow_gap<z_temp1 && lead_veh_speed<-1){
          z_temp1=max(1.0,car_follow_gap-5);
        }
        else if (car_follow_gap<z_temp1 && lead_veh_speed<2){
          z_temp1=max(1.0,car_follow_gap-1);
        }
        //沿车道线行驶，车道方程
        //path_segment1  变速
        path_segment path_segment_temp;
        path_segment_temp.init_point.z = 0;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(0);
        path_segment_temp.end_point.z = z_temp1;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp1);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        path_segment_temp.init_speed = veh_info.cur_speed;
        path_segment_temp.end_speed = max(0.01,min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed),lead_veh_speed));
        straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
        //path_segment2  匀速
        if(path_segment_temp.end_speed>0.3){
        path_segment_temp.init_point.z = z_temp1;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(z_temp1);
        path_segment_temp.end_point.z = z_temp2;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp2);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        path_segment_temp.init_speed = max(0.01,min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed),lead_veh_speed));
        path_segment_temp.end_speed = max(0.01,min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed), lead_veh_speed));
        straight_path.path_series.insert(straight_path.path_series.begin()+1, path_segment_temp);
        }
        planned_path= straight_path;
        return straight_path;
    }
    else {
        planned_path = previous_path;
        return previous_path;
    }
}

path straight::generate_path_braking(int brake_distance) {
    //如果车道线有效就更新规划点，无效就沿用之前的规划轨迹
    if (lane_info.left.valid == true && lane_info.right.valid == true) {
        //更新路径规划起始GPS和航向角
        path straight_path;
        straight_path.GPS_pos_init = GPS_position_cur;
        straight_path.path_angle_init = veh_path_angle;
        if(veh_info.cur_speed==0)
        {
          brake_distance=0;
          //不沿车道线行驶，直线
          path_segment path_segment_temp;
          path_segment_temp.init_point.z = 0;
          path_segment_temp.init_point.x = 0;
          path_segment_temp.end_point.z = 0;
          path_segment_temp.end_point.x = 0;
          path_segment_temp.is_lane_driving = 0;
          path_segment_temp.kappa = 0;
          path_segment_temp.init_speed = 0;
          path_segment_temp.end_speed = 0;
          straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
          planned_path= straight_path;
          return straight_path;
        }
        else {
          //不沿车道线行驶，直线
          path_segment path_segment_temp;
          path_segment_temp.init_point.z = 0;
          path_segment_temp.init_point.x = 0;
          path_segment_temp.end_point.z = brake_distance;
          path_segment_temp.end_point.x = lane_info.lateral_position_centerline(brake_distance);
          path_segment_temp.is_lane_driving = 0;
          path_segment_temp.kappa = 0;
          path_segment_temp.init_speed = veh_info.cur_speed;
          path_segment_temp.end_speed = 0;
          straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
          planned_path= straight_path;
          return straight_path;
        }

    }
    else {
        //紧急情况不能沿用上一次的规划
        //更新路径规划起始GPS和航向角
        path straight_path;
        straight_path.GPS_pos_init = GPS_position_cur;
        straight_path.path_angle_init = veh_path_angle;

        //非沿车道线行驶，直线
        path_segment path_segment_temp;
        path_segment_temp.init_point.z = 0;
        path_segment_temp.init_point.x = 0;
        path_segment_temp.end_point.z = brake_distance;
        path_segment_temp.end_point.x = 0;
        path_segment_temp.is_lane_driving = 0;
        path_segment_temp.kappa = 0;
        path_segment_temp.init_speed = veh_info.cur_speed;
        path_segment_temp.end_speed = 0;
        straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
        planned_path= straight_path;
        return straight_path;
    }
}




//path straight::speed_planning(void) {//跟车模型待优化
//    double car_follow_gap=200;//跟车距离（初始化为200m）
//    double lead_veh_speed = 0;//m/s
//    //计算跟车距离、前车车速等
//    for (int i = 0; i < obstacle_info.size(); i++) {
//        if (abs(obstacle_info[i].pos_x) < lane_info.lane_width()/2
//                && obstacle_info[i].pos_z>0) {//即在当前车道内，且在本车前方
//            if (car_follow_gap > obstacle_info[i].pos_z) {
//                car_follow_gap = obstacle_info[i].pos_z;
//                lead_veh_speed = obstacle_info[i].v_z;
//            }
//        }
//    }
//    if (car_follow_gap > 150) {//自由行驶
//        planned_path.path_series[0].init_speed = veh_info.cur_speed;
//        planned_path.path_series[0].end_speed = veh_info.cur_speed;
//        planned_path.path_series[1].init_speed = veh_info.cur_speed;
//        planned_path.path_series[1].end_speed
//                = min(lane_info.road_speed_limit, veh_info.veh_preferred_speed);
//    }
//    else if (lead_veh_speed <= 1 && car_follow_gap<veh_info.cur_speed*10) {//停车
//        planned_path.path_series.erase(planned_path.path_series.begin() + 1);
//        planned_path.path_series[0].end_point.z
//                = max(car_follow_gap - veh_info.veh_len - 2,(double)0);
//        planned_path.path_series[0].end_point.x = 0;
//        planned_path.path_series[0].is_lane_driving = 0;
//        planned_path.path_series[0].kappa = 0;
//        planned_path.path_series[0].init_speed = veh_info.cur_speed;
//        planned_path.path_series[0].end_speed = 0;
//    }
//    else {//跟车
//        double car_follow_speed=0;//根据跟车距离、当前车速计算的理想车速
//        //使用跟车模型计算合理的跟车车速IDM
//        double car_follow_gap_des = 0;//理想的跟车距离
//        car_follow_gap_des = max(veh_info.cur_speed * 5
//                                 + veh_info.cur_speed*(lead_veh_speed - veh_info.cur_speed)
//                                 / sqrt(2 * veh_info.max_acc*veh_info.max_dec), (double)0) + 10;
//        car_follow_speed = car_follow_speed + veh_info.max_acc*
//                (1 - pow(veh_info.cur_speed / veh_info.veh_preferred_speed, 1)
//                 - pow(car_follow_gap_des / car_follow_gap, 2));
//        //道路最高车速lane_info.road_speed_limit
//        //驾驶员目标车速veh_info.veh_preferred_speed
//        planned_path.path_series[0].init_speed = veh_info.cur_speed;
//        planned_path.path_series[0].end_speed = min(min(car_follow_speed,
//                                                        lane_info.road_speed_limit), veh_info.veh_preferred_speed);
//        planned_path.path_series[1].init_speed = planned_path.path_series[0].end_speed;
//        planned_path.path_series[1].end_speed = min(min(lead_veh_speed,
//                                                        lane_info.road_speed_limit), veh_info.veh_preferred_speed);
//    }
//    return planned_path;
//}

//path intersection::speed_planning(void) {//不知道变道后前方车辆的速度
//    //判断能否在绿灯时间内以当前车速通过路口
//    bool pass = false;
//    if (traffic_light_state == 1
//            && traffic_light_time_remaining > planned_path.path_series[0].path_segment_length_cal() / veh_info.cur_speed) {
//        pass = true;
//    }
//    else {
//        pass = false;
//    }
//    double turn_speed_limit = 6;//m/s 转弯车速限制
//    if (pass) {
//        //当前车速
//        planned_path.path_series[0].init_speed = veh_info.cur_speed;
//        //转弯车速限制
//        planned_path.path_series[0].end_speed = min(min(veh_info.cur_speed,
//                                                        turn_speed_limit), veh_info.veh_preferred_speed);
//        planned_path.path_series[1].init_speed = min(min(veh_info.cur_speed,
//                                                         turn_speed_limit), veh_info.veh_preferred_speed);
//        //转弯车速限制
//        planned_path.path_series[1].end_speed = min(min(veh_info.cur_speed,
//                                                        turn_speed_limit), veh_info.veh_preferred_speed);
//        planned_path.path_series[2].init_speed = min(min(veh_info.cur_speed,
//                                                         turn_speed_limit), veh_info.veh_preferred_speed);
//        //道路车速限制
//        planned_path.path_series[2].end_speed= min(min(veh_info.cur_speed,
//                                                       lane_info.road_speed_limit), veh_info.veh_preferred_speed);
//        //道路最高车速lane_info.road_speed_limit
//        //驾驶员目标车速veh_info.veh_preferred_speed
//    }
//    else {//停车
//        planned_path.path_series.erase(planned_path.path_series.begin() + 2);
//        planned_path.path_series.erase(planned_path.path_series.begin() + 1);
//        planned_path.path_series[0].init_speed = veh_info.cur_speed;
//        planned_path.path_series[0].end_speed = 0;
//    }
//    return planned_path;
//}


//CoordinateList straight::speed_planning_astar(void){
//    //转换到车道坐标后再用A*进行规划，避免车辆不沿着车道行驶
//    AStar::Generator generator;
//    //set environment
//    generator.setWorldSize({0, 0},{100, 100});//左下角与右上角坐标
//    generator.setHeuristic(AStar::Heuristic::euclidean);
//    generator.setDiagonalMovement(true);
//    generator.clearCollisions();
//    for(int i=0;i<100;i++){
//        for(int j=0;j<100;j++){
//            if(obstacle_map_temporal_spatio[i][j]==1){
//                generator.addCollision({i,j});
//            }
//        }
//    }
//    CoordinateList path = generator.findPath({0,0}, {100,100});//到达里程终点即可
//    return path;
//}


path change_lane::generate_path(void) {
    if (change_lane_direction == 1) {//左变道
        //首先根据障碍物地图确定能否变道，若不能，则先继续沿车道行驶，同straight
        double lane_width = lane_info.lane_width();
        double lead_veh_time_gap=100, left_lead_veh_time_gap=100, left_follow_veh_time_gap=100;
        for (int i = 0; i < obstacle_info.size(); i++) {
            //计算障碍物与当前车的距离
            double z = sqrt(pow(obstacle_info[i].pos_z,2)+pow(obstacle_info[i].pos_x,2));//前方＞0,后方＜0
            //计算障碍物与当前车道偏离的横向距离
            double frenet_x = lane_info.distance_point_lane_centerline(obstacle_info[i].pos_z,
                                                                       obstacle_info[i].pos_x);
            double v_s = max(abs(obstacle_info[i].v_s),abs(veh_info.cur_speed));//向前行驶＞0，向后行驶＜0
            if (v_s == 0) {
                v_s = 1;
            }
            //判断该车在目标车道还是当前车道，或者在其他车道，不影响当前车行驶
            if (frenet_x >= -lane_width / 2 && frenet_x <= lane_width / 2 && z>0) {
                //若在当前车道，计算当前车辆与前方车辆的时距
                lead_veh_time_gap = min(lead_veh_time_gap, abs(z / v_s));
            }
            else if (frenet_x >= -lane_width*3 / 2 && frenet_x <= -lane_width / 2) {
                //若在左侧车道，计算当前车辆与左侧前方、后方车辆的最小时距
                if (z >= 0) {
                    left_lead_veh_time_gap = min(left_lead_veh_time_gap, abs(z / v_s));
                }
                else {
                    left_follow_veh_time_gap = min(left_follow_veh_time_gap, abs(z / v_s));
                }
            }
            cout<<"obstacle_vs="<<obstacle_info[i].v_s<<endl;
        }
        cout<<"lead_veh_time_gap="<<lead_veh_time_gap<<endl;
        cout<<"left_follow_veh_time_gap="<<left_follow_veh_time_gap<<endl;
        cout<<"left_lead_veh_time_gap="<<left_lead_veh_time_gap<<endl;
        //判断是否满足安全距离，阈值待修改，且车道线类型表明允许换道，若满足则规划变道路径
        if (left_follow_veh_time_gap > 5 && left_lead_veh_time_gap > 5 && lead_veh_time_gap > 5
                && lane_info.left.lane_line_type!=1 &&lane_info.left.lane_line_type!=3
                &&lane_info.left.lane_line_type!=4 ) {
          cout<<"leftchange"<<endl;
            //更新路径规划起始GPS和航向角
            path change_lane_path;
            change_lane_path.GPS_pos_init = GPS_position_cur;
            change_lane_path.path_angle_init = veh_path_angle;
            //规划点1、2
            double z_temp1 = 20;//规划点1的纵向位置初始化
            double z_temp2 = 100;//规划点2的纵向位置初始化
            //点1的纵向位置还需要考虑车速
            z_temp1=abs(lane_info.lane_width())/tan(veh_info.safety_steering_angle_cal())+2;
            if (veh_info.veh_preferred_speed<veh_info.cur_speed){
              z_temp1=max(z_temp1,0.5*(veh_info.veh_preferred_speed+veh_info.cur_speed)*abs(veh_info.veh_preferred_speed-veh_info.cur_speed)/2);
            }
            //非沿车道线行驶，直线，变道过程
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = 0;
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_left_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 0;
            path_segment_temp.kappa = 0;
            path_segment_temp.init_speed = veh_info.cur_speed;
            path_segment_temp.end_speed = max(veh_info.veh_preferred_speed,veh_info.cur_speed);
            change_lane_path.path_series.insert(change_lane_path.path_series.begin(),
                                                path_segment_temp);
            //沿车道线行驶，左侧车道方程
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_left_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_left_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.left_center_line_cal().C0;
            path_segment_temp.C1 = lane_info.left_center_line_cal().C1;
            path_segment_temp.C2 = lane_info.left_center_line_cal().C2;
            path_segment_temp.C3 = lane_info.left_center_line_cal().C3;
            path_segment_temp.init_speed = max(veh_info.veh_preferred_speed,veh_info.cur_speed);
            path_segment_temp.end_speed = max(veh_info.veh_preferred_speed,min(min(veh_info.cur_speed,
                                                  lane_info.road_speed_limit), veh_info.veh_preferred_speed));
            change_lane_path.path_series.insert(change_lane_path.path_series.begin() + 1,
                                                path_segment_temp);
            planned_path = change_lane_path;
            //道路最高车速lane_info.road_speed_limit
            //驾驶员目标车速veh_info.veh_preferred_speed
            return change_lane_path;
        }
        else {//依然沿当前车道行驶
            //更新路径规划起始GPS和航向角
          cout<<"keep"<<endl;
            path straight_path;
            straight_path.GPS_pos_init = GPS_position_cur;
            straight_path.path_angle_init = veh_path_angle;
            double z_temp1=10;
            double z_temp2=100;
            z_temp1=max(z_temp1,0.5*(veh_info.cur_speed*veh_info.veh_preferred_speed)*abs(veh_info.cur_speed-veh_info.veh_preferred_speed)/2);
            z_temp2=max(z_temp2,z_temp1+1);
            double car_follow_gap=200;//跟车距离（初始化为200m）
            double lead_veh_speed = 10;//m/s
            //计算跟车距离、前车车速等
            for (int i = 0; i < obstacle_info.size(); i++) {
                if (abs(obstacle_info[i].pos_x) < lane_info.lane_width()/2
                        && obstacle_info[i].pos_z>0) {//即在当前车道内，且在本车前方
                    if (car_follow_gap > obstacle_info[i].pos_z) {
                        car_follow_gap = obstacle_info[i].pos_z;
                        lead_veh_speed = obstacle_info[i].v_z;
                    }
                }
            }
            if (car_follow_gap<z_temp1 && lead_veh_speed<-1){
              z_temp1=max(1.0,car_follow_gap-5);
            }
            else if (car_follow_gap<z_temp1 && lead_veh_speed<2){
              z_temp1=max(1.0,car_follow_gap-1);
            }
            cout<<"z_temp1="<<z_temp1<<endl;
            //沿车道线行驶，车道方程
            //path_segment1  变速
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = lane_info.lateral_position_centerline(0);
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.center_line_cal().C0;
            path_segment_temp.C1 = lane_info.center_line_cal().C1;
            path_segment_temp.C2 = lane_info.center_line_cal().C2;
            path_segment_temp.C3 = lane_info.center_line_cal().C3;
            path_segment_temp.init_speed = veh_info.cur_speed;
            path_segment_temp.end_speed = max(0.01,min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed),lead_veh_speed));
            straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
            cout<<"z_temp1="<<z_temp1<<endl;
            cout<<"end_speed="<<path_segment_temp.end_speed<<endl;
            //path_segment2  匀速
            if (path_segment_temp.end_speed>0.3){
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.center_line_cal().C0;
            path_segment_temp.C1 = lane_info.center_line_cal().C1;
            path_segment_temp.C2 = lane_info.center_line_cal().C2;
            path_segment_temp.C3 = lane_info.center_line_cal().C3;
            path_segment_temp.init_speed = min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed),lead_veh_speed);
            path_segment_temp.end_speed = min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed), lead_veh_speed);
            straight_path.path_series.insert(straight_path.path_series.begin()+1, path_segment_temp);
            }
            planned_path= straight_path;
            return straight_path;
        }
    }
    else if (change_lane_direction == 2) {//右变道
        //首先根据障碍物地图确定能否变道，若不能，则先继续沿车道行驶，同straight
        double lane_width = lane_info.lane_width();
        double lead_veh_time_gap = 100, right_lead_veh_time_gap = 100,
                right_follow_veh_time_gap = 100;
        for (int i = 0; i < obstacle_info.size(); i++) {
            double z = obstacle_info[i].pos_z;//前方＞0,后方＜0
            //计算障碍物与当前车道偏离的横向距离
            double frenet_x = lane_info.distance_point_lane_centerline(obstacle_info[i].pos_z,
                                                                       obstacle_info[i].pos_x);
            double v_s = obstacle_info[i].v_s;//向前行驶＞0，向后行驶＜0
            if (v_s == 0) {
                v_s = 1;
            }
            //判断该车在目标车道还是当前车道，或者在其他车道，不影响当前车行驶
            if (frenet_x >= -lane_width / 2 && frenet_x <= lane_width / 2 && z>0) {
                //若在当前车道，计算当前车辆与前方车辆的时距
                lead_veh_time_gap = min(lead_veh_time_gap, abs(z / v_s));
            }
            else if (frenet_x >= lane_width / 2 && frenet_x <= lane_width * 3 / 2) {
                //若在右侧车道，计算当前车辆与右侧前方、后方车辆的最小时距
                if (z >= 0) {
                    right_lead_veh_time_gap = min(right_lead_veh_time_gap, abs(z / v_s));
                }
                else {
                    right_follow_veh_time_gap = min(right_follow_veh_time_gap, abs(z / v_s));
                }
            }
        }
        //判断是否满足安全距离，阈值待修改，且车道线类型表明允许换道，若满足则规划变道路径
        if (right_follow_veh_time_gap > 5 && right_lead_veh_time_gap > 5
                && lead_veh_time_gap > 5 && lane_info.right.lane_line_type!=1 &&lane_info.right.lane_line_type!=3
                &&lane_info.right.lane_line_type!=4) {
            //更新路径规划起始GPS和航向角
            path change_lane_path;
            change_lane_path.GPS_pos_init = GPS_position_cur;
            change_lane_path.path_angle_init = veh_path_angle;
            //规划点1、2
            double z_temp1 = 20;//规划点1的纵向位置
            double z_temp2 = 100;//规划点2的纵向位置
            //点1的纵向位置还需要考虑车速
            z_temp1=abs(lane_info.lane_width())/tan(veh_info.safety_steering_angle_cal())+2;
            if (veh_info.veh_preferred_speed<veh_info.cur_speed){
              z_temp1=max(z_temp1,0.5*(veh_info.veh_preferred_speed+veh_info.cur_speed)*abs(veh_info.veh_preferred_speed-veh_info.cur_speed)/2);
            }
            //非沿车道线行驶，直线，变道过程
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = 0;
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_right_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 0;
            path_segment_temp.kappa = 0;
            path_segment_temp.init_speed = max(double(2),veh_info.cur_speed);
            path_segment_temp.end_speed = max(double(2),veh_info.cur_speed);
            change_lane_path.path_series.insert(change_lane_path.path_series.begin(),
                                                path_segment_temp);
            //沿车道线行驶，右侧车道方程
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_right_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_right_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.right_center_line_cal().C0;
            path_segment_temp.C1 = lane_info.right_center_line_cal().C1;
            path_segment_temp.C2 = lane_info.right_center_line_cal().C2;
            path_segment_temp.C3 = lane_info.right_center_line_cal().C3;
            path_segment_temp.init_speed = max(double(2),veh_info.cur_speed);
            path_segment_temp.end_speed = max(double(2),min(min(veh_info.cur_speed,
                                                  lane_info.road_speed_limit), veh_info.veh_preferred_speed));
            change_lane_path.path_series.insert(change_lane_path.path_series.begin() + 1,
                                                path_segment_temp);
            planned_path = change_lane_path;
            return change_lane_path;
        }
        else {//依然沿当前车道行驶
            //更新路径规划起始GPS和航向角
            path straight_path;
            straight_path.GPS_pos_init = GPS_position_cur;
            straight_path.path_angle_init = veh_path_angle;
            double z_temp1=10;
            double z_temp2=100;
            z_temp1=max(z_temp1,0.5*(veh_info.cur_speed*veh_info.veh_preferred_speed)*abs(veh_info.cur_speed-veh_info.veh_preferred_speed)/2);
            z_temp2=max(z_temp2,z_temp1+1);
            double car_follow_gap=200;//跟车距离（初始化为200m）
            double lead_veh_speed = 10;//m/s
            //计算跟车距离、前车车速等
            for (int i = 0; i < obstacle_info.size(); i++) {
                if (abs(obstacle_info[i].pos_x) < lane_info.lane_width()/2
                        && obstacle_info[i].pos_z>0) {//即在当前车道内，且在本车前方
                    if (car_follow_gap > obstacle_info[i].pos_z) {
                        car_follow_gap = obstacle_info[i].pos_z;
                        lead_veh_speed = obstacle_info[i].v_z;
                    }
                }
            }
            if (car_follow_gap<z_temp1 && lead_veh_speed<-1){
              z_temp1=max(1.0,car_follow_gap-5);
            }
            else if (car_follow_gap<z_temp1 && lead_veh_speed<2){
              z_temp1=max(1.0,car_follow_gap-1);
            }
            //沿车道线行驶，车道方程
            //path_segment1  变速
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = lane_info.lateral_position_centerline(0);
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.center_line_cal().C0;
            path_segment_temp.C1 = lane_info.center_line_cal().C1;
            path_segment_temp.C2 = lane_info.center_line_cal().C2;
            path_segment_temp.C3 = lane_info.center_line_cal().C3;
            path_segment_temp.init_speed = veh_info.cur_speed;
            path_segment_temp.end_speed = max(0.01,min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed),lead_veh_speed));
            straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
            //path_segment2  匀速
            if (path_segment_temp.end_speed>0.3){
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.center_line_cal().C0;
            path_segment_temp.C1 = lane_info.center_line_cal().C1;
            path_segment_temp.C2 = lane_info.center_line_cal().C2;
            path_segment_temp.C3 = lane_info.center_line_cal().C3;
            path_segment_temp.init_speed = min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed),lead_veh_speed);
            path_segment_temp.end_speed = min(min(lane_info.road_speed_limit, veh_info.veh_preferred_speed), lead_veh_speed);
            straight_path.path_series.insert(straight_path.path_series.begin()+1, path_segment_temp);
            }
            planned_path= straight_path;
            return straight_path;
        }
    }
}

//CoordinateList change_lane::speed_planning_astar(void){
//    //转换到车道坐标后再用A*进行规划，避免车辆不沿着车道行驶
//    AStar::Generator generator;
//    //set environment
//    generator.setWorldSize({0, 0},{100, 100});//左下角与右上角坐标
//    generator.setHeuristic(AStar::Heuristic::euclidean);
//    generator.setDiagonalMovement(true);
//    generator.clearCollisions();
//    for(int i=0;i<100;i++){
//        for(int j=0;j<100;j++){
//            if(obstacle_map_temporal_spatio[i][j]==1){
//                generator.addCollision({i,j});
//            }
//        }
//    }
//    CoordinateList path = generator.speed_plan({0,0}, {100,100});//到达里程终点即可
//    return path;
//}

void shortrange_planning::obstacle_path_temporal_spatio_figure(void) {//计算障碍物在ST图上的分布
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            obstacle_map_temporal_spatio[i][j] = 0;//赋初值为0，表示没有障碍物
        }
    }
    for (int i = 0; i < obstacle_info.size(); i++) {
        //首先根据path类型以及obs的pos_x和pos_z，计算obs的pos_s和pos_l
        double length_temp=0;
        double pos_l_temp=1000;
        double pos_s_temp=1000;
        obstacle_info[i].pos_l = 1000;
        for (int j = 0; j < planned_path.path_series.size(); j++) {
            if(obstacle_info[i].pos_z>=planned_path.path_series[j].init_point.z
                    && obstacle_info[i].pos_z<=planned_path.path_series[j].end_point.z){
                pos_l_temp
                        = planned_path.path_series[j].path_segment_distance_with_obstacle(obstacle_info[i]);
                if (pos_l_temp < obstacle_info[i].pos_l) {
                    obstacle_info[i].pos_l = pos_l_temp;
                    obstacle_info[i].pos_s = obstacle_info[i].pos_z + length_temp;//这显然是不对的，做了简化
                    obstacle_info[i].calculate_speed_frenet(0, pos_l_temp, veh_info.cur_speed);
                }
            }
            length_temp = length_temp + planned_path.path_series[j].path_segment_length_cal();
        }//第i个障碍物与第j条轨迹,选出最接近的一条轨迹
        //根据pos_l和v_l计算出障碍物与轨迹的交点
        if (abs(obstacle_info[i].v_l) <= 0.3) {//认为横向不动
            if (abs(obstacle_info[i].pos_l) < obstacle_info[i].width * 2) {
                for (int t = 0; t < 50; t++) {
                    int pos_temp = round(obstacle_info[i].pos_s + obstacle_info[i].v_s * t);
                    //          pos_temp = max(1, pos_temp);
                    //          pos_temp = min(99, pos_temp);
                    if(pos_temp>=1 && pos_temp<=98){
                        obstacle_map_temporal_spatio[t][pos_temp]=1;
                        obstacle_map_temporal_spatio[t][pos_temp+1] = 1;
                        obstacle_map_temporal_spatio[t][pos_temp-1] = 1;
                        obstacle_map_temporal_spatio[t][pos_temp+2] = 1;
                        obstacle_map_temporal_spatio[t][pos_temp-2] = 1;
                    }
                }
            }
        }
        else{//与轨迹有交点，但不是一直在轨迹上
            int t_temp = obstacle_info[i].pos_l / obstacle_info[i].v_l;
            int s_temp = obstacle_info[i].pos_s + obstacle_info[i].v_s * t_temp;
            if(s_temp>=0 && s_temp<99){
                obstacle_map_temporal_spatio[t_temp][s_temp] = 1;
                obstacle_map_temporal_spatio[t_temp][s_temp - 1] = 1;
                obstacle_map_temporal_spatio[t_temp][s_temp + 1] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp - 1] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp + 1] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp - 2] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp + 2] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp - 1] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp + 1] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp - 2] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp + 2] = 1;
            }
        }
        //给栅格地图赋值
    }
}

shortrange_planning::shortrange_planning(){
    lane lane_temp;
    lane_info=lane_temp;//车道信息
    vehicle veh_temp;
    veh_info=veh_temp;//车辆信息
    vector<obstacle> obstacle_temp;
    obstacle obs_temp;
    obstacle_temp.insert(obstacle_temp.begin(),obs_temp);
    obstacle_info=obstacle_temp;//障碍物详细信息
    driving_intention=0;//短程驾驶意图（列表：0-直行，1-左变道，2-右变道等等）
    GPS_position_cur=vec2d(31.0,121.0);
    veh_path_angle=0;
}

shortrange_planning::shortrange_planning(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                                         int driving_intention_in,vec2d GPS_cur, double path_angle){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
}

void shortrange_planning::planned_path_cal(){
    out_path.clear();
    //output
    double path_interpolate[300][4]={0};
    double z_record=planned_path.path_series[0].init_point.z;
    double x_record=planned_path.path_series[0].init_point.x;
    double v_record=0;
    double t_record=0;
    int num=0;
    double z_temp=0;
    //interpolate path
    for(int i=0;i<planned_path.path_series.size();i++){//遍历每一条路径
        path_segment path_temp=planned_path.path_series[i];
        double length_temp=path_temp.path_segment_length_cal();//路径长度
        double vmean_temp=(path_temp.end_speed+path_temp.init_speed)/2;//平均速度
        double t_len_temp=min(20.0,length_temp/vmean_temp);//耗时
        double tan_temp=0;
      if(path_temp.is_lane_driving==1){
        for(double t_temp=0; t_temp<t_len_temp;t_temp=t_temp+0.1){
            v_record=(path_temp.end_speed-path_temp.init_speed)*t_temp/t_len_temp+path_temp.init_speed;
            t_record=t_record+0.1;
            tan_temp=path_temp.C1+path_temp.C2*z_temp+path_temp.C3*z_temp*z_temp;
            z_temp=z_temp+0.1*v_record/sqrt(1+tan_temp*tan_temp);
            z_record=z_temp;
            x_record=path_temp.C0+z_temp*path_temp.C1+z_temp*z_temp*path_temp.C2+
                    +z_temp*z_temp*z_temp*path_temp.C3;
            if(num<300){
              path_interpolate[num][0]=t_record;
              path_interpolate[num][1]=z_record;
              path_interpolate[num][2]=x_record;
              path_interpolate[num][3]=v_record;
              num=num+1;
              //cout<<num<<" "<<t_temp<<endl;
            }
        }
      }

      else if(path_temp.kappa==0){
          for(double t_temp=0; t_temp<t_len_temp;t_temp=t_temp+0.1){
              t_record=t_record+0.1;
              v_record=(path_temp.end_speed-path_temp.init_speed)*t_temp/t_len_temp+path_temp.init_speed;
              tan_temp=(path_temp.end_point.x-path_temp.init_point.x)/(path_temp.end_point.z-path_temp.init_point.z);
              z_temp=z_temp+0.1*v_record/sqrt(1+tan_temp*tan_temp);
              z_record=z_temp;
              x_record=(z_temp-path_temp.init_point.z)*(path_temp.end_point.x-path_temp.init_point.x)/(path_temp.end_point.z-path_temp.init_point.z);
              if(num<300){
                path_interpolate[num][0]=t_record;
                path_interpolate[num][1]=z_record;
                path_interpolate[num][2]=x_record;
                path_interpolate[num][3]=v_record;
                num=num+1;
                //cout<<num<<" "<<t_temp<<endl;
              }
          }
      }
      else{
          for(double t_temp=0; t_temp<t_len_temp;t_temp=t_temp+0.1){
              t_record=t_record+0.1;
              v_record=(path_temp.end_speed-path_temp.init_speed)*t_temp/t_len_temp+path_temp.init_speed;
              tan_temp=(path_temp.end_point.x-path_temp.init_point.x)/(path_temp.end_point.z-path_temp.init_point.z);
              z_temp=z_temp+0.1*v_record/sqrt(1+tan_temp*tan_temp);
              z_record=z_temp;
              x_record=(z_temp-path_temp.init_point.z)*(path_temp.end_point.x-path_temp.init_point.x)/(path_temp.end_point.z-path_temp.init_point.z);
              if(num<300){
                path_interpolate[num][0]=t_record;
                path_interpolate[num][1]=z_record;
                path_interpolate[num][2]=x_record;
                path_interpolate[num][3]=v_record;
                num=num+1;
                //cout<<num<<" "<<t_temp<<endl;
              }
          }
      }
    }
    //多项式拟合
    poly p;
    int deg_in=3;
    std::vector<double> x_poly;
    std::vector<double> y_poly;
    if (num>2){
        for(int i=0;i<num-1;i++){
            //cout<<path[i].x<<","<<path[i].y<<endl;
            x_poly.push_back(path_interpolate[i][1]);
            y_poly.push_back(path_interpolate[i][2]);
        }
        p.inter(deg_in,x_poly,y_poly);
        double z_record,x_record,v_record=veh_info.veh_preferred_speed,t_record=0;
        double dx,dt,dz;
        path_point a;
        int num1=0;
        z_record=planned_path.path_series[0].init_point.z;
        x_record=planned_path.path_series[0].init_point.x;
        v_record=0;
        t_record=0;
        z_temp=0;
        for(int i=0;i<planned_path.path_series.size();i++){//遍历每一条路径
            path_segment path_temp=planned_path.path_series[i];
            double length_temp=path_temp.path_segment_length_cal();//路径长度
            double vmean_temp=(path_temp.end_speed+path_temp.init_speed)/2;//平均速度
            double t_len_temp=min(20.0,length_temp/vmean_temp);//耗时
            double tan_temp=0;
            for(double t_temp=0; t_temp<t_len_temp;t_temp=t_temp+0.1){
                v_record=(path_temp.end_speed-path_temp.init_speed)*t_temp/t_len_temp+path_temp.init_speed;
                t_record=t_record+0.1;
                tan_temp=path_temp.C1+path_temp.C2*z_temp+path_temp.C3*z_temp*z_temp;
                z_temp=z_temp+0.1*v_record/sqrt(1+tan_temp*tan_temp);
                z_record=z_temp;
                x_record=p.mat[0][0]*z_temp*z_temp*z_temp+p.mat[1][0]*z_temp*z_temp+p.mat[2][0]*z_temp+p.mat[3][0];
                a.t=t_record;
                a.z=z_record;
                a.x=x_record;
                a.v=v_record;
                out_path.insert(out_path.begin()+num1,a);
                num1=num1+1;
            }
        }
    }
    //不拟合
//    path_point a;
//    for (int i=0;i<num-1;i++){
//        a.t=path_interpolate[i][0];
//        a.z=path_interpolate[i][1];
//        a.x=path_interpolate[i][2];
//        a.v=path_interpolate[i][3];
//        out_path.insert(out_path.begin()+i,a);
//    }
}

//path intersection::generate_path(void) {
//    path intersection_path;
//    //更新路径规划起始GPS和航向角
//    intersection_path.GPS_pos_init = GPS_position_cur;
//    intersection_path.path_angle_init = veh_path_angle;
//    vec2d point_temp1, point_temp2;
//    point_temp1 = GPS_to_local_coordinate(GPS_position_cur, GPS_out_road_section,
//                                          veh_path_angle);
//    point_temp2 = GPS_to_local_coordinate(GPS_position_cur, GPS_in_road_section,
//                                          veh_path_angle);

//    if (intersection_type == 0) {//直行通过路口
//        //沿车道线行驶
//        path_segment path_segment_temp;
//        path_segment_temp.init_point.z = 0;
//        path_segment_temp.init_point.x = 0;
//        path_segment_temp.end_point.z = point_temp1.z;
//        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(point_temp1.z);
//        path_segment_temp.is_lane_driving = 1;
//        path_segment_temp.C0 = lane_info.center_line_cal().C0;
//        path_segment_temp.C1 = lane_info.center_line_cal().C1;
//        path_segment_temp.C2 = lane_info.center_line_cal().C2;
//        path_segment_temp.C3 = lane_info.center_line_cal().C3;
//        intersection_path.path_series.insert(intersection_path.path_series.begin(), path_segment_temp);
//        //路口连接线，直线
//        path_segment_temp.init_point.z = point_temp1.z;
//        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(point_temp1.z);
//        path_segment_temp.end_point.z = point_temp2.z;
//        path_segment_temp.end_point.x = point_temp2.x;
//        path_segment_temp.is_lane_driving = 0;
//        path_segment_temp.kappa = 0;
//        intersection_path.path_series.insert(intersection_path.path_series.begin() + 1,
//                                             path_segment_temp);
//        //因为识别不出后一段路的车道线，因此用直线代替，后面识别出来后再更新
//        path_segment_temp.init_point.z = point_temp2.z;
//        path_segment_temp.init_point.x = point_temp2.x;
//        path_segment_temp.end_point.z = point_temp2.z+ 100;
//        path_segment_temp.end_point.x = point_temp2.x
//                + lane_info.center_line_cal().C1*100;//预估斜率与当前车道相同
//        path_segment_temp.is_lane_driving = 0;//应该识别不出来转弯后的车道线，所以按照直线规划
//        path_segment_temp.kappa = 0;
//        intersection_path.path_series.insert(intersection_path.path_series.begin() + 2,
//                                             path_segment_temp);
//    }
//    else if (intersection_type == 1) {//左转
//        //沿车道线行驶
//        path_segment path_segment_temp;
//        path_segment_temp.init_point.z = 0;
//        path_segment_temp.init_point.x = 0;
//        path_segment_temp.end_point.z = point_temp1.z;
//        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(point_temp1.z);
//        path_segment_temp.is_lane_driving = 1;
//        path_segment_temp.C0 = lane_info.center_line_cal().C0;
//        path_segment_temp.C1 = lane_info.center_line_cal().C1;
//        path_segment_temp.C2 = lane_info.center_line_cal().C2;
//        path_segment_temp.C3 = lane_info.center_line_cal().C3;
//        intersection_path.path_series.insert(intersection_path.path_series.begin(), path_segment_temp);
//        //路口连接线，圆弧
//        path_segment_temp.init_point.z = point_temp1.z;
//        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(point_temp1.z);
//        path_segment_temp.end_point.z = point_temp2.z;
//        path_segment_temp.end_point.x = point_temp2.x;
//        path_segment_temp.is_lane_driving = 0;
//        path_segment_temp.direction = 0;//左转圆弧
//        double dev_z = abs(path_segment_temp.init_point.z - path_segment_temp.end_point.z);
//        double dev_x = abs(path_segment_temp.init_point.x - path_segment_temp.end_point.x);
//        double R;//计算合适的半径，半径计算方法待修改
//        if( dev_z/dev_x > 1 ) {
//            R = dev_z * dev_z / dev_x;
//        }
//        else {
//            R = dev_x * dev_x / dev_z;
//        }
//        path_segment_temp.kappa = 1/R;
//        intersection_path.path_series.insert(intersection_path.path_series.begin() + 1,
//                                             path_segment_temp);
//        //因为识别不出后一段路的车道线，因此用直线代替，后面识别出来后再更新
//        path_segment_temp.init_point.z = point_temp2.z;
//        path_segment_temp.init_point.x = point_temp2.x;
//        path_segment_temp.end_point.z = point_temp2.z;
//        path_segment_temp.end_point.x = point_temp2.x -100;//预估的直线
//        path_segment_temp.is_lane_driving = 0;//应该识别不出来转弯后的车道线，所以按照直线规划
//        path_segment_temp.kappa = 0;
//        intersection_path.path_series.insert(intersection_path.path_series.begin() + 2,
//                                             path_segment_temp);
//    }
//    else{//右转
//        //沿车道线行驶
//        path_segment path_segment_temp;
//        path_segment_temp.init_point.z = 0;
//        path_segment_temp.init_point.x = 0;
//        path_segment_temp.end_point.z = point_temp1.z;
//        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(point_temp1.z);
//        path_segment_temp.is_lane_driving = 1;
//        path_segment_temp.C0 = lane_info.center_line_cal().C0;
//        path_segment_temp.C1 = lane_info.center_line_cal().C1;
//        path_segment_temp.C2 = lane_info.center_line_cal().C2;
//        path_segment_temp.C3 = lane_info.center_line_cal().C3;
//        intersection_path.path_series.insert(intersection_path.path_series.begin(), path_segment_temp);
//        //路口连接线，圆弧
//        path_segment_temp.init_point.z = point_temp1.z;
//        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(point_temp1.z);
//        path_segment_temp.end_point.z = point_temp2.z;
//        path_segment_temp.end_point.x = point_temp2.x;
//        path_segment_temp.is_lane_driving = 0;
//        path_segment_temp.direction = 1;//右转圆弧
//        double dev_z = abs(path_segment_temp.init_point.z - path_segment_temp.end_point.z);
//        double dev_x = abs(path_segment_temp.init_point.x - path_segment_temp.end_point.x);
//        double R;//计算合适的半径，半径计算方法待修改
//        if (dev_z / dev_x > 1) {
//            R = dev_z * dev_z / dev_x;
//        }
//        else {
//            R = dev_x * dev_x / dev_z;
//        }
//        path_segment_temp.kappa = 1 / R;
//        intersection_path.path_series.insert(intersection_path.path_series.begin() + 1,
//                                             path_segment_temp);
//        //因为识别不出后一段路的车道线，因此用直线代替，后面识别出来后再更新
//        path_segment_temp.init_point.z = point_temp2.z;
//        path_segment_temp.init_point.x = point_temp2.x;
//        path_segment_temp.end_point.z = point_temp2.z;
//        path_segment_temp.end_point.x = point_temp2.x + 100;//预估的直线
//        path_segment_temp.is_lane_driving = 0;//应该识别不出来转弯后的车道线，所以按照直线规划
//        path_segment_temp.kappa = 0;
//        intersection_path.path_series.insert(intersection_path.path_series.begin() + 2,
//                                             path_segment_temp);
//    }
//    planned_path = intersection_path;
//    return intersection_path;
//}

//CoordinateList intersection::generate_path_astar(void){
//    path intersection_path;
//    //更新路径规划起始GPS和航向角
//    intersection_path.GPS_pos_init = GPS_position_cur;
//    intersection_path.path_angle_init = veh_path_angle;
//    vec2d point_temp1, point_temp2;
//    point_temp1 = GPS_to_local_coordinate(GPS_position_cur, GPS_out_road_section,
//                                          veh_path_angle);
//    point_temp2 = GPS_to_local_coordinate(GPS_position_cur, GPS_in_road_section,
//                                          veh_path_angle);
//    //转换到车道坐标后再用A*进行规划，避免车辆不沿着车道行驶
//    AStar::Generator generator;
//    //set environment
//    generator.setWorldSize({-20,0},{20, 150});//左下角与右上角坐标
//    generator.setHeuristic(AStar::Heuristic::euclidean);
//    generator.setDiagonalMovement(true);
//    generator.clearCollisions();
//    for(int i=0;i<obstacle_info.size();i++){
//        int x_c=obstacle_info[i].pos_x
//                -lane_info.lateral_position_centerline(obstacle_info[i].pos_z);//frenet coordinate x
//        int z_c=obstacle_info[i].pos_z;// cartesian coordinate z
//        int w=obstacle_info[i].width;
//        int h=obstacle_info[i].width*1.5;
//        int w_v=veh_info.veh_width;//vehicle width
//        for(int x=x_c-(w+w_v)/2-1;x<x_c+(w+w_v)/2+2;x++){
//            for(int y=z_c-(h+w_v)/2-1;y<z_c+(h+w_v)/2+2;y++){
//                generator.addCollision({x,y});
//            }
//        }
//    }

//    //注意此时的坐标系是与换道后车道中心线相对应的坐标系
//    //generate path
//    CoordinateList path;
//    int init_veh_pos_x=-lane_info.lateral_position_centerline(0);
//    int init_veh_pos_z=0;
//    int end_veh_pos_x=0;
//    int end_veh_pos_z=point_temp1.z;
//    for(int i=0;i<end_veh_pos_z;i++) {
//        path.push_back({lane_info.lateral_position_centerline(i),i});
//    }
//    init_veh_pos_x=end_veh_pos_x;
//    init_veh_pos_z=end_veh_pos_z;
//    end_veh_pos_x=point_temp2.x-lane_info.lateral_position_centerline(point_temp2.z);
//    end_veh_pos_z=point_temp2.z;
//    CoordinateList path_temp2 = generator.findPath({init_veh_pos_x,init_veh_pos_z},
//    {end_veh_pos_x,end_veh_pos_z});
//    for(int i=path_temp2.size()-1;i>=0;i--) {
//        path_temp2[i].x=path_temp2[i].x+lane_info.lateral_position_centerline(path_temp2[i].y);
//        path.push_back(path_temp2[i]);
//    }
//    return path;

//}



vector<path_point> intersection::generate_path_rrt(void){
    vec2d point_temp1, point_temp2;
    point_temp1 = GPS_out_road_section;
    point_temp2 = GPS_in_road_section;
    int direction=intersection_type;//路口转向方向，0-直行，1-左转，2-右转

    //临时添加，测试用
    //point_temp2.z=10;
    //point_temp2.x=-10;
    //int direction=1;

    srand(time(NULL));
    Utils::Point<int> start,finish,origin;
    start.x=0;
    start.y=0;
    finish.x=point_temp2.z;
    finish.y=point_temp2.x;
    origin.x=0;
    origin.y=0;


    RRT<int> test;
    test.setEndPoints(start,finish);
   // test.setCheckPointFunction(**(check));
    test.setStepLength(2);
    test.setHalfDimensions(100.0,100.0);
    test.setBiasParameter(50);
    test.setOrigin(origin);
    test.setMaxIterations(1000);
    test.plan(obstacle_info,direction);
    cout<<"#################################################"<<endl;
    deque<Utils::Point<int> > path=test.getPointsOnPath();

    //不拟合直接输出
//    double z_record=0,x_record=0,v_record=0,t_record=0;
//    double dx,dt,dz;
//    path_point a;
//    int num=0;
//    for(int i=0;i<path.size();i++){
//        z_record=path[i].x;
//        x_record=path[i].y;
//        v_record=5;
//        dt=5/5;
//        t_record=t_record+dt;
//        a.t=t_record;
//        a.z=z_record;
//        a.x=x_record;
//        a.v=v_record;
//        out_path.insert(out_path.begin()+num,a);
//        num=num+1;
//    }
//    return out_path;

    //多项式拟合
    poly p;
    int deg_in=3;
    std::vector<double> x_rrt;
    std::vector<double> y_rrt;
    if (path.size()>2){
        for(int i=0;i<10;i++){
            x_rrt.push_back(i*0.5);
            y_rrt.push_back(0);
        }
//        for(int i=0;i<10;i++){
//            x_rrt.push_back(finish.x);
//            y_rrt.push_back(finish.y-i*0.5);
//        }
        for(int i=0;i<path.size();i++){
            cout<<path[i].x<<","<<path[i].y<<endl;
            x_rrt.push_back(path[i].x);
            y_rrt.push_back(path[i].y);
        }
        p.inter(deg_in,x_rrt,y_rrt);
        double z_record,x_record,v_record=veh_info.veh_preferred_speed,t_record=0;
        double dx,dt,dz;
        path_point a;
        int num=0;
        for(double z_temp=0; z_temp<finish.x;z_temp=z_temp+0.1){
            if (veh_info.veh_preferred_speed>v_record+0.5){
                v_record=max(0.0,v_record+0.1/5*3);
            }
            else if (veh_info.veh_preferred_speed<v_record-0.5){
                v_record=max(0.0,v_record-0.1/5*3);
            }
            else {
                v_record=v_record;
            }
            z_record=z_temp;
            x_record=p.mat[0][0]*z_temp*z_temp*z_temp+p.mat[1][0]*z_temp*z_temp+p.mat[2][0]*z_temp+p.mat[3][0];
            dx=(3*p.mat[0][0]*0.1*0.1+2*p.mat[1][0]*0.1+1*p.mat[2][0])*0.1;
            dz=0.1;
            dt=sqrt(dx*dx+dz*dz)/v_record;
            t_record=t_record+dt;
            a.t=t_record;
            a.z=z_record;
            a.x=x_record;
            a.v=v_record;
            out_path.insert(out_path.begin()+num,a);
            num=num+1;
        }
        return out_path;
    }
    else{
        //没有找到合适的路径
        double z_record=0,x_record,v_record,t_record=0;
        path_point a;
        int num=0;
        for(double t_temp=0; t_temp<2;t_temp=t_temp+0.1){
            z_record=z_record+v_record*0.1;
            x_record=0;
            v_record=max(0.0,veh_info.cur_speed-(t_temp*3));
            t_record=t_temp;
            a.t=t_record;
            a.z=z_record;
            a.x=x_record;
            a.v=v_record;
            out_path.insert(out_path.begin()+num,a);
            num=num+1;
        }
        return out_path;
    }
}

vector<path_point> intersection::generate_path_brake(void){
    //没有找到合适的路径
    double z_record=0,x_record,v_record,t_record=0;
    path_point a;
    int num=0;
    for(double t_temp=0; t_temp<2;t_temp=t_temp+0.1){
        z_record=z_record+v_record*0.1;
        x_record=0;
        v_record=max(0.0,veh_info.cur_speed-(t_temp*3));
        t_record=t_temp;
        a.t=t_record;
        a.z=z_record;
        a.x=x_record;
        a.v=v_record;
        out_path.insert(out_path.begin()+num,a);
        num=num+1;
    }
    return out_path;
}



straight::straight(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                   int driving_intention_in,vec2d GPS_cur, double path_angle){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
}

change_lane::change_lane(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                         int driving_intention_in,vec2d GPS_cur, double path_angle,int change_lane_direction_in){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
    change_lane_direction=change_lane_direction_in;
}


intersection::intersection(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                           int driving_intention_in,vec2d GPS_cur, double path_angle,
                           int intersection_type_in, vec2d gps_out, vec2d gps_in
                           ,int traffic_light_state_in, int traffic_light_time_remaining_in){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
    intersection_type=intersection_type_in;
    GPS_in_road_section=gps_in;//位置已转换成自车坐标（不是GPS坐标了）
    GPS_out_road_section=gps_out;//位置已转换成自车坐标（不是GPS坐标了）
    traffic_light_state=traffic_light_state_in;
    traffic_light_time_remaining=traffic_light_time_remaining_in;
}


vec2d circle_center(vec2d init_point,vec2d end_point,double kappa,int direction){
    double c1 = 0, c2 = 0, A = 0, B = 0, C = 0, z01 = 0, x01 = 0, x02 = 0, z02 = 0;
    c1 = (pow(end_point.x, 2) - pow(init_point.x, 2) + pow(end_point.z, 2)
          - pow(init_point.z, 2)) / 2 / (end_point.x - init_point.x);
    c2 = (end_point.z - init_point.z) / (end_point.x - init_point.x);
    A = 1.0 + pow(c2, 2);
    B = 2 * (init_point.x - c1) * c2 - 2 * init_point.z;
    C = pow((init_point.x - c1), 2) + pow(init_point.z, 2) - pow(1 / kappa, 2);
    z01 = (-B + sqrt(B*B - 4 * A * C)) / 2 / A;
    x01 = c1 - c2 * z01;
    z02 = (-B - sqrt(B*B - 4 * A * C)) / 2 / A;
    x02 = c1 - c2 * z02;
    cout << "circle center coordinates 1: (" << x01 << ", " << z01 << ")" << endl;
    cout << "circle center coordinates 2: (" << x02 << ", " << z02 << ")" << endl;
    double x0, z0;
    if (direction == 0) {//left
        if (x01 < x02) {
            x0 = x01;
            z0 = z01;
        }
        else {
            x0 = x02;
            z0 = z02;
        }
    }
    else {//right
        if (x01 > x02) {
            x0 = x01;
            z0 = z01;
        }
        else {
            x0 = x02;
            z0 = z02;
        }
    }
    vec2d center=vec2d(z0,x0);
    return center;
}
