#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/FFT>
#include <matplotlibcpp.h>
#include <complex>
#include <cmath>
#include <Eigen/SVD>
#include "leastsquareid.h"
#include "Data.h"
#include <vector>
#include "write.h"
#include "signal.h"
#include "read.h"
#include <Eigen/StdVector>
#include<cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <iostream>


int main()
{
    Data data;
    data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    LeastSquareID ls;
  
    Read read;   


    
   // const std::string & fileName =   "../../data/setting.json";
    read.readJson("../../data/setting.json","signal");
   

    for (int i=0; i<read.result.size();i++){
      
     std::cout << read.result[i]<< "\n";
    
    }
    Signal signal;
     
    signal.maxTorque = read.result[0];
    signal.minTorque = read.result[1];
    signal.pulseNumber = read.result[2];
    signal.duration = read.result[3];
    ls.deadBand = read.result[4];

    // read.readJson("../../data/setting.json","start");
    //  for (int i=0; i<read.result.size();i++){
      
    //  std::cout << read.result[i] << "\n";
    
    // }
   
    ls.calculateLeastSquareIdentification(torque, velocity, ls.deadBand);
  
    ls.getInfo();
   
    signal.setTorqueInput();

    Write write;
 
    write.write_csv("../../data/torqueInput.csv", "Torque Input", signal.torqueInput);
    

    std::vector<double> torquee;
    torquee.resize(torque.size());
    std::vector<double> velocityy;
    velocityy.resize(torque.size());

     for (int i=0;i<torque.size(); i++){
       torquee[i]= torque(i);
        velocityy[i]=velocity(i);
     }
     
     
   std::vector<std::pair<std::string, std::vector<double>>> vals = {{"Actual Torque", torquee}, {"Actual Velocity", velocityy}};
    

     
    write.write_csv_col("../../data/ActualValues.csv",vals);



   // signal.plotTorqueInput();
    return 0;
}