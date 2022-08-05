#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>
#include <matplotlibcpp.h>
#include <complex>
#include <cmath>
#include "../src/leastsquareid.h"
#include "../src/Data.h"
#include "../src/read.h"
#include "../src/write.h"
#include "../src/pulse.h"
#include "../src/torquesignal.h"

#define __DEBUG__

class LeastSquareTestFixture
{
public:
    const double ROOT_TOLERANCE = 1.E-5;
    std::string ResultName[4] = {"Inertia",
                                 "Viscous Damping",
                                 "Coulomb Torque Positive",
                                 "Coulomb Torque Negative"};

    const double realResultValue[4] = {0.000450505952,
                                       0.001945861419,
                                       0.5987435423629,
                                       -0.575497714017};
    std::string SignalProporties[5] = {"maxTorque", "minTorque", "pulseNumber", "duration", "deadBand"};
};
TEST_CASE_METHOD(LeastSquareTestFixture, "read test", "[read test]")
{
    Data data;

#ifndef __DEBUG__
    data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
#else
    data.setFile("/home/bcd/programming/least_square_identification/data/leastSquare_y_v5_500interval_24062022.csv");
#endif

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

#ifndef __DEBUG__
    data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
#else
    data.setFile("/home/bcd/programming/least_square_identification/data/leastSquare_y_v5_500interval_24062022.csv");
#endif

    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    LeastSquareID ls;
    ls.setDeadBand(0.6);
    ls.setSampleTime(0.001);
    ls.setTorque(torque);
    ls.setVelocity(velocity);
    ls.calculateLeastSquareIdentification();
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
// TEST_CASE_METHOD(LeastSquareTestFixture, "Setting Signal test","[Signal Test]"){

//     Read read;
//     std::string fileName =   "../../data/setting.json";
//     read.readJson(fileName,"command");
//     CHECK (read.result[0]==1);

//     read.readJson(fileName,"signal");

//     Pulse pulse;
//     // set signal builder settings
//     pulse.setDuration(signalBuilderSettings.result[0]);
//     pulse.setMaxTorque(signalBuilderSettings.result[1]);
//     pulse.setPulseNumber(signalBuilderSettings.result[2]);
//     pulse.setDuration(signalBuilderSettings.result[3]);
//     pulse.calculatePulseInput();

//     SECTION("Signal Setting Test")
//     {
//         REQUIRE(read.result.size() ==5);
//         for (int i = 0; i < read.result.size(); i++)
//         {
//             THEN(SignalProporties[i])
//             {
//                REQUIRE(read.result[i] != NAN);
//             }
//         }
//         CHECK (signal.torqueInput.size()>0 );

//         Eigen::VectorXd absTorqueInput;
//         absTorqueInput.resize(signal.torqueInput.size());

//        THEN("Min Torque Test ") {
//         for (int i=0; i<signal.torqueInput.size();i++){

//          if (signal.torqueInput(i)>0 ){
//             continue;
//              signal.torqueInput(i)=absTorqueInput(i);
//              CHECK(absTorqueInput.minCoeff()==read.result[1]);
//          }
//         }
//       }
//         THEN("Max Torque Test"){
//         CHECK(signal.torqueInput.maxCoeff()==read.result[0] );
//         }
//     }
// }

// TEST_CASE_METHOD(LeastSquareTestFixture, "signalgeneratortest", "[signal generator test]")
// {

//     double maxTorque = 30.0;
//     double minTorque = 10.0;
//     double duration = 5.0;
//     int pulseNumber = 3;

//     Pulse p(maxTorque, minTorque, duration, pulseNumber);
//     Eigen::VectorXd torqueInput = p.getTorqueInput();

//     double testset[59] = {10, 10, 10, 10, 0, -10, -10, -10, -10, 0, 20, 20, 20, 20, 0, -20, -20, -20, -20, 0, 30, 30, 30, 30, 0, -30, -30, -30, -30, 0, 0, 30, 30, 30, 30, 0, -30, -30, -30, -30, 0, 20, 20, 20, 20, 0, -20, -20, -20, -20, 0, 10, 10, 10, 10, 0, -10, -10, -10};
//     for (int i = 0; i < 3; i++)
//     {
//         REQUIRE(torqueInput(i+1) == testset[i]);
//     }
// }
