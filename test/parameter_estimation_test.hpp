#pragma once
#include "catch.hpp"
#include "../src/leastsquareid.h"
#include "../src/Data.h"

class LeastSquareTestFixture
{
public:
    const std::string tempFile = "../../data/";
    const double ROOT_TOLERANCE = 1.E-5;
    std::string ResultName[4] = {"Inertia",
                                 "Viscous Damping",
                                 "Coulomb Torque Positive",
                                 "Coulomb Torque Negative"};

    const double realResultValue[4] = {0.000450505952,
                                       0.001945861419,
                                       0.5987435423629,
                                       -0.575497714017}; // results for sampleTime = 0.001; deadBand = 0.7
};

TEST_CASE_METHOD(LeastSquareTestFixture, "read test", "[read test]")
{

    Data data;
    data.setFile(tempFile + "leastSquare_y_v5_500interval_24062022.csv");
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
    data.setFile(tempFile + "leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    double deadBand = 0.7;
    double sampleTime = 0.001;
    LeastSquareID ls(deadBand, sampleTime, torque, velocity);

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