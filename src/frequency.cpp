#include "frequency.h"

void Frequency::setSampleTime(const double & sampleTime)
{
    mSampleTime = sampleTime;
}

void Frequency::setVelocity(Eigen::VectorXd velocity)
{
    mVelocity = velocity;
}

void Frequency::setTorque(Eigen::VectorXd torque)
{
    mTorque = torque;
}


Eigen::VectorXd Frequency::getFrequencyResponseFunction()
{
    return mFrequencyResponseFunction;
}

double Frequency::getSampleTime()
{
    return mSampleTime;
}

Eigen::VectorXd Frequency::getVelocity()
{
    return mVelocity;
}

Eigen::VectorXd Frequency::getTorque()
{
    return mTorque;
}

Eigen::VectorXd Frequency::getFrequencySeries()
{
    return mFrequencySeries;
}


void Frequency::calculateFrequencyResponseFunction()
{
    Eigen::FFT<double> fft;
    
    Eigen::VectorXcd FFT_torque = fft.fwd(mTorque);
    Eigen::VectorXcd FFT_velocity = fft.fwd(mVelocity);

    Eigen::VectorXd mPSDVelocity;
    mPSDVelocity.resize(FFT_velocity.size());

    Eigen::VectorXd mPSDTorque;
    mPSDTorque.resize(FFT_torque.size());

    Eigen::VectorXd mCPSVelocity;
    mCPSVelocity.resize(FFT_velocity.size());

    Eigen::VectorXd mCPSTorque;
    mCPSTorque.resize(FFT_torque.size());

    mFrequencyResponseFunction.resize(FFT_torque.size());

    for (int i = 0; i < FFT_torque.size(); i++)
    {
        mPSDVelocity(i) = FFT_velocity(i).real() * FFT_velocity(i).real() + FFT_velocity(i).imag() * FFT_velocity(i).imag();
        mPSDTorque(i) = FFT_torque(i).real() * FFT_torque(i).real() + FFT_torque(i).imag() * FFT_torque(i).imag();
        mCPSVelocity(i) = FFT_velocity(i).real() * FFT_velocity(i).real() + FFT_velocity(i).imag() * FFT_velocity(i).imag();
        mCPSTorque(i) = FFT_torque(i).real() * FFT_torque(i).real() + FFT_torque(i).imag() * FFT_torque(i).imag();
        mFrequencyResponseFunction(i) = mCPSTorque(i) / mPSDTorque(i);
    }
}

void Frequency::calculateFrequencySeries(){

   for (int i = 0; i < mFrequencyResponseFunction.size(); i++)
    {
        mFrequencySeries.resize(mFrequencyResponseFunction.size());
        mFrequencySeries(i) = 1.0 / mFrequencyResponseFunction.size() / mSampleTime * i;
    }
}

