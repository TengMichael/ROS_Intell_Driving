#include "global.h"
using namespace std;

road::road(){
    lane_num=1;
    obj_lane_no1=1;
    obj_lane_no2=1;
    lane_cur_no=1;
    cur_lane_passable=1;
}

road::road(int lane_num_input, int lane_cur_no_input, int obj_lane_no1_input, int obj_lane_no2_input, bool cur_lane_passable_input){
    lane_num=lane_num_input;
    obj_lane_no1=obj_lane_no1_input;
    obj_lane_no2=obj_lane_no2_input;
    lane_cur_no=lane_cur_no_input;
    cur_lane_passable=cur_lane_passable_input;
}

int road::cal_obj_lane_cur(bool left_lane_change_allowed, bool right_lane_change_allowed){
    int lane_change_dmnd=0;
    //dmnd为0时不换道，dmnd为1时向左换道，dmnd为2时向右换道
    //left_lane_change_allowed仅表示左侧车道在交通规则中能否变道，不考虑左侧车道是否存在障碍物影响变道
    //right_lane_change_allowed仅表示右侧车道在交通规则中能否变道，不考虑右侧车道是否存在障碍物影响变道
    //根据情况判断目标车道
    if(cur_lane_passable & (lane_cur_no==obj_lane_no1 | lane_cur_no==obj_lane_no2)){//当前车道可以通行，且当前车道就是目标车道
        obj_lane_no_cur=lane_cur_no;
        lane_change_dmnd=0;
    }
    else if(!cur_lane_passable){
        if (left_lane_change_allowed){
            lane_change_dmnd=1;
            obj_lane_no_cur=lane_cur_no-1;//obj_lane_no_cur如果是0就表示越过黄线变道
        }
        else if(right_lane_change_allowed){
            lane_change_dmnd=2;
            obj_lane_no_cur=lane_cur_no+1;
        }
        else{
            lane_change_dmnd=0;
            obj_lane_no_cur=lane_cur_no;
        }
    }
    else{
        if(lane_cur_no<obj_lane_no1&lane_cur_no<obj_lane_no2){
            lane_change_dmnd=2;
            obj_lane_no_cur=lane_cur_no+1;
        }
        else if(lane_cur_no>obj_lane_no1&lane_cur_no>obj_lane_no2){
            lane_change_dmnd=1;
            obj_lane_no_cur=lane_cur_no-1;
        }
        else{
            lane_change_dmnd=0;
            obj_lane_no_cur=lane_cur_no;
        }
    }
    return lane_change_dmnd;
}

int road::lane_change_completed(){
    if(lane_cur_no==obj_lane_no_cur){
        return 1;
    }
    else{
        return 0;
    }
}

lane lane_data_input(lane_input lane_data){

    lane_line left_in=lane_line(-lane_data.Left_Dist, lane_data.Heading,
                                lane_data.Curvature, 0, lane_data.Left_Type, true);
    lane_line right_in=lane_line(lane_data.Right_Dist, lane_data.Heading,
                                lane_data.Curvature, 0, lane_data.Right_Type, true);
    double road_speed_limit_in=30;
    lane temp=lane(left_in,  right_in, road_speed_limit_in);
    return temp;
}


obstacle obs_data_input(obs_input obs_data){
    obstacle temp=obstacle(obs_data.DistX, obs_data.DistY, obs_data.VrelX, obs_data.VrelY, obs_data.Length, obs_data.Width, 1);
    return temp;
}

void state_transfer_condition_cal(lane lane_data, vector<obstacle> obs_data, vehicle veh_data, navi navi_data,
                                  int lane_num_input, int lane_cur_no_input,
                                  int obj_lane_no1_input, int obj_lane_no2_input,
                                  bool left_lane_change_allowed, bool right_lane_change_allowed){
    //给以下参数赋值
    E1=0;//启动指令
    E2=0;//停车指令
    lane_driving_C1=0;
    lane_driving_C2=0;
    lane_driving_C3=0;
    lane_driving_C4=0;
    lane_driving_E1=0;
    lane_driving_E2=0;
    lane_driving_F=0;
    //根据导航计算是否需要启动或到达终点
    if(navi_data.distance_from_road_seg_end<5 & navi_data.turn==0)
    {//表示到达规划终点
      E1=0;
      E2=1;//出现了一靠近路口turn就变成0的情况，于是到达终点停车指令会与到达路口状态同时置1，这样一到路口就会停车
    }
    else{//其他情况
      E1=1;
      E2=0;
    }
    //计算间隔距离和前车车速
    int lane_no;
    double front_dis_left=1000;//左前车距
    double front_dis_right=1000;//右前车距
    double back_dis_left=1000;//左后车距
    double back_dis_right=1000;//右后车距
    front_dis=1000;//global variable!
    double v_leading=100;
    double v_leading_low=2;//前方障碍物速度阈值，低于此阈值需要换道
    double front_dis_brake=5;
    double front_dis_follow=20;
    for(int i=0;i<obs_data.size();i++){
        lane_no=lane_data.obs_in_lane(obs_data[i]);
        if(lane_no==0 | lane_no==1 | lane_no==-1 | lane_no==3){
            //占中间车道
            if(obs_data[i].pos_z>0 & front_dis>=obs_data[i].pos_z){
                front_dis=obs_data[i].pos_z;
                v_leading=obs_data[i].v_z;
            }
        }
        if(lane_no==-2 | lane_no==-1 | lane_no==3){
            //占左边车道
            if(obs_data[i].pos_z>0 & front_dis_left>=obs_data[i].pos_z){
                front_dis_left=obs_data[i].pos_z;
            }
            else if(obs_data[i].pos_z<0 & back_dis_left>=abs(obs_data[i].pos_z)){
                back_dis_left=abs(obs_data[i].pos_z);
            }
        }
        if(lane_no==2 | lane_no==1 | lane_no==3){
            //占右边车道
            if(obs_data[i].pos_z>0 & front_dis_right>=obs_data[i].pos_z){
                front_dis_right=obs_data[i].pos_z;
            }
            else if(obs_data[i].pos_z<0 & back_dis_right>=abs(obs_data[i].pos_z)){
                back_dis_right=abs(obs_data[i].pos_z);
            }
        }
    }
    if(v_leading<v_leading_low){
        lane_driving_C1=1;
    }
    if(front_dis<front_dis_follow){
        lane_driving_C2=1;
    }
    if(front_dis<front_dis_brake){
        lane_driving_C3=1;
    }
    if(abs(veh_data.cur_speed)<0.5){
        lane_driving_C4=1;
    }
    road road_temp=road(lane_num_input, lane_cur_no_input, obj_lane_no1_input, obj_lane_no2_input, (1-lane_driving_C1));
    lane_driving_E1=road_temp.cal_obj_lane_cur(left_lane_change_allowed, right_lane_change_allowed);
    lane_driving_E2=road_temp.lane_change_completed();
    if((front_dis_left>20  & back_dis_left>20) | (front_dis_right>20& back_dis_right>20)){
        lane_driving_F=1;//左边能够换道或者右边能够换道
    }
    //十字路口相关的变量
    intersection_C1=0;//表示路口障碍物情况，障碍物较多时置1，不知道怎么判断，先默认为0好了，RRT规划不出来的时候也会自动停车
    if (navi_data.distance_from_road_seg_end<30){
      C1=1;//临近当前道路终点，通过接收的数据信息来判断
    }
    else{
      C1=0;
    }
    //C1=0;
    if (navi_data.newroad==1 || navi_data.distance_from_road_seg_end>30){//这个信号没有延时，导致读取信息频率不够高时，读不到该信号置1的瞬间，有限状态机退不出路口状态
      E3=1;//已经进入了新的路段
    }
    else{
      E3=0;
    }
}
