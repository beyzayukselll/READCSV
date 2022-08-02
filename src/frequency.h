#pragma once
#include <iostream>
#include <unsupported/Eigen/FFT>
#include <Eigen/Dense>
#include <complex>

class Frequency
{
private:
    Eigen::VectorXd mFrequencyResponseFunction;
    Eigen::VectorXd mFrequency;
    Eigen::VectorXd mMagnitude;
    Eigen::VectorXd mPhase;

    Eigen::VectorXd mVelocity;
    Eigen::VectorXd mTorque;

    Eigen::VectorXd mPSDVelocity;
    Eigen::VectorXd mPSDTorque;
    Eigen::VectorXd mCPSVelocity;
    Eigen::VectorXd mCPSTorque;


public:
    Eigen::VectorXd mTime;
    void setFrequencyResponseFunction(Eigen::VectorXd frequencyResponseFunction);
    void setFrequency(Eigen::VectorXd frequency);
    void setMagnitude(Eigen::VectorXd magnitude);
    void setPhase(Eigen::VectorXd phase);
    void setVelocity(Eigen::VectorXd velocity);
    void setTorque(Eigen::VectorXd torque);
    void setPSDVelocity(Eigen::VectorXd CPSVelocity);
    void setPSDTorque(Eigen::VectorXd CPSTorque);
    void setCPSVelocity(Eigen::VectorXd CPSVelocity);
    void setCPSTorque(Eigen::VectorXd CPSTorque);

    Eigen::VectorXd getFrequencyResponseFunction();
    Eigen::VectorXd getFrequency();
    Eigen::VectorXd getMagnitude();
    Eigen::VectorXd getPhase();
    Eigen::VectorXd getVelocity();
    Eigen::VectorXd getTorque();
    Eigen::VectorXd getPSDVelocity();
    Eigen::VectorXd getPSDTorque();
    Eigen::VectorXd getCPSVelocity();
    Eigen::VectorXd getCPSTorque();


    void calculateFrequencyResponseFunction(Eigen::VectorXd torque, Eigen::VectorXd velocity);   
    void calculateFrequency(Eigen::VectorXd torque, double sampleTime);
    // yukarıdaki fonksiyon daha sonradan verilerden hesaplanacaktır.
};
