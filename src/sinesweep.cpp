#include "sinesweep.h"

void SineSweep::setMinimumFrequency(double minimumFrequency)
{
    mMinimumFrequency = minimumFrequency;
}

void SineSweep::setMaximumFrequency(double maximumFrequency)
{
    mMaximumFrequency = maximumFrequency;
}

void SineSweep::setTorqueAmplitude(double torqueAmplitude)
{
    mTorqueAmplitude = torqueAmplitude;
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

Eigen::VectorXd SineSweep::calculateSineSweepInput(Eigen::VectorXd sineSweepInput)
{

    double sampleTime = getSampleTime();
    double totalTime = getTotalTime();
    for (int i = 1; i < sineSweepInput.size(); sampleTime*i ++)
    {
        double time = i * sampleTime;
        sineSweepInput(i) = mTorqueAmplitude*(sin(2*atan(1)*4*(mMinimumFrequency*i+(mMaximumFrequency-mMinimumFrequency)/(2*totalTime)*i*i)));
    }
}
