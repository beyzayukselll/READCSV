#include "frequency.h"

void Frequency::setFrequencyResponseFunction(Eigen::VectorXd frequencyResponseFunction)
{
    mFrequencyResponseFunction = frequencyResponseFunction;
}

void Frequency::setFrequency(Eigen::VectorXd frequency)
{
    mFrequency = frequency;
}

void Frequency::setMagnitude(Eigen::VectorXd magnitude)
{
    mMagnitude = magnitude;
}

void Frequency::setPhase(Eigen::VectorXd phase)
{
    mPhase = phase;
}

void Frequency::setVelocity(Eigen::VectorXd velocity)
{
    mVelocity = velocity;
}

void Frequency::setTorque(Eigen::VectorXd torque)
{
    mTorque = torque;
}

void Frequency::setPSDVelocity(Eigen::VectorXd CPSVelocity)
{
    mPSDVelocity = CPSVelocity;
}

void Frequency::setPSDTorque(Eigen::VectorXd CPSTorque)
{
    mPSDTorque = CPSTorque;
}

void Frequency::setCPSVelocity(Eigen::VectorXd CPSVelocity)
{
    mCPSVelocity = CPSVelocity;
}

void Frequency::setCPSTorque(Eigen::VectorXd CPSTorque)
{
    mCPSTorque = CPSTorque;
}



Eigen::VectorXd Frequency::getFrequencyResponseFunction()
{
    return mFrequencyResponseFunction;
}

Eigen::VectorXd Frequency::getFrequency()
{
    return mFrequency;
}

Eigen::VectorXd Frequency::getMagnitude()
{
    return mMagnitude;
}

Eigen::VectorXd Frequency::getPhase()
{
    return mPhase;
}

Eigen::VectorXd Frequency::getVelocity()
{
    return mVelocity;
}

Eigen::VectorXd Frequency::getTorque()
{
    return mTorque;
}

Eigen::VectorXd Frequency::getPSDVelocity()
{
    return mPSDVelocity;
}

Eigen::VectorXd Frequency::getPSDTorque()
{
    return mPSDTorque;
}

Eigen::VectorXd Frequency::getCPSVelocity()
{
    return mCPSVelocity;
}

Eigen::VectorXd Frequency::getCPSTorque()
{
    return mCPSTorque;
}

void Frequency::calculateFrequencyResponseFunction(Eigen::VectorXd torque, Eigen::VectorXd velocity)
{
    mVelocity = velocity;
    mTorque = torque;

    Eigen::FFT<double> fft;
    
    Eigen::VectorXcd FFT_torque = fft.fwd(mTorque);
    Eigen::VectorXcd FFT_velocity = fft.fwd(mVelocity);

    Eigen::VectorXd mPSDVelocity;
    Eigen::VectorXd mPSDTorque;

    Eigen::VectorXd mCPSVelocity;
    Eigen::VectorXd mCPSTorque;

    Eigen::VectorXd mFrequencyResponseFunction;

    for (int i = 0; i < FFT_torque.size(); i++)
    {
        mPSDVelocity(i) = FFT_velocity(i).real() * FFT_velocity(i).real() + FFT_velocity(i).imag() * FFT_velocity(i).imag();
        mPSDTorque(i) = FFT_torque(i).real() * FFT_torque(i).real() + FFT_torque(i).imag() * FFT_torque(i).imag();
        mCPSVelocity(i) = FFT_velocity(i).real() * FFT_velocity(i).real() + FFT_velocity(i).imag() * FFT_velocity(i).imag();
        mCPSTorque(i) = FFT_torque(i).real() * FFT_torque(i).real() + FFT_torque(i).imag() * FFT_torque(i).imag();
        mFrequencyResponseFunction(i) = mCPSTorque(i) / mPSDTorque(i);
    }
    setFrequencyResponseFunction(mFrequencyResponseFunction);
    setPSDVelocity(mPSDVelocity);
    setPSDTorque(mPSDTorque);
    setCPSVelocity(mCPSVelocity);
    setCPSTorque(mCPSTorque);
}

void Frequency::calculateFrequency(Eigen::VectorXd torque, double sampleTime){

   for (int i = 0; i < torque.size(); i++)
    {
        mFrequency(i) = 1.0 / torque.size() / sampleTime * i;
    }
    setFrequency(mFrequency);
}

