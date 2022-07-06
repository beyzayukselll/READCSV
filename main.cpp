#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/FFT>
#include <matplotlibcpp.h>
#include <complex>
#include <cmath>
#include <Eigen/SVD>
#include "LeastSquareID.h"
#include "Data.h"

int main()
{
    Data data;
    data.setFile("/home/beyza/least_square/least_square_identification/leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    LeastSquareID ls(torque, velocity);
    ls.leastSquareIdentification();
    ls.getInfo();
    
    return 0;
}