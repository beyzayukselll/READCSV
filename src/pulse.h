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
    Pulse();
    Pulse(const double & maxTorque, const double & minTorque,const double & duration, const int pulseNumber);
    void setDuration(const double &duration);
    void setMaxTorque(const double &maxTorque);
    void setMinTorque(const double &minTorque);
    void setPulseNumber(const int &pulseNumber);

    double getDuration();
    double getMaxTorque();
    double getMinTorque();
    int getPulseNumber();
    double getTotalTime();

    void calculatePulseInput();
};