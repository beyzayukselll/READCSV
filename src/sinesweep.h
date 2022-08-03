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
    double mTotalTime;


public:
    void setMinimumFrequency(const double & minimumFrequency);
    void setMaximumFrequency(const double & maximumFrequency);
    void setTorqueAmplitude(const double & torqueAmplitude);
    void setTotalTime(const double & totalTime);


    double getMinimumFrequency();
    double getMaximumFrequency();
    double getTorqueAmplitude();
    double getTotalTime();

    void calculateSineSweepInput();
};

