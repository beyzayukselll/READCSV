#include "sinesweep.h"

void SineSweep::setMinimumFrequency(const double & minimumFrequency)
{
    mMinimumFrequency = minimumFrequency;
}

void SineSweep::setMaximumFrequency(const double & maximumFrequency)
{
    mMaximumFrequency = maximumFrequency;
}

void SineSweep::setTorqueAmplitude(const double & torqueAmplitude)
{
    mTorqueAmplitude = torqueAmplitude;
}

void SineSweep::setTotalTime(const double & totalTime)
{
    mTotalTime = totalTime;
}



double SineSweep::getMinimumFrequency()
{
    return mMinimumFrequency;
}

double SineSweep::getMaximumFrequency()
{
    return mMaximumFrequency;
}

double SineSweep::getTorqueAmplitude()
{
    return mTorqueAmplitude;
}

double SineSweep::getTotalTime()
{
    return mTotalTime;
}

void SineSweep::calculateSineSweepInput()
{

    double sampleTime = getSampleTime();

    Eigen::VectorXd sineSweepInput;
    sineSweepInput.resize(mTotalTime/sampleTime);

    for (int i = 1; i < sineSweepInput.size(); i ++)
    {
        double time = i * sampleTime;
        sineSweepInput(i) = mTorqueAmplitude*(sin(2*atan(1)*4*(mMinimumFrequency*time+(mMaximumFrequency-mMinimumFrequency)/(2*mTotalTime)*time*time)));
    }
    setTorqueInput(sineSweepInput);
}
