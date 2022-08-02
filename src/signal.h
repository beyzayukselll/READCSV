#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <matplotlibcpp.h>
#include <vector>
#include <algorithm>

class Signal
{
private:
    int totalTime;
public:

    Eigen::VectorXd torqueInput;

    void setTorqueInput();
    void setTorquePulse();
    void setSineSweep();
    Eigen::VectorXd getTorqueInput();
    Eigen::VectorXd getTorquePulse();
    Eigen::VectorXd getSineSweep();

    double maxTorque;
    double minTorque;
    int pulseNumber;
    double duration;
    
    void plotTorqueInput();

};