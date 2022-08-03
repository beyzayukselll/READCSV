#pragma once

#include <iostream>
#include <Eigen/Dense>

class TorqueSignal
{
private:
    double mSampleTime;
    Eigen::VectorXd mTorqueInput;

public:
    void setSampleTime(const double & sampleTime);
    void setTorqueInput(Eigen::VectorXd torqueInput);

    double getSampleTime();
    double getTotalTime();
    Eigen::VectorXd getTorqueInput();
};