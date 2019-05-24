#include <ros/ros.h>
#include <kalman_filter.h>
#include <kalman/radar_mobileye_data.h>
#include <kalman/radar_mobileye_data_multi.h>

#define Obstacle_Num 64
uint8_t fusion_ID_Total=0;

using Eigen::MatrixXd;
using Eigen::VectorXd;

KalmanFilter kf;
kalman::radar_mobileye_data fusion_data[Obstacle_Num];

KalmanFilter::KalmanFilter() {}
KalmanFilter::~KalmanFilter() {}

// Struct with kalman data and timestamp for next time
struct kalman_data{
  Eigen::VectorXd x_;
  Eigen::MatrixXd P_;
  uint previous_timestamp_;
};
// Vector for kalman_data structure
std::vector <kalman_data> kalman_vector;

void KalmanFilter::Predict() {
  /**TODO:predict the state */
  x_ = F_ * x_;
  MatrixXd Ft = F_.transpose();
  P_ = F_ * P_ * Ft + Q_;
}
void KalmanFilter::Update_radar() {
  /***TODO:update the state by using Kalman Filter equations*/
  VectorXd z_pred = H_radar * x_;
  VectorXd y = z_radar - z_pred;
  MatrixXd Ht = H_radar.transpose();
  MatrixXd S = H_radar * P_ * Ht + R_radar;
  MatrixXd Si = S.inverse();
  MatrixXd PHt = P_ * Ht;
  MatrixXd K = PHt * Si;
  //new estimate
  x_radar = x_ + (K * y);
  long x_size = x_radar.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_radar = (I - K * H_radar) * P_;
}
void KalmanFilter::Update_mobileye() {
  /***TODO:update the state by using Kalman Filter equations*/
  VectorXd z_pred = H_mobileye * x_;
  VectorXd y = z_mobileye - z_pred;
  MatrixXd Ht = H_mobileye.transpose();
  MatrixXd S = H_mobileye * P_ * Ht + R_mobileye;
  MatrixXd Si = S.inverse();
  MatrixXd PHt = P_ * Ht;
  MatrixXd K = PHt * Si;
  //new estimate
  x_mobileye = x_ + (K * y);
  long x_size = x_mobileye.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_mobileye = (I - K * H_mobileye) * P_;
}

void kf_calc(kalman::radar_mobileye_data *measure_value){
  //ROS_INFO_STREAM("Start ProcessMeasurement.. ");
  /*Initialization*/
  kf.id_ = measure_value->ID;
  // Push kalman vector
  if (kalman_vector.size() == 0)
  {
    for (int8_t n = 0; n<100; n++)
    {
      kalman_vector.push_back(kalman_data());
    }
  }
  // First time computation
  if(kalman_vector[kf.id_].previous_timestamp_ == 0) {
    // Increase the size of the kalman_vector
    //ROS_INFO_STREAM("First computation. kf id: " << kf.id_ );
    // first measurement
    kf.x_ = VectorXd(4);
    kf.x_ << 1, 1, 1, 1;
    /*Initialize state*/
    kf.x_(0) = measure_value->radar_DistX;
    kf.x_(1) = measure_value->radar_DistY;
    kf.x_(2) = measure_value->radar_VrelX;
    kf.x_(3) = measure_value->radar_VrelY;
    kf.previous_timestamp_ = measure_value->timestamp;
    //state covariance matrix P
    kf.P_ = MatrixXd(4, 4);
    kf.P_ << 1000, 0, 0, 0,
        0, 1000, 0, 0,
        0, 0, 1000, 0,
        0, 0, 0, 1000;
  }
  else
  {
    kf.x_ = kalman_vector[kf.id_].x_;
    kf.P_ = kalman_vector[kf.id_].P_;
    kf.previous_timestamp_ = kalman_vector[kf.id_].previous_timestamp_;
    //ROS_INFO_STREAM("New data update after init.");
  }
  /*  Prediction*/
  kf.F_ = MatrixXd(4, 4);
  kf.F_ << 1, 0, 1, 0,
      0, 1, 0, 1,
      0, 0, 1, 0,
      0, 0, 0, 1;
  //compute the time elapsed between the current and previous measurements
  float dt = (measure_value->timestamp - kf.previous_timestamp_)/1000.0;	//dt - expressed in seconds
  kf.previous_timestamp_ = measure_value->timestamp;
  float dt_2 = dt   * dt;
  float dt_3 = dt_2 * dt;
  float dt_4 = dt_3 * dt;
  //Modify the F matrix so that the time is integrated
  kf.F_(0, 2) = dt;
  kf.F_(1, 3) = dt;
  //set the acceleration noise components
  float noise_ax = 2;
  float noise_ay = 2;
  //set the process covariance matrix Q
  kf.Q_ = MatrixXd(4, 4);
  kf.Q_ << dt_4 / 4 * noise_ax, 0, dt_3 / 2 * noise_ax, 0,
      0, dt_4 / 4 * noise_ay, 0, dt_3 / 2 * noise_ay,
      dt_3 / 2 * noise_ax, 0, dt_2*noise_ax, 0,
      0, dt_3 / 2 * noise_ay, 0, dt_2*noise_ay;
  //ROS_INFO_STREAM("Update KF Predict..");
  kf.Predict();
  /*Update*/
  kf.H_radar = MatrixXd(4, 4);
  kf.H_radar << 1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1;
  kf.H_mobileye = MatrixXd(3, 4);
  kf.H_mobileye << 1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0;
  kf.R_radar = MatrixXd(4, 4);
  kf.R_radar<< 0.09, 0, 0, 0,
      0, 0.09, 0, 0,
      0, 0, 0.0009, 0,
      0, 0, 0, 0.0009;
  kf.R_mobileye= MatrixXd(3, 3);
  kf.R_mobileye<< 0.09, 0, 0,
      0, 0.09, 0,
      0, 0, 0.0009;
  //ROS_INFO_STREAM("Calling update KF");
  kf.z_radar=VectorXd(4);
  kf.z_radar(0) = measure_value->radar_DistX;
  kf.z_radar(1) = measure_value->radar_DistY;
  kf.z_radar(2) = measure_value->radar_VrelX;
  kf.z_radar(3) = measure_value->radar_VrelY;
  kf.Update_radar();
  kf.z_mobileye=VectorXd(3);
  kf.z_mobileye(0) = measure_value->mobileye_DistX;
  kf.z_mobileye(1) = measure_value->mobileye_DistY;
  kf.z_mobileye(2) = measure_value->mobileye_VrelX;
  kf.Update_mobileye();
  // Fusion the estimation
  MatrixXd S =kf.P_radar.inverse()+kf.P_mobileye.inverse();
  kf.P_=S.inverse();
  kf.x_=kf.P_*(kf.P_radar.inverse()*kf.x_radar+kf.P_mobileye.inverse()*kf.x_mobileye);
  //ROS_INFO("radar_DistX %f",kf.x_radar(0));
  //ROS_INFO("radar_DistY %f",kf.x_radar(1));
  //ROS_INFO("mobileye_DistX %f",kf.x_mobileye(0));
  //ROS_INFO("mobileye_DistY %f",kf.x_mobileye(1));
  //ROS_INFO("fusion_DistX %f",kf.x_(0));
  //ROS_INFO("fusion_DistY %f",kf.x_(1));
  // Store all the values for next measurement
  kalman_vector[kf.id_].x_ = kf.x_;
  kalman_vector[kf.id_].P_ = kf.P_;
  kalman_vector[kf.id_].previous_timestamp_ = kf.previous_timestamp_;
  measure_value->fusion_DistX=kf.x_(0);
  measure_value->fusion_DistY=kf.x_(1);
  measure_value->fusion_VrelX=kf.x_(2);
  measure_value->fusion_VrelY=kf.x_(3);
}

void kf_calc_multi(kalman::radar_mobileye_data_multi msg){
  fusion_ID_Total=msg.objs.size();
  for(uint8_t i=0;i<fusion_ID_Total;i++){
    if (msg.objs[i].fusion_flag)
      kf_calc(&(msg.objs[i]));
    else
    {
      msg.objs[i].fusion_DistX= msg.objs[i].radar_DistX;
      msg.objs[i].fusion_DistY= msg.objs[i].radar_DistY;
      msg.objs[i].fusion_VrelX= msg.objs[i].radar_VrelX;
      msg.objs[i].fusion_VrelY= msg.objs[i].radar_VrelY;
    }
    memcpy(&(fusion_data[i]),&(msg.objs[i]),sizeof(msg.objs[i]));
  }
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "kalman_filter");
  ros::NodeHandle nh;

  memset(&kalman_vector,0,sizeof(&kalman_vector));

  ros::Subscriber sub = nh.subscribe ("radar_mobileye_data_multi", 1000,kf_calc_multi);
  ros::Publisher pub= nh.advertise<kalman::radar_mobileye_data_multi>("radar_mobileye_kf", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    kalman::radar_mobileye_data_multi msg;
    for(uint8_t i=0;i<fusion_ID_Total;i++)
      msg.objs.push_back(fusion_data[i]);
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
