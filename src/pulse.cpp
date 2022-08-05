#include "pulse.h"

Pulse::Pulse()
 {

 }

Pulse::Pulse(const double & maxTorque, const double & minTorque,const double & duration, const int pulseNumber)
: mDuration(duration), mMaxTorque(maxTorque), mMinTorque(minTorque), mPulseNumber(pulseNumber)
{
    calculatePulseInput();
}

void Pulse::setDuration(const double & duration)
{
    mDuration = duration;
}

void Pulse::setMaxTorque(const double & maxTorque)
{
    mMaxTorque = maxTorque;
}

void Pulse::setMinTorque(const double & minTorque)
{
    mMinTorque = minTorque;
}

void Pulse::setPulseNumber(const int & pulseNumber)
{
    mPulseNumber = pulseNumber;
}


double Pulse::getDuration()
{
    return mDuration;
}

double Pulse::getMaxTorque()
{
    return mMaxTorque;
}

double Pulse::getMinTorque()
{
    return mMinTorque;
}

int Pulse::getPulseNumber()
{
    return mPulseNumber;
}

double Pulse::getTotalTime()
{
    return mTotalTime;
}

void Pulse::calculatePulseInput(){   

    mTotalTime = 4 * mPulseNumber * mDuration;
    double sampleTime = getSampleTime(); // miliseconds

    Eigen::VectorXd pulseInput;
    pulseInput.resize(mTotalTime);

    for (int i = 0; i < mTotalTime; ++i)
    {
            pulseInput(i)=0;
    }

    for (int t = 0; t < mTotalTime; ++t)
    {
        for (int i = 0; i < mPulseNumber; ++i)
        {
            if (t > (2*i ) * mDuration && t < (2*i+1) * mDuration)
            {
                pulseInput(t) = (i) * (mMaxTorque - mMinTorque) / (mPulseNumber - 1) + mMinTorque;
            }
            else if (t > (2 *i + 1) * mDuration && t < 2 * (i+1) * mDuration)
            {
                pulseInput(t) = -(i) * (mMaxTorque - mMinTorque) / (mPulseNumber - 1) - mMinTorque;
            }
        }
    }

    std::vector<double> temp;
    temp.resize(mTotalTime);

    for (int i = 0; i < mTotalTime; ++i)
    {
        temp.push_back(pulseInput(i));
    }

    std::reverse (temp.begin(), temp.end());
    
    for (int i = 0; i < mTotalTime; ++i)
    {
        temp[i] = temp[i]*-1;
    }
    
    Eigen::VectorXd temp1;
    temp1.resize(mTotalTime);
    for (int i = 0; i < mTotalTime; ++i)
    {
        temp1(i) = temp[i];
    }

    pulseInput.tail((mTotalTime/2)+1) = temp1.tail((mTotalTime/2)+1);
    setTorqueInput(pulseInput);
}
