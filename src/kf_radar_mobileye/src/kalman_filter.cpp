#include <ros/ros.h>
#include <kf_radar_mobileye/kalman_filter.h>
#include <kf_radar_mobileye/radar_mobileye_data.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;

KalmanFilter kf;

KalmanFilter::KalmanFilter() {}
KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Predict() {
  /**TODO:predict the state */
  x_ = F_ * x_;
  MatrixXd Ft = F_.transpose();
  P_ = F_ * P_ * Ft + Q_;
}
void KalmanFilter::Update_radar(const VectorXd &z) {
  /***TODO:update the state by using Kalman Filter equations*/
  VectorXd z_pred = H_radar * x_;
  VectorXd y = z - z_pred;
  MatrixXd Ht = H_radar.transpose();
  MatrixXd S = H_radar * P_ * Ht + R_radar;
  MatrixXd Si = S.inverse();
  MatrixXd PHt = P_ * Ht;
  MatrixXd K = PHt * Si;
  //new estimate
  x_radar = z_pred + (K * y);
  long x_size = x_radar.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_radar = (I - K * H_radar) * P_;
}
void KalmanFilter::Update_mobileye(const VectorXd &z) {
  /***TODO:update the state by using Kalman Filter equations*/
  VectorXd z_pred = H_mobileye * x_;
  VectorXd y = z - z_pred;
  MatrixXd Ht = H_mobileye.transpose();
  MatrixXd S = H_mobileye * P_ * Ht + R_mobileye;
  MatrixXd Si = S.inverse();
  MatrixXd PHt = P_ * Ht;
  MatrixXd K = PHt * Si;
  //new estimate
  x_mobileye = z_pred + (K * y);
  long x_size = x_mobileye.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_mobileye = (I - K * H_mobileye) * P_;
}
void kf_calc(const kf_radar_mobileye::radar_mobileye_data measure_value){
  ROS_INFO_STREAM("Start ProcessMeasurement.. ");
  /*Initialization*/
  kf.id_ = measure_value.ID;
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
    ROS_INFO_STREAM("First computation. kf id: " << kf.id_ );
    // first measurement
    kf.x_ = VectorXd(4);
    kf.x_ << 1, 1, 1, 1;
    /*Initialize state*/
    kf.x_(0) = measure_value.radar_DistX;
    kf.x_(1) = measure_value.radar_DistY;
    kf.x_(2) = measure_value.radar_VrelX;
    kf.x_(3) = measure_value.radar_VrelY;
    kf.previous_timestamp_ = measure_value.timestamp;
    //state covariance matrix P
    kf.P_ = MatrixXd(4, 4);
    kf.P_ << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
  }
  else
  {
    kf.x_ = kalman_vector[kf.id_].x_;
    kf.P_ = kalman_vector[kf.id_].P_;
    kf.previous_timestamp_ = kalman_vector[kf.id_].previous_timestamp_;
    ROS_INFO_STREAM("New data update after init.");
  }
  /*  Prediction*/
  kf.F_ = MatrixXd(4, 4);
  kf.F_ << 1, 0, 1, 0,
      0, 1, 0, 1,
      0, 0, 1, 0,
      0, 0, 0, 1;
  //compute the time elapsed between the current and previous measurements
  float dt = (measure_value.timestamp - kf.previous_timestamp_) / 1000000000;	//dt - expressed in seconds
  kf.previous_timestamp_ = measure_value.timestamp;
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
  ROS_INFO_STREAM("Update EKF Predict..");
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
  kf.R_mobileye= MatrixXd(4, 4);
  kf.R_mobileye<< 0.09, 0, 0,
      0, 0.09, 0,
      0, 0, 0.0009;
  ROS_INFO_STREAM("Calling update KF");
  kf.z_=VectorXd(4);
  kf.z_(0) = measure_value.radar_DistX;
  kf.z_(1) = measure_value.radar_DistY;
  kf.z_(2) = measure_value.radar_VrelX;
  kf.z_(3) = measure_value.radar_VrelY;
  kf.Update_radar(kf.z_);
  kf.z_=VectorXd(3);
  kf.z_(0) = measure_value.mobileye_DistX;
  kf.z_(1) = measure_value.mobileye_DistY;
  kf.z_(2) = measure_value.mobileye_VrelX;
  kf.Update_mobileye(kf.z_);
  // Fusion the estimation
  MatrixXd S =kf.P_radar.inverse()+kf.P_mobileye.inverse();
  kf.P_=S.inverse();
  kf.x_=kf.P_*(kf.P_radar*kf.x_radar+kf.P_mobileye*kf.x_mobileye);
  // Store all the values for next measurement
  kalman_vector[kf.id_].x_ = kf.x_;
  kalman_vector[kf.id_].P_ = kf.P_;
  kalman_vector[kf.id_].previous_timestamp_ = kf.previous_timestamp_;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "kalman_filter");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe ("radar_mobileye_data", 1000,kf_calc);

  ROS_INFO("Hello world!");
}
