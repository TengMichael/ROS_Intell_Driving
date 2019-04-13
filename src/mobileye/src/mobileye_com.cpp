#include <ros/ros.h>
#include <canbus/candata_multi.h>
#include <mobileye/vehicle_info.h>
#include <mobileye/mobileye_Lane.h>
#include <mobileye/mobileye_TSR.h>
#include <mobileye/mobileye_TSR_multi.h>
#include <mobileye/mobileye_Obstacle.h>
#include <mobileye/mobileye_Obstacle_multi.h>
#include <mobileye/mobileye_LKA_Lane.h>
#include <mobileye/mobileye_LKA_Lane_multi.h>
#include <math.h>

#define TSR_Num 7
#define Obstacle_Num 64

mobileye::vehicle_info Carinfo;
mobileye::mobileye_Lane Lane;
mobileye::mobileye_LKA_Lane_multi LKA;
mobileye::mobileye_TSR TSR[TSR_Num];
mobileye::mobileye_Obstacle Obstacle[Obstacle_Num];

uint8_t Obstacle_Total;
int16_t uint_int(uint16_t num,uint8_t len){
  int16_t temp;
  temp=num/(0x1<<(len-1))*(-1*(0x1<<(len-1)))+num%(0x1<<(len-1));
  return (temp);
}
/*Coordinate exchange for mobileye*/
void Coordinate_Exc_mobileye(float delta_x, float delta_y, float angle) {
    float px, py, vx, vy,ax,ay;
    for(uint8_t i=0;i<Obstacle_Total;i++){
        px = Obstacle[i].PosX+Carinfo.Speed/3.6;//plus distance of the reference points which is 1s headway
        py = Obstacle[i].PosY;
        vx = Obstacle[i].VrelX;
        ax = Obstacle[i].ArelX;

        Obstacle[i].PosX = px*cos(angle) - py*sin(angle) + delta_x;//Euler rotation+Offset
        Obstacle[i].PosY = px*sin(angle) + py*cos(angle) + delta_y;
        Obstacle[i].VrelX= vx*cos(angle) - vy*sin(angle);//Euler rotation
        Obstacle[i].ArelX= ax*cos(angle) - ay*sin(angle);//Euler rotation
    }
}
/*Analysis mobileyeQ2 CAN data to objects information*/
void mobileye_extract(const canbus::candata_multi::ConstPtr& CanData) {
  uint8_t Data[8];
  for (uint16_t i = 0; i < CanData->frame.size(); i++) {
    memcpy(Data,&(CanData->frame[i].data),sizeof(CanData->frame[i].data));
    switch(CanData->frame[i].id){
    case 0x760:
      Carinfo.Speed=Data[2]/3.6;
      Carinfo.YawAngle=Lane.YawAngle;
      Carinfo.PitchAngle=Lane.PitchAngle;
      break;
    case 0x737:
      if(((uint16_t)Data[1]*256+Data[0])!=0x8000)Lane.Curvature=(int16_t)((uint16_t)Data[1]*256+Data[0])*3.81*0.000001*(-1);//-0.12:0.12[1/m];invalid value:8000h
      //else Lane.Curvature=0;//only update when receiving effective data
      if(((uint16_t)Data[3]%16*256+Data[2])!=0x800)Lane.Heading=uint_int((uint16_t)Data[3]%16*256+Data[2],12)*0.0005*(-1);//-1:1;invalid value:800h
      //else Lane.Heading=0;
      Lane.Constr_Area=(Data[3]%32)/16;
      //Lane.Right_LDW_avai=(Data[3]%64)/32;
      //Lane.Left_LDW_avai=(Data[3]%128)/64;
      Lane.YawAngle=((float)Data[5]*256+Data[4]-(uint16_t)0x7fff)/1024.0;//radians
      Lane.PitchAngle=((float)Data[7]*256+Data[6]-(uint16_t)0x7fff)/1024.0/512.0;//-0.05:0.05 radians
      break;
    case 0x669:
      Lane.Left_Conf=Data[0]%4;//0 lowest;3 highest
      Lane.Left_Type=Data[0]/16;//0 dashed;1 solid;2 none;3 rode edge;4 double lane mark;5 bott's dots;6 invalid
      if(((uint16_t)Data[2]*16+Data[1]/16)!=0x800)Lane.Left_Dist=uint_int((uint16_t)Data[2]*16+Data[1]/16,12)*0.02;// -40:40[m];invalid value:800h
      //else Lane.Left_Dist=0;
      Lane.Right_Conf=Data[5]%4;
      Lane.Right_Type=Data[5]/16;
      Lane.Right_Dist=uint_int((uint16_t)Data[7]*16+Data[6]/16,12)*0.02;
      Lane.Right_LDW_avai=(Data[0]%8)/4;
      Lane.Left_LDW_avai=(Data[5]%8)/4;
      break;
    case 0x766:
      LKA.Left.MType=Data[0]%16;//0 dashed;1 solid;2 none;3 rode edge;4 double lane mark;5 bott's dots;6 invalid
      LKA.Left.Quality=(Data[0]%64)/16;//0,1 low;2,3 high
      LKA.Left.Model_degree=Data[0]/64;
      LKA.Left.Position=(int16_t)((uint16_t)Data[2]*256+Data[1])/256.0;//-127:128[m]
      LKA.Left.Curvature=((float)Data[4]*256+Data[3]-(uint16_t)0x7fff)/1024.0/1000.0;//-0.02:0.02
      LKA.Left.Curvature_deriv=((float)Data[6]*256+Data[5]-(uint16_t)0x7fff)/((uint32_t)0x01<<28);//-0.00012:0.00012
      LKA.Left.Width=Data[7]*0.01;//0-2.5[m]
      break;
    case 0x767:
      LKA.Left.Heading=((float)Data[1]*256+Data[0]-(uint16_t)0x7fff)/1024.0;//-0.357:0.357[radians];positive means steering towards the right
      LKA.Left.View_range=((float)(Data[3]%128)*256+Data[2])/256*(Data[3]/128.0);//0-127.996[m]
      break;
    case 0x768:
      LKA.Right.MType=Data[0]%16;//0 dashed;1 solid;2 none;3 rode edge;4 double lane mark;5 bott's dots;6 invalid
      LKA.Right.Quality=(Data[0]%64)/16;//0,1 low;2,3 high
      LKA.Right.Model_degree=Data[0]/64;
      LKA.Right.Position=(int16_t)((uint16_t)Data[2]*256+Data[1])/256.0;//-127:128[m]
      LKA.Right.Curvature=((float)Data[4]*256+Data[3]-(uint16_t)0x7fff)/1024.0/1000.0;//-0.02:0.02
      LKA.Right.Curvature_deriv=((float)Data[6]*256+Data[5]-(uint16_t)0x7fff)/((uint32_t)0x01<<28);//-0.00012:0.00012
      LKA.Right.Width=Data[7]*0.01;//0-2.5[m]
      break;
    case 0x769:
      LKA.Right.Heading=((float)Data[1]*256+Data[0]-(uint16_t)0x7fff)/1024.0;//-0.357:0.357[radians];positive means steering towards the right
      LKA.Right.View_range=((float)(Data[3]%128)*256+Data[2])/256*(Data[3]/128.0);//0-127.996[m]
      break;
    case 0x76C:
      LKA.Next_Left.MType=Data[0]%16;//0 dashed;1 solid;2 none;3 rode edge;4 double lane mark;5 bott's dots;6 invalid
      LKA.Next_Left.Quality=(Data[0]%64)/16;//0,1 low;2,3 high
      LKA.Next_Left.Model_degree=Data[0]/64;
      LKA.Next_Left.Position=(int16_t)((uint16_t)Data[2]*256+Data[1])/256.0;//-127:128[m]
      LKA.Next_Left.Curvature=((float)Data[4]*256+Data[3]-(uint16_t)0x7fff)/1024.0/1000.0;//-0.02:0.02
      LKA.Next_Left.Curvature_deriv=((float)Data[6]*256+Data[5]-(uint16_t)0x7fff)/((uint32_t)0x01<<28);//-0.00012:0.00012
      LKA.Next_Left.Width=Data[7]*0.01;//0-2.5[m]
      break;
    case 0x76D:
      LKA.Next_Left.Heading=((float)Data[1]*256+Data[0]-(uint16_t)0x7fff)/1024.0;//-0.357:0.357[radians];positive means steering towards the right
      LKA.Next_Left.View_range=((float)(Data[3]%128)*256+Data[2])/256*(Data[3]/128.0);//0-127.996[m]
      break;
    case 0x76E:
      LKA.Next_Right.MType=Data[0]%16;//0 dashed;1 solid;2 none;3 rode edge;4 double lane mark;5 bott's dots;6 invalid
      LKA.Next_Right.Quality=(Data[0]%64)/16;//0,1 low;2,3 high
      LKA.Next_Right.Model_degree=Data[0]/64;
      LKA.Next_Right.Position=(int16_t)((uint16_t)Data[2]*256+Data[1])/256.0;//-127:128[m]
      LKA.Next_Right.Curvature=((float)Data[4]*256+Data[3]-(uint16_t)0x7fff)/1024.0/1000.0;//-0.02:0.02
      LKA.Next_Right.Curvature_deriv=((float)Data[6]*256+Data[5]-(uint16_t)0x7fff)/((uint32_t)0x01<<28);//-0.00012:0.00012
      LKA.Next_Right.Width=Data[7]*0.01;//0-2.5[m]
      break;
    case 0x76F:
      LKA.Next_Right.Heading=((float)Data[1]*256+Data[0]-(uint16_t)0x7fff)/1024.0;//-0.357:0.357[radians];positive means steering towards the right
      LKA.Next_Right.View_range=((float)(Data[3]%128)*256+Data[2])/256*(Data[3]/128.0);//0-127.996[m]
      break;
    case 0x738:
      Obstacle_Total=Data[0];
      break;
    default:
      for(uint16_t j=0;j<TSR_Num;j++){
        if (CanData->frame[i].id==(uint16_t)(0x720+0x01*j)){
          TSR[j].MType=Data[0];
          TSR[j].SupType=Data[1];
          TSR[j].PosX=Data[2]*0.5;
          TSR[j].PosY=(int8_t)Data[3]*0.5;//wait test
          TSR[j].PosZ=(int8_t)Data[4]*0.5;//
          TSR[j].FilterType=Data[5];
        }
      }
      for(uint16_t j=0;j<Obstacle_Total;j++){
        if (CanData->frame[i].id==(uint16_t)(0x739+0x03*j)){
          Obstacle[j].ID=Data[0];
          //Obstacle[j].timestamp=CanData->frame[i].timestamp;
          if(((uint16_t)(Data[2]%16)*256+Data[1])!=0xFFF)Obstacle[j].PosX=((uint16_t)(Data[2]%16)*256+Data[1])*0.0625;//0:250[m];invalid value:FFFh
          //else Obstacle[j].PosX=0;
          if(((uint16_t)(Data[4]%4)*256+Data[3])!=0x200)Obstacle[j].PosY=uint_int((uint16_t)(Data[4]%4)*256+Data[3],10)*0.0625;//-31.93:31.93[m];invalid value:200h
          //else Obstacle[j].PosY=0;
          Obstacle[j].Blinker=Data[4]%32/4;//0 unavailabe;1 off;2 left;3 right;4 both
          Obstacle[j].CutState=Data[4]/32;//0 undefined;1 in host lane;2 out host lane;3 cut in;4 cut out
          if(((uint16_t)(Data[6]%16)*256+Data[5])!=0x800)Obstacle[j].VrelX=uint_int((uint16_t)(Data[6]%16)*256+Data[5],12)*0.0625;//-127.93:127.93[m/s];invalid value:800h
          //else Obstacle[j].VrelX=0;
          Obstacle[j].MType=Data[6]%128/16;//0 vehicle;1 truck;2 bike;3 ped;4 bicyle;5-7 unused
          Obstacle[j].Status=Data[7]%8;//0 undefined;1 standing;2 stopped;3 moving;4 oncoming;5 parked;6 unused
          Obstacle[j].Brake=Data[7]%16/8;//0 off;1 on
          Obstacle[j].Valid=Data[7]/64;//1 new valid;2 older valid
        }
        else if (CanData->frame[i].id==(uint16_t)(0x73A+0x03*j)){
          if(Data[0]!=0x3F)Obstacle[j].Length=(float)Data[0]*0.5;//0-31[m];invalid value:3Fh
          else Obstacle[j].Length=1;
          if(Data[1]!=0xFF)Obstacle[j].Width=(float)Data[1]*0.05;//0:12.5[m];invalid value:FFh
          else Obstacle[j].Width=1;
          Obstacle[j].Age=Data[2];
          Obstacle[j].ObsLane=Data[3]%4;//0 not assigned;1 ego lane;2 next lane;3 invalid
          Obstacle[j].CIPV=Data[3]%8/4;
        }
        else if (CanData->frame[i].id==(uint16_t)(0x73B+0x03*j)){
          Obstacle[j].AngleRate=(int16_t)((uint16_t)Data[1]*256+Data[0])*0.01;//-327.68:327.68[degree/sec]
          if(((uint16_t)Data[3]*256+Data[2])!=0x7FF)Obstacle[j].ScaleChange=(int16_t)((uint16_t)Data[3]*256+Data[2])*0.0002;//-6.5532:6.5532[pix/sec];invalid value:7FFh
          //else Obstacle[j].ScaleChange=0;
          if(((uint16_t)(Data[5]%4)*256+Data[4])!=0x200)Obstacle[j].ArelX=uint_int((uint16_t)(Data[5]%4)*256+Data[4],10)*0.03;//-14.97:14.97[m/s^2];invalid value:200h
          //else Obstacle[j].ArelX=0;
          Obstacle[j].Replaced=Data[5]%32/16;
          Obstacle[j].Angle=(int16_t)((uint16_t)Data[7]*256+Data[6])*0.01;//-327.68:327.68[degree]
        }
        else{}
      }
      break;
    }
  }
  Coordinate_Exc_mobileye(-0.4,-0.06,0);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mobileye_com");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe ("can_device2_can2_receive", 1000,mobileye_extract);

  ros::Publisher pub_car= nh.advertise<mobileye::vehicle_info>("vehicle_info", 1000);
  ros::Publisher pub_lane= nh.advertise<mobileye::mobileye_Lane>("mobileye_Lane", 1000);
  ros::Publisher pub_LKA= nh.advertise<mobileye::mobileye_LKA_Lane_multi>("mobileye_LKA", 1000);
  ros::Publisher pub_TSR= nh.advertise<mobileye::mobileye_TSR_multi>("mobileye_TSR_", 1000);
  ros::Publisher pub_obstacle= nh.advertise<mobileye::mobileye_Obstacle_multi>("mobileye_Obstacle", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    mobileye::mobileye_TSR_multi TSR_multiarray;
    mobileye::mobileye_Obstacle_multi Obstacle_multiarray;

    for(uint16_t i=0;i<TSR_Num;i++)
      TSR_multiarray.TSRs.push_back(TSR[i]);
    //ROS_INFO("Obstacle_Total %d",Obstacle_Total);
    for(uint16_t i=0;i<Obstacle_Total;i++)
      Obstacle_multiarray.Obstacles.push_back(Obstacle[i]);

    pub_car.publish(Carinfo);
    pub_lane.publish(Lane);
    pub_LKA.publish(LKA);
    pub_TSR.publish(TSR_multiarray);
    pub_obstacle.publish(Obstacle_multiarray);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
