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
    this->_timerld=this->startTimer(1000);
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
    out_path.clear();
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
    state_transfer_condition_cal(lane_test, obs_info,veh_test.cur_speed, 1, 0, 1 ,1 , 1,1,true,false);
//void state_transfer_condition_cal(lane lane_data, vector<obstacle> obs_data, double v_cur, int E1_input, int E2_input,
//    int lane_num_input, int lane_cur_no_input, int obj_lane_no1_input, int obj_lane_no2_input,
//    bool left_lane_change_allowed, bool right_lane_change_allowed);

    //决策
    cout <<"decision begin... ";
    decision_simple_step();
    //decision_simple_step();
    //decision_simple_step();
    //decision_simple_step();//写这么多行时因为程序偶尔会莫名其妙崩溃。。
    cout <<"decision result: ";

    //规划
    //path path_test;
    //vector<path_point> out_path;
    if (upper_state==1){
        cout <<"upper_state=1;";
        int brake_dis=max(1.0,min(5.0,front_dis));//根据探测情况赋值
        straight b=straight(lane_test,veh_test,obs_info,0,vec2d(31.0,121.0),0.0);
        path_test=b.generate_path_braking(brake_dis);
        out_path=b.planned_path_cal();
        cout <<"upper_state=1"<<endl;
    }
    else if(upper_state==2){
        if(lane_driving_state==1){
            cout <<"upper_state=2,free_driving;";
            straight b=straight(lane_test,veh_test,obs_info,0,vec2d(31.0,121.0),0.0);
            path_test=b.generate_path_free_driving();
            out_path=b.planned_path_cal();
            cout <<"upper_state=2,free_driving"<<endl;
        }
        else if(lane_driving_state==2){
            cout <<"upper_state=2,following;";
            straight b=straight(lane_test,veh_test,obs_info,0,vec2d(31.0,121.0),0.0);
            path_test=b.generate_path_following();
            out_path=b.planned_path_cal();
            cout <<"upper_state=2,following"<<endl;
        }
        else if(lane_driving_state==3){
            cout <<"upper_state=2,change_lane;";
            change_lane c=change_lane(lane_test,veh_test,obs_info,0,vec2d(31.0,121.0),0.0,lane_driving_E1);
                    //lane_driving_E1就是换道方向，1表示左，2表示右
            path_test=c.generate_path();
            out_path=c.planned_path_cal();
            cout <<"upper_state=2,change_lane"<<endl;
        }
        else if(lane_driving_state==4){
            cout <<"upper_state=2,braking;";
            int brake_dis=max(1.0,min(5.0,front_dis));//根据探测情况赋值
            straight b=straight(lane_test,veh_test,obs_info,0,vec2d(31.0,121.0),0.0);
            path_test=b.generate_path_braking(brake_dis);
            out_path=b.planned_path_cal();
            cout <<"upper_state=2,braking"<<endl;
        }
    }


  cout<<"painting obs,";
  //painting
  QPainter painter(this);
  painter.setWindow(-1000,1000,4000,-2000);//set the window coordinate system, unit: 0.1m !!!

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
  painter.setPen(QPen(Qt::gray,2,Qt::DashLine));//设置画笔形式
  painter.setBrush(QBrush(Qt::red,Qt::NoBrush));//设置画刷形式
  int range_down=-100;
  int range_above=100;
  QPainterPath path1;
  QPointF sp,ep,c1,c2;
  for (double z_len = range_down; z_len<range_above; z_len=z_len+0.1) {
    sp=QPointF(10*(lane_test.left.C0+z_len*lane_test.left.C1+z_len*z_len*lane_test.left.C2
                   +z_len*z_len*z_len*lane_test.left.C3),10*z_len);
    ep=QPointF(10*(lane_test.left.C0+(z_len+1)*lane_test.left.C1+(z_len+1)*(z_len+1)*lane_test.left.C2
                   +(z_len+1)*(z_len+1)*(z_len+1)*lane_test.left.C3),10*(z_len+1));
    c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
    c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
    if(z_len==range_down){
      path1.moveTo(sp);
    }
    path1.cubicTo(c1,c2,ep);
  }
  painter.drawPath(path1);
  for (double z_len = range_down; z_len<range_above; z_len=z_len+0.1) {
    sp=QPointF(10*(lane_test.right.C0+z_len*lane_test.right.C1+z_len*z_len*lane_test.right.C2
                   +z_len*z_len*z_len*lane_test.right.C3),10*z_len);
    ep=QPointF(10*(lane_test.right.C0+(z_len+1)*lane_test.right.C1+(z_len+1)*(z_len+1)*lane_test.right.C2
                   +(z_len+1)*(z_len+1)*(z_len+1)*lane_test.right.C3),10*(z_len+1));
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
  painter.setPen(QPen(Qt::blue,2,Qt::SolidLine));
  QPainterPath path2;  
  for(int i=0;i<out_path.size()-1;i++){
        sp=QPointF(out_path[i].x*10,out_path[i].z*10);
        ep=QPointF(out_path[i+1].x*10,out_path[i+1].z*10);
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
  painter.setPen(QPen(Qt::black,5,Qt::SolidLine));//设置画笔形式
  QPainterPath axis;
  sp=QPointF(0+1000,0-500);
  ep=QPointF(out_path[out_path.size()-1].t*50+1500,0-500);
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
  for(int i=0;i<out_path.size()-1;i++){
        sp=QPointF(out_path[i].t*50+1000,out_path[i].v*50-500);
        ep=QPointF(out_path[i+1].t*50+1000,out_path[i+1].v*50-500);
        c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
        c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
        if (i==0){
            path3.moveTo(sp);
        }
        path3.cubicTo(c1,c2,ep);
        traj_temp[i].timestamp=timestamp;
        traj_temp[i].ID=i;
        traj_temp[i].t=out_path[i].t;
        traj_temp[i].v=out_path[i].v;
        traj_temp[i].x=out_path[i].z;
        traj_temp[i].y=out_path[i].x;
  }
  painter.drawPath(path3);

  cout<<"painting text ";
  //注释
  painter.setPen(QPen(Qt::black,3,Qt::SolidLine));//设置画笔形式
  painter.setWindow(0,0,4000,2000);//把绘图坐标系转过来方便写注释文字
  QFont font("Times New Roman",40,QFont::Bold,true);
  painter.setFont(font);
  painter.drawText(100,100,"Driving Path");
  painter.drawText(2100,100,"Speed Trajectory");
  painter.drawText(2500,1750,"t");
  //painter.rotate(90);
  painter.drawText(1700,1000,"v");

  QFont font1("Times New Roman",40,QFont::Medium,true);
  painter.setFont(font1);
  painter.drawText(1800,500,"20 m/s");
  painter.drawText(1800,750,"15 m/s");
  painter.drawText(1800,1000,"10 m/s");
  painter.drawText(1800,1250,"5 m/s");
  painter.drawText(1800,1500,"0 m/s");
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
  cout<<"painting end"<<endl;
}

void MainWindow::timerEvent(QTimerEvent* e){
  cout<<"repaint ";
  ros::spinOnce();
  this->repaint();
}
