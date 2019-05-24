#ifndef ENV_DATA_PREPROCESSING_H
#define ENV_DATA_PREPROCESSING_H
#include "environment.h"
#include "env_data_preprocessing.h"
using namespace std;

struct lane_input{
    double Curvature;
    double Heading;
    double Left_Dist;
    double Right_Dist;
    int Left_Type;
    int Right_Type;
    int Left_Conf;
    int Right_Conf;
    int Left_LDW_avai;
    int Right_LDW_avai;
    int Constr_Area;
    double YawAngle;
    double PitchAngle;
};

struct obs_input{
    int ID;
    double DistX;
    double DistY;
    double VrelX;
    double VrelY;
    double RCS;
    int DynProp;
    int Orientation_rms;
    int MeasState;
    int ProbOfExist;
    double ArelX;
    double ArelY;
    int Class;
    double OrientationAngel;
    double Length;
    double Width;
};

class road {//用于表示点或相对位置
public:
    int lane_num;//路段有几个车道
    int lane_cur_no;//当前所在的车道编号（从左往右数）
    //可能有两条车道都满足要求，例，如只有一条左转车道时，obj_lane_no2=obj_lane_no1;
    int obj_lane_no1;//根据路口转向需求等条件确定的目标车道1（不考虑前方障碍物）
    int obj_lane_no2;//根据路口转向需求等条件确定的目标车道2（不考虑前方障碍物）
    int obj_lane_no_cur;//当前时刻的目标车道（综合考虑障碍物和路口转向需求）
    bool cur_lane_passable;//当前车道是否可通行的

public:
    road();//默认构造函数
    road(int lane_num_input, int lane_cur_no_input, int obj_lane_no1_input, int obj_lane_no2_input, bool cur_lane_passable_input);//构造函数
    int cal_obj_lane_cur(bool left_lane_change_allowed, bool right_lane_change_allowed);
    int lane_change_completed();
};


void state_transfer_condition_cal(lane lane_data, vector<obstacle> obs_data, vehicle veh_data, navi navi_data,
                                  int lane_num_input, int lane_cur_no_input,
                                  int obj_lane_no1_input, int obj_lane_no2_input,
                                  bool left_lane_change_allowed, bool right_lane_change_allowed);


#endif // ENV_DATA_PREPROCESSING_H
