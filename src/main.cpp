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
#include<Eigen/StdVector>
#include<cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <iostream>


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
    data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    LeastSquareID ls(torque, velocity);
   

    std::vector<double> d;

    Read read;   
    
    std::string fileName =   "../../data/setting.json";
    read.readJson(fileName);
    d = read.d;
    
    
   
    Signal signal;
  
   
    signal.maxTorque = d[0];
    signal.minTorque = d[1];
    signal.pulseNumber = d[2];
    signal.duration = d[3];

    signal.setTorqueInput();

    Write write;
 
    write.write_csv("../../data/torqueInput.csv", "torqueInput", signal.torqueInput);
    

    std::vector<double> torquee;
    torquee.resize(torque.size());
    std::vector<double> velocityy;
    velocityy.resize(torque.size());

     for (int i=0;i<torque.size(); i++){
       torquee[i]= torque(i);
        velocityy[i]=velocity(i);
        std::cout<<torquee[i]<<std::endl;
     }
     
   
   std::vector<std::pair<std::string, std::vector<double>>> vals = {{"Actual Torque", torquee}, {"Actual Velocity", velocityy}};
    

     
    write.write_csv_col("../../data/ActualValues.csv",vals);



    signal.plotTorqueInput();
    return 0;
}