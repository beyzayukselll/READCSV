#pragma once
#include <iostream>
#include <Eigen/Dense>
#include "torquesignal.h"
#include <vector>

class Pulse : public TorqueSignal
{
private:
    double mDuration;
    double mMaxTorque;
    double mMinTorque;
    int mPulseNumber;
    double mTotalTime;

public:
    void setDuration(const double &duration);
    void setMaxTorque(const double &maxTorque);
    void setMinTorque(const double &minTorque);
    void setPulseNumber(const int &pulseNumber);
    void setTotalTime(double totalTime);

    double getDuration();
    double getMaxTorque();
    double getMinTorque();
    int getPulseNumber();
    double getTotalTime();

    void calculatePulseInput();
};