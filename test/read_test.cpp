#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
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

class ReadTestFixture {
	
};
TEST_CASE_METHOD( ReadTestFixture,"read test", "[read test]" ) {
    
    Data data;
    data.setFile("/home/bcd/programming/least_square_identification/leastSquare_y_v5_500interval_24062022.csv");
     
   
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();
     REQUIRE(  torque(0)==0);

    LeastSquareID ls(torque, velocity);
    ls.leastSquareIdentification();

    
}
