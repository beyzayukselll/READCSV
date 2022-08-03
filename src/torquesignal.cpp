#include "torquesignal.h"

void TorqueSignal::setSampleTime(const double & sampleTime)
{
    mSampleTime = sampleTime;
}

void TorqueSignal::setTorqueInput(Eigen::VectorXd torqueInput)
{
    mTorqueInput = torqueInput;
}

double TorqueSignal::getSampleTime()
{
    return mSampleTime;
}

Eigen::VectorXd TorqueSignal::getTorqueInput()
{
    return mTorqueInput;
}


