#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT

#include <vector>
#include <iostream>
#include "Eigen/Dense"

class KalmanFilter {
public:

    // id object
    int8_t id_;

    // state vector
    Eigen::VectorXd x_,x_radar,x_mobileye;

    // state covariance matrix
    Eigen::MatrixXd P_,P_radar,P_mobileye;

    // state transistion matrix
    Eigen::MatrixXd F_;

    // process covariance matrix
    Eigen::MatrixXd Q_;

    // measurement matrix
    Eigen::MatrixXd H_radar,H_mobileye;

    // measurement covariance matrix
    Eigen::MatrixXd R_radar,R_mobileye;

    // state vector
    Eigen::VectorXd z_;
    // timestamp
    uint previous_timestamp_;

    /*** Constructor*/
    KalmanFilter();

    /**** Destructor*/
    virtual ~KalmanFilter();

    /*** Prediction Predicts the state and the state covariance
   * using the process model @param delta_T Time between k and k+1 in s
   */
    void Predict();

    /*** Updates the state by using standard Kalman Filter equations
   * @param z The measurement at k+1 */
    void Update_radar(const Eigen::VectorXd &z);
    void Update_mobileye(const Eigen::VectorXd &z);
};
// Struct with kalman data and timestamp for next time
struct kalman_data{
  Eigen::VectorXd x_;
  Eigen::MatrixXd P_;
  uint previous_timestamp_;
};
// Vector for kalman_data structure
std::vector <kalman_data> kalman_vector;

#endif /* KALMAN_FILTER_H_ */
