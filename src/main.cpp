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
#include <vector>
// int functionExampleShallowCopy (LeastSquareID &myparameter )
//  {
//      Data data;
//     data.setFile("/home/bcd/programming/least_square_identification/leastSquare_y_v5_500interval_24062022.csv");
//     data.dataRead();
//     Eigen::VectorXd torque = data.getTorque();
//     myparameter.setTorque(torque);
//  }

//  int functionExampleDeepCopy (LeastSquareID myparameter )
//  {

//  }
int main()
{
    Data data;
    data.setFile("/home/kose/programming/least_square_identification/data/leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    LeastSquareID ls(torque, velocity);
    ls.getInfo();
    
    const Eigen::VectorXd &myr = ls.getCalculationResult();
    

    // int nAxis = 3;
    // std::vector<LeastSquareID *> allAxis;// =new std::vector<LeastSquareID *>();
    // for (int i=0;i<nAxis;++i)
    // {
    //     LeastSquareID *curAxisId = new LeastSquareID(torque,velocity);
    //     allAxis.push_back(curAxisId);
    //     functionExampleShallowCopy(*curAxisId);
    //     std::cout << curAxisId->getTorque().operator[](0);
    //     functionExampleDeepCopy(*curAxisId);

    // }

    return 0;
}