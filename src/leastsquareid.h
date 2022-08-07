#pragma once

#include <iostream>
#include <Eigen/Dense>

class LeastSquareID
{
private:
    double mInertia;
    double mViscousDamping;
    double mCoulombTorquePositive;
    double mCoulombTorqueNegative;

    double mDeadBand;
    double mSampleTime;
    Eigen::VectorXd mTorque;
    Eigen::VectorXd mVelocity;
    Eigen::VectorXd mCalculationResult;

public:
    LeastSquareID();
    LeastSquareID(const double &deadBand,const double &sampleTime,const Eigen::VectorXd &torque,const Eigen::VectorXd &velocity);
    void setDeadBand(const double & deadBand);
    void setSampleTime(const double & sampleTime);
    void setTorque(const Eigen::VectorXd & torque);
    void setVelocity(const Eigen::VectorXd & velocity);

    double getDeadBand();
    Eigen::VectorXd getTorque();
    Eigen::VectorXd getVelocity();
    double getSampleTime();

    void calculateLeastSquareIdentification();

    const Eigen::VectorXd &getCalculationResult()const;

    void getInfo();
};