#pragma once
#include <iostream>
#include <unsupported/Eigen/FFT>
#include <Eigen/Dense>
#include <complex>

class Frequency
{
private:
    double mSampleTime;

    Eigen::VectorXd mFrequencyResponseFunction;
    Eigen::VectorXd mVelocity;
    Eigen::VectorXd mTorque;

    Eigen::VectorXd mFrequencySeries;

public:
    void setSampleTime(const double & sampleTime);
    void setVelocity(Eigen::VectorXd velocity);
    void setTorque(Eigen::VectorXd torque);

    Eigen::VectorXd getFrequencyResponseFunction();
    double getSampleTime();
    Eigen::VectorXd getVelocity();
    Eigen::VectorXd getTorque();
    Eigen::VectorXd getFrequencySeries();

    void calculateFrequencyResponseFunction();   
    void calculateFrequencySeries();
    // yukarıdaki fonksiyon daha sonradan verilerden hesaplanacaktır.
};
