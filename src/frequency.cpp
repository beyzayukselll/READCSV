#include "frequency.h"

Frequency::Frequency()
{
}

Frequency::Frequency(const double &sampleTime, const Eigen::VectorXd &velocity, const Eigen::VectorXd &torque)
    : mSampleTime(sampleTime), mVelocity(velocity), mTorque(torque)
{
    calculateFrequencyResponseFunction();
}

void Frequency::setSampleTime(const double &sampleTime)
{
    mSampleTime = sampleTime;
}

void Frequency::setVelocity(const Eigen::VectorXd &velocity)
{
    mVelocity = velocity;
}

void Frequency::setTorque(const Eigen::VectorXd &torque)
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

    std::vector<double> time_vec;
    std::vector<double> velocity_vec;
    std::vector<double> torque_vec;

    for (int i = 0; i < mTorque.size(); i++)
    {
        time_vec = {i * mSampleTime};
        velocity_vec.push_back(mVelocity(i));
        torque_vec.push_back(mTorque(i));
    }  

    Eigen::FFT<double> fft;
    std::vector<std::complex<double> > FFT_velocity;
    std::vector<std::complex<double> > FFT_torque;

  
    fft.fwd( FFT_velocity, velocity_vec);
    fft.fwd( FFT_torque, torque_vec);

    std::vector<double> mPSDVelocity_vec;
    mPSDVelocity_vec.resize(mTorque.size());
    std::vector<double> mPSDTorque_vec;
    mPSDTorque_vec.resize(mTorque.size());
    std::vector<double> mCPSVelocity_vec;
    mCPSVelocity_vec.resize(mTorque.size());
    std::vector<double> mCPSTorque_vec;
    mCPSTorque_vec.resize(mTorque.size());

    mFrequencyResponseFunction.resize(mTorque.size());


    for (int i = 0; i < mTorque.size(); i++)
    {
        mPSDVelocity_vec[i] = FFT_velocity[i].real() * FFT_velocity[i].real() + FFT_velocity[i].imag() * FFT_velocity[i].imag();
        mPSDTorque_vec[i] = FFT_torque[i].real() * FFT_torque[i].real() + FFT_torque[i].imag() * FFT_torque[i].imag();
        mCPSVelocity_vec[i] = (FFT_torque[i].real() + FFT_torque[i].imag() ) * ( FFT_velocity[i].real() - FFT_velocity[i].imag());
        mCPSTorque_vec[i] = ( FFT_velocity[i].real() + FFT_velocity[i].imag()) * (FFT_torque[i].real() - FFT_torque[i].imag() );
        mFrequencyResponseFunction(i) = mCPSVelocity_vec[i] / mCPSTorque_vec[i];
    }
   

    calculateFrequencySeries();
}

void Frequency::calculateFrequencySeries()
{

    for (int i = 0; i < mFrequencyResponseFunction.size(); i++)
    {
        mFrequencySeries.resize(mFrequencyResponseFunction.size());
        mFrequencySeries(i) = 1.0 / mFrequencyResponseFunction.size() / mSampleTime * i;
    }
}
