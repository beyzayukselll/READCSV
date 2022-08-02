#include "torquesignal.h"

void TorqueSignal::setSampleTime(double sampleTime)
{
    mSampleTime = sampleTime;
}

void TorqueSignal::setTotalTime(double totalTime)
{
    mTotalTime = totalTime;
}

void TorqueSignal::setTorqueInput(Eigen::VectorXd torqueInput)
{
    mTorqueInput = torqueInput;
}

double TorqueSignal::getSampleTime()
{
    return mSampleTime;
}

double TorqueSignal::getTotalTime()
{
    return mTotalTime;
}

Eigen::VectorXd TorqueSignal::getTorqueInput()
{
    return mTorqueInput;
}


