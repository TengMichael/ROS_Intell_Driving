#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "ros/ros.h"

//extern ros::Publisher pub_planning;
//extern ros::NodeHandle nh;

int randnum(int num){//generate random number
  qsrand(num+QTime(0,0,0).secsTo(QTime::currentTime()));
  return qrand();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(QSize(2000,1000));//set window size
    this->_timerld=this->startTimer(300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
  //environment initialization
    // //临时测试 数据赋值
    //lane_line left = lane_line(0, 0, -0.005, 0, 1, true);
    //lane_line right = lane_line(5, 0, -0.005, 0, 1, true);
    //lane lane_test = lane(left, right, 10);
    //lane_test = lane(left, right, 10);
    //vehicle veh_test = vehicle(4, 2, 3, 5, 1, 1, PI / 4);
    //veh_test = vehicle(4, 2, 3, 5, 1, 1, PI / 4);
    //vector<obstacle> obs_info;

  //vector数据清空
    //obs_info.clear();
    out_path1.clear();
//    int obs_num=1;
//    for (int i = 0; i < obs_num; i++) {
//        int type = randnum(5+i*5) % 2 + 1;//1 或 2
//        int width = 2;
//        int height = 2;
//        obstacle obs_temp = obstacle(7.0, 2.0, 0.0, 0.0, width, height, type);
//        obs_info.insert(obs_info.begin() + i, obs_temp);
//    }
//    int obs_num=10;
//    for (int i = 0; i < obs_num; i++) {
//      int z_temp = randnum(1+i*5) % 200 - 100;//±100m范围
//      int x_temp = randnum(2+i*5) % 20 - 10;//±10m范围
//      int vz_temp = randnum(3+i*5) % 10;//0-9m/s范围
//      int vx_temp = randnum(4+i*5) % 2;//0-1m/s范围
//      int type = randnum(5+i*5) % 2 + 1;//1 或 2
//      int width = 2;
//      int height = 2;
//      obstacle obs_temp = obstacle((double)z_temp, (double)x_temp,
//                                   (double)vz_temp, (double)vx_temp, width, height, type);
//      obs_info.insert(obs_info.begin() + i, obs_temp);
//    }
    //数据接口


    cout <<"cal transfer condition... ";
    //环境数据分析+决策切换条件赋值
    state_transfer_condition_cal(lane_test, obs_info,veh_test,navi_test, 1, 1, 1, 1, true, false);
    //void state_transfer_condition_cal(lane lane_data, vector<obstacle> obs_data, vehicle veh_data, navi navi_data,
    //                                  int lane_num_input, int lane_cur_no_input,
    //                                  int obj_lane_no1_input, int obj_lane_no2_input,
    //                                  bool left_lane_change_allowed, bool right_lane_change_allowed){

    //决策
    cout <<"decision begin... ";
    decision_simple_step();
    //decision_simple_step();
    //decision_simple_step();
    //decision_simple_step();//写这么多行是因为程序偶尔会莫名其妙崩溃。。现在不会啦
    cout <<"decision result: ";


    //规划
    //path path_test;
    //vector<path_point> out_path;
    if (upper_state==1){
        cout <<"upper_state=1;";
        int temp=max(5.0,veh_test.cur_speed*abs(veh_test.cur_speed)/veh_test.max_dec);
        int brake_dis=max(1.0,min(double(temp),front_dis));//根据探测情况赋值
        straight b=straight(lane_test,veh_test,obs_info,0,vec2d(veh_test.lat,veh_test.lon),veh_test.yaw_angle);
        path_test=b.generate_path_braking(brake_dis);
        b.planned_path_cal();
        out_path1=b.out_path;
        cout <<"upper_state=1"<<endl;
    }
    else if(upper_state==2){
        if(lane_driving_state==1){
            cout <<"upper_state=2,free_driving;";
            straight b=straight(lane_test,veh_test,obs_info,0,vec2d(veh_test.lat,veh_test.lon),veh_test.yaw_angle);
            path_test=b.generate_path_free_driving();
            b.planned_path_cal();
            out_path1=b.out_path;
            cout <<"upper_state=2,free_driving"<<endl;
        }
        else if(lane_driving_state==2){
            cout <<"upper_state=2,following;";
            straight b=straight(lane_test,veh_test,obs_info,0,vec2d(veh_test.lat,veh_test.lon),veh_test.yaw_angle);
            path_test=b.generate_path_following();
            b.planned_path_cal();
            out_path1=b.out_path;
            cout <<"upper_state=2,following"<<endl;
        }
        else if(lane_driving_state==3){
            cout <<"upper_state=2,change_lane;";
            change_lane c=change_lane(lane_test,veh_test,obs_info,0,vec2d(veh_test.lat,veh_test.lon),veh_test.yaw_angle,lane_driving_E1);
            //lane_driving_E1就是换道方向，1表示左，2表示右
            path_test=c.generate_path();
            c.planned_path_cal();
            out_path1=c.out_path;
            cout <<"upper_state=2,change_lane"<<endl;
        }
        else if(lane_driving_state==4){
            cout <<"upper_state=2,braking;";
            int temp=max(5.0,veh_test.cur_speed*abs(veh_test.cur_speed)/veh_test.max_dec);
            int brake_dis=max(1.0,min(double(temp),front_dis));//根据探测情况赋值
            straight b=straight(lane_test,veh_test,obs_info,0,vec2d(veh_test.lat,veh_test.lon),veh_test.yaw_angle);
            path_test=b.generate_path_braking(brake_dis);
            b.planned_path_cal();
            out_path1=b.out_path;
            cout <<"upper_state=2,braking"<<endl;
        }
    }
    else if(upper_state==3){
        if(intersection_state==1){
            cout <<"upper_state=3,pass the intersection;";
            //目前是给定的路段入口，先测试一下!!!!!
            intersection b=intersection(lane_test,veh_test,obs_info,1,vec2d(veh_test.lat,veh_test.lon),veh_test.yaw_angle,navi_test.turn_for_intersection,vec2d(5,0),vec2d(20,20),1,60);
            out_path1=b.generate_path_rrt();
            cout <<"upper_state=3,pass the intersection"<<endl;
        }
        else if(intersection_state==2){
            cout <<"upper_state=3,intersection stop;";
            //目前是给定的路段入口，先测试一下!!!!!
            intersection b=intersection(lane_test,veh_test,obs_info,1,vec2d(veh_test.lat,veh_test.lon),veh_test.yaw_angle,navi_test.turn_for_intersection,vec2d(5,0),vec2d(20,20),1,60);
            out_path1=b.generate_path_brake();
            cout <<"upper_state=3,intersection stop"<<endl;
        }
    }
    for(int i=0;i<out_path1.size();i++){//写入需要发送的消息
      traj_temp[i].timestamp=timestamp;
      traj_temp[i].ID=i;
      traj_temp[i].t=out_path1[i].t;
      traj_temp[i].v=out_path1[i].v;
      traj_temp[i].x=out_path1[i].z;
      traj_temp[i].y=out_path1[i].x;
    }


    cout<<"painting obs,";
    //painting
    QPainter painter(this);
    painter.setWindow(-1000,1000,4000,-2000);//set the window coordinate system, unit: 0.1m !!!
    //设定横向坐标的放大系数（车道宽一点比较容易看清）
    int size=2;

    //draw current vehicle
    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine));
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));//设置画刷形式
    painter.drawEllipse(QPoint(0,0),20,20);
    painter.drawPoint(0,0);

    //draw obstacle
    for (int i = 0; i < obs_info.size(); i++) {
      painter.setPen(QPen(Qt::red,2,Qt::SolidLine));
      painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
      painter.drawEllipse(QPoint(obs_info[i].pos_x*10,obs_info[i].pos_z*10),obs_info[i].width*10,obs_info[i].width*10);
    }
    cout<<"painting lane,";
    //draw lane
    painter.setPen(QPen(Qt::gray,8,Qt::DashLine));//设置画笔形式
    painter.setBrush(QBrush(Qt::red,Qt::NoBrush));//设置画刷形式
    int range_down=-50;
    int range_above=50;
    QPainterPath path1;
    QPointF sp,ep,c1,c2;
    for (double z_len = range_down; z_len<range_above; z_len=z_len+0.1) {
      sp=QPointF(size*10*(lane_test.left.C0+z_len*lane_test.left.C1+z_len*z_len*lane_test.left.C2
                     +z_len*z_len*z_len*lane_test.left.C3),size*10*z_len);
      ep=QPointF(size*10*(lane_test.left.C0+(z_len+1)*lane_test.left.C1+(z_len+1)*(z_len+1)*lane_test.left.C2
                     +(z_len+1)*(z_len+1)*(z_len+1)*lane_test.left.C3),size*10*(z_len+1));
      c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
      c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
      if(z_len==range_down){
        path1.moveTo(sp);
      }
      path1.cubicTo(c1,c2,ep);
    }
    painter.drawPath(path1);
    for (double z_len = range_down; z_len<range_above; z_len=z_len+0.1) {
      sp=QPointF(size*10*(lane_test.right.C0+z_len*lane_test.right.C1+z_len*z_len*lane_test.right.C2
                     +z_len*z_len*z_len*lane_test.right.C3),size*10*z_len);
      ep=QPointF(size*10*(lane_test.right.C0+(z_len+1)*lane_test.right.C1+(z_len+1)*(z_len+1)*lane_test.right.C2
                     +(z_len+1)*(z_len+1)*(z_len+1)*lane_test.right.C3),size*10*(z_len+1));
      c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
      c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
      if(z_len==range_down){
        path1.moveTo(sp);
      }
      path1.cubicTo(c1,c2,ep);
    }
    painter.drawPath(path1);
    cout<<"painting path,";
    //draw path
    painter.setPen(QPen(Qt::blue,8,Qt::SolidLine));
    QPainterPath path2;
    for(int i=0;i<out_path1.size()-1;i++){
          sp=QPointF(size*10*out_path1[i].x,size*out_path1[i].z*10);
          ep=QPointF(size*10*out_path1[i+1].x,size*out_path1[i+1].z*10);
          c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
          c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
          if (i==0){
              path2.moveTo(sp);
          }
          path2.cubicTo(c1,c2,ep);
    }
    painter.drawPath(path2);

    cout<<"painting speed,";
    //draw speed trajectory
    painter.setPen(QPen(Qt::black,6,Qt::SolidLine));//设置画笔形式
    QPainterPath axis;
    sp=QPointF(0+1000,0-500);
    ep=QPointF(out_path1[out_path1.size()-1].t*50+1500,0-500);
    axis.moveTo(sp);
    axis.lineTo(ep);
    painter.drawPath(axis);
    sp=QPointF(0+1000,0-500);
    ep=QPointF(0+1000,1000-500);
    axis.moveTo(sp);
    axis.lineTo(ep);
    painter.drawPath(axis);

    painter.setPen(QPen(Qt::red,5,Qt::SolidLine));//设置画笔形式
    QPainterPath path3;
    for(int i=0;i<out_path1.size()-1;i++){
          sp=QPointF(out_path1[i].t*50+1000,out_path1[i].v*100-500);
          ep=QPointF(out_path1[i+1].t*50+1000,out_path1[i+1].v*100-500);
          c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
          c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
          if (i==0){
              path3.moveTo(sp);
          }
          path3.cubicTo(c1,c2,ep);
    }
    painter.drawPath(path3);

    cout<<"painting text ";
    //注释
    painter.setPen(QPen(Qt::black,3,Qt::SolidLine));//设置画笔形式
    painter.setWindow(0,0,4000,2000);//把绘图坐标系转过来方便写注释文字
    QFont font("Times New Roman",40,QFont::Bold,true);
    painter.setFont(font);
    painter.drawText(100,100,"Driving Path");
    if (E1==0){
      painter.drawText(100,200,"Navigation Start: No");
    }
    else {
      painter.drawText(100,200,"Navigation Start: Yes");
    }
    if (E2==0){
      painter.drawText(100,300,"Navigation Stop: No");
    }
    else {
      painter.drawText(100,300,"Navigation Stop: Yes");
    }
    if (navi_test.distance_from_road_seg_end>10){
      painter.drawText(100,400,"Near intersection: No");
    }
    else {
      painter.drawText(100,400,"Near intersection: Yes");
    }    
    painter.drawText(100,500,"Distance from intersection (m):");
    char r[256];
    sprintf(r,"%.0f",double(navi_test.distance_from_road_seg_end));//);    //0 为小数位数
    painter.drawText(800,500,r);
    if (E3==0){
      painter.drawText(100,600,"Enter new road: No");
    }
    else {
      painter.drawText(100,600,"Enter new road: Yes");
    }
    if(C1==1 && navi_test.turn_for_intersection==0){
      painter.drawText(100,700,"Intersection driving: straight");
    }
    else if(C1==1 && navi_test.turn_for_intersection==1){
      painter.drawText(100,700,"Intersection driving: left turn");
    }
    else if(C1==1 && navi_test.turn_for_intersection==2){
      painter.drawText(100,700,"Intersection driving: right turn");
    }

    painter.drawText(1100,100,"50m");
    painter.drawText(1100,1000,"0m");
    painter.drawText(1100,1900,"-50m");
    painter.drawText(2100,100,"Speed Trajectory");
    painter.drawText(2500,1750,"t");
    //painter.rotate(90);
    painter.drawText(1700,1000,"v");

    QFont font1("Times New Roman",40,QFont::Medium,true);
    painter.setFont(font1);
    painter.drawText(1800,500,"36 km/h");
    painter.drawText(1800,750,"27 km/h");
    painter.drawText(1800,1000,"18 km/h");
    painter.drawText(1800,1250,"9 km/h");
    painter.drawText(1800,1500,"0 km/h");
    painter.drawText(3250,1600,"25 s");
    painter.drawText(3000,1600,"20 s");
    painter.drawText(2750,1600,"15 s");
    painter.drawText(2500,1600,"10 s");
    painter.drawText(2250,1600,"5 s");
    painter.drawText(2000,1600,"0 s");
    //决策结果显示
    painter.setPen(QPen(Qt::red,3,Qt::SolidLine));//设置画笔形式
    painter.setFont(font);
    if (upper_state==1){
        painter.drawText(2500,300,"stop");
    }
    else if(upper_state==2){
        if(lane_driving_state==1){
            painter.drawText(2500,300,"free driving");
        }
        else if(lane_driving_state==2){
            painter.drawText(2500,300,"car following");
        }
        else if(lane_driving_state==3){
            painter.drawText(2500,300,"lane change");
        }
        else if(lane_driving_state==4){
            painter.drawText(2500,300,"braking");
        }
    }
    else if(upper_state==3){
      if(intersection_state==1){
          painter.drawText(2500,300,"intersection");
      }
      else if(intersection_state==2){
          painter.drawText(2500,300,"intersection");
      }
    }
    cout<<"painting end"<<endl;
}

void MainWindow::timerEvent(QTimerEvent* e){
  cout<<"repaint ";
  ros::spinOnce();
  this->repaint();
}
