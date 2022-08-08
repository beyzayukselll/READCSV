#pragma once
#include "catch.hpp"
#include "../src/frequency.h"
#include "../src/Data.h"

class FrequencyTestFixture
{
    public:
    const std::string tempFile = "../../data/";
    const double ROOT_TOLERANCE = 1.E-5;
    
};
TEST_CASE_METHOD(FrequencyTestFixture, "Frequency result test", "[Frequency test]")
{
    Data data;
    data.setFile(tempFile + "sineSweept_y_Axis_torqueMode_0To70Hz_2tor_05sample_27062022.csv");
    data.dataRead();

    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();
    double sampleTime = 0.0005;

    Frequency fr(sampleTime, velocity, torque);
    Eigen::VectorXd frequencyResponseFunction = fr.getFrequencyResponseFunction();
    Eigen::VectorXd frequencySeries = fr.getFrequencySeries();
}
