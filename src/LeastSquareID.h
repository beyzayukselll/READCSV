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
    void calculateLeastSquareIdentification();

public:
    LeastSquareID(Eigen::VectorXd torque, Eigen::VectorXd velocity);
    void setTorque(Eigen::VectorXd torque);
    void setVelocity(Eigen::VectorXd velocity);

    Eigen::VectorXd getTorque();
    Eigen::VectorXd getVelocity();

    Eigen::VectorXd &getTorqueRef();
    Eigen::VectorXd &getVelocityRef();

    const Eigen::VectorXd &getCalculationResult()const;

    void getInfo();
    
};