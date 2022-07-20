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
#include "Write.h"
#include "signal.h"
#include "read.h"
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
    // Data data;
    // data.setFile("/home/bcd/programming/least_square_identification/data/leastSquare_y_v5_500interval_24062022.csv");
    // data.dataRead();
    // Eigen::VectorXd torque = data.getTorque();
    // Eigen::VectorXd velocity = data.getVelocity();

    // LeastSquareID ls(torque, velocity);
    // ls.getInfo();

    // const Eigen::VectorXd &myr = ls.getCalculationResult();

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

    std::vector<double> d;

    Read read;
    std::string fileName = "/home/bcd/programming/least_square_identification/data/file.json";
    read.readJson(fileName);
    d = read.d;
    std::vector <std::string> inputName = read.inputName;
    // Write write;
    // std::string fileName = "/home/bcd/programming/least_square_identification/data/test.json";
    // std::string fileName1 = "/home/bcd/programming/least_square_identification/data/write.json";

    // write.dataWrite(myr,fileName);
    // write.dataWriteNew(myr, fileName1);

    Signal signal;
  
   
    signal.maxTorque = d[0];
    signal.minTorque = d[1];
    signal.pulseNumber = d[2];
    signal.duration = d[3];

    signal.setTorqueInput();

    std::cout << signal.torqueInput << std::endl;
    signal.plotTorqueInput();
  
    
  

    return 0;
}