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
    Eigen::VectorXd mTorque;
    Eigen::VectorXd mVelocity;
    Eigen::VectorXd mCalculationResult;

public:
    double deadBand;
    void setTorque(Eigen::VectorXd torque);
    
    void setVelocity(Eigen::VectorXd velocity);

    Eigen::VectorXd getTorque();
    Eigen::VectorXd getVelocity();

    Eigen::VectorXd &getTorqueRef();

    void calculateLeastSquareIdentification(Eigen::VectorXd torque, Eigen::VectorXd velocity, double deadBand);

    const Eigen::VectorXd &getCalculationResult()const;

    void getInfo();
    Eigen::VectorXd &getVelocityRef();

};