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

class LeastSquareTestFixture 
{
  public:
   const double ROOT_TOLERANCE = 1.E-5;
   std::string ResultName[4] = {"inertia",
                                "ViscousDamping",
                                "CoulombTorquePositive",
                                "CoulombTorqueNegativ"};

   const double realResultValue[4]={0.000450505952,
                                    0.001945861419,
                                    0.5987435423629,
                                    -0.575497714017};
 
};
TEST_CASE_METHOD( LeastSquareTestFixture,"read test", "[read test]" ) 
{
    
    Data data;
    data.setFile("/home/bcd/programming/least_square_identification/leastSquare_y_v5_500interval_24062022.csv");        
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();
  
   SECTION( "Torque Read Test" ) {
     REQUIRE(  torque.size()>5000);

     for (int i=0; i<torque.size()-1 ;i++){
      REQUIRE( torque(i) !=NAN);
     }
   }

    SECTION( "Velocity Read Test" ) {
     REQUIRE(  velocity.size()>66);
       for (int i=0; i<velocity.size()-1 ;i++){
      REQUIRE( velocity(i) !=NAN);
     }
    }
   
   REQUIRE(  torque.size()==velocity.size());
   
}
TEST_CASE_METHOD( LeastSquareTestFixture,"square result test", "[read test]") 
{
    
   Data data;
   data.setFile("/home/bcd/programming/least_square_identification/leastSquare_y_v5_500interval_24062022.csv");        
   data.dataRead();
   Eigen::VectorXd torque = data.getTorque();
   Eigen::VectorXd velocity = data.getVelocity();

    
  LeastSquareID ls(torque, velocity);
  const Eigen::VectorXd &myresult = ls.getCalculationResult();

  Eigen::VectorXd realRefDeger(4) ;

    realRefDeger(0)=realResultValue[0];
    CHECK (fabs(myresult(0) - realRefDeger(0)) < ROOT_TOLERANCE); 

   
//   SECTION("Inertia,ViscousDamping  and Coulomb Torque Result"){
    
//      for (int i=0;i<4;i++){
//      realRefDeger(i)=realResultValue[i];
//      THEN (ResultName[i]){
//       }
  
//     }
//    }
  
}