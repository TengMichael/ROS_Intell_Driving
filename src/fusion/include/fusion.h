#ifndef FUSION_H
#define FUSION_H

#include "std_msgs/String.h"
#include <milradar/obj208_multi.h>
#include <milradar/obj408_multi.h>
#include <mobileye/mobileye_Obstacle_multi.h>
#include <mobileye/vehicle_info.h>
#include <fusion/fusion_obj.h>
#include <kf_radar_mobileye/radar_mobileye_data.h>
#include <kf_radar_mobileye/radar_mobileye_data_multi.h>

#include <vector>
#include <iostream>
#include "Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

#define Object_408Num 100
#define Object_208Num 25
#define Sensors_208Num 6
#define Obstacle_Num 64

#endif // FUSION_H
