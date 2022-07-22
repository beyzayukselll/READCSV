#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/FFT>
#include <matplotlibcpp.h>
#include <complex>
#include <cmath>
#include <Eigen/SVD>
#include "../src/LeastSquareID.h"
#include "../src/Data.h"
#include "../src/read.h"
#include "../src/signal.h"
#include "../src/Write.h"

class LeastSquareTestFixture
{
public:
    const double ROOT_TOLERANCE = 1.E-5;
    std::string ResultName[4] = {"inertia",
                                 "ViscousDamping",
                                 "CoulombTorquePositive",
                                 "CoulombTorqueNegativ"};

    const double realResultValue[4] = {0.000450505952,
                                       0.001945861419,
                                       0.5987435423629,
                                       -0.575497714017};
    
};
TEST_CASE_METHOD(LeastSquareTestFixture, "read test", "[read test]")
{

    Data data;
    data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    SECTION("Torque Read Test")
    {
        REQUIRE(torque.size() > 5000);

        for (int i = 0; i < torque.size(); i++)
        {
            REQUIRE(torque(i) != NAN);
        }
    }

    SECTION("Velocity Read Test")
    {
        REQUIRE(velocity.size() > 5000);
        for (int i = 0; i < velocity.size(); i++)
        {
            REQUIRE(velocity(i) != NAN);
        }
    }

    REQUIRE(torque.size() == velocity.size());
}
TEST_CASE_METHOD(LeastSquareTestFixture, "LeastSquare result test", "[LeastSquare test]")
{

    Data data;
    data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    LeastSquareID ls(torque, velocity);
    const Eigen::VectorXd &myresult = ls.getCalculationResult();

    Eigen::VectorXd realRefDeger(sizeof(realResultValue));

    SECTION("Inertia, ViscousDamping  and Coulomb Torque Result")
    {

        for (int i = 0; i < 4; i++)
        {
            realRefDeger(i) = realResultValue[i];
            THEN(ResultName[i])
            {
                CHECK(fabs((myresult(i) - realRefDeger(i))) < ROOT_TOLERANCE);
            }
        }
    }
}
TEST_CASE_METHOD(LeastSquareTestFixture, "Signal test","[Signal Test]"){

    

    Read read;   
    
    std::string fileName =   "../../data/setting.json";
    std::vector<double> d;
    read.readJson(fileName);
    d = read.d;

    
}