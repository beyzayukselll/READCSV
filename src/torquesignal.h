#pragma once

#include <iostream>
#include <Eigen/Dense>

class TorqueSignal
{
private:
    double mSampleTime;
    double mTotalTime;
    Eigen::VectorXd mTorqueInput;

public:
    void setSampleTime(double sampleTime);
    void setTotalTime(double totalTime);
    void setTorqueInput(Eigen::VectorXd torqueInput);

    double getSampleTime();
    double getTotalTime();
    Eigen::VectorXd getTorqueInput();
};