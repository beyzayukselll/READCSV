#pragma once
#include <iostream>
#include <Eigen/Dense>
#include "torquesignal.h"
#include <matplotlibcpp.h>


class SineSweep : public TorqueSignal
{
private:
    double mMinimumFrequency;
    double mMaximumFrequency;
    double mTorqueAmplitude;

public:
    void setMinimumFrequency(double minimumFrequency);
    void setMaximumFrequency(double maximumFrequency);
    void setTorqueAmplitude(double torqueAmplitude);

    double getMinimumFrequency();
    double getMaximumFrequency();
    double getTorqueAmplitude();
    Eigen::VectorXd calculateSineSweepInput();

    void plotTorqueInput();

};

