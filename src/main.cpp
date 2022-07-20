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

    // Write write;
    //  std::string fileName = "/home/bcd/programming/least_square_identification/data/test.json";
    // std::string fileName1 = "/home/bcd/programming/least_square_identification/data/write.json";

    // write.dataWrite(myr,fileName);
    // write.dataWriteNew(myr, fileName1);

    Signal signal;
    signal.maxTorque = 50;
    signal.minTorque = 5;
    signal.pulseNumber = 12;
    signal.duration = 200;

    signal.setTorqueInput();
    signal.plotTorqueInput();

    // std::cout << signal.torqueInput.size() << std::endl;
  
    // Eigen::VectorXd torque;
    // torque = signal.getTorqueInput();
    // std::cout << torque.size() << std::endl;

    // std::vector<double> x;
    // x.resize(torque.size());

    // matplotlibcpp::figure();
    // for (int i = 0; i < torque.size(); i++)
    // {
    //     x[i] = torque(i);
    // }
    // std::cout << x.size() << std::endl;

    // std::vector<double> time;
    // time.resize(torque.size());
    // for (int i = 0; i < torque.size(); i++)
    // {
    //     time[i] = i;
    // }

    // std::cout << time.size() << std::endl;

    // matplotlibcpp::plot(x);
    // matplotlibcpp::xlabel("Time [s]");
    // matplotlibcpp::grid(true);
    // matplotlibcpp::title("Trajectory");
    // matplotlibcpp::show();
    return 0;
}