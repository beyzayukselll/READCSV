#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/FFT>
#include <matplotlibcpp.h>
#include <iterator>
#include <vector>
#include <complex>
#include <cmath>
#include <Eigen/SVD>
#include "LeastSquareID.h"
#include "ReadData.h"

int main()
{
    ReadData data;
    data.File = "/home/bcd/programming/least_square_identification/leastSquare_y_v5_500interval_24062022.csv";
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    LeastSquareID ls;

    ls.setTorque(torque);
    ls.setVelocity(velocity);
    ls.leastSquareIdentification();
    ls.getInfo();

    return 0;
}