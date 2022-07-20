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
    void setTorqueInput();
    Eigen::VectorXd torqueInput;
    Eigen::VectorXd getTorqueInput();
    double maxTorque;
    double minTorque;
    int pulseNumber;
    double duration;

    void plotTorqueInput();

};