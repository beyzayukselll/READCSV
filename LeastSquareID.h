#pragma once

#include <iostream>
#include <Eigen/Dense>

class LeastSquareID
{
private:
    double Inertia;
    double ViscousDamping;
    double CoulombTorquePositive;
    double CoulombTorqueNegative;
    Eigen::VectorXd Torque;
    Eigen::VectorXd Velocity;

public:
    LeastSquareID(Eigen::VectorXd torque, Eigen::VectorXd velocity);
    void setTorque(Eigen::VectorXd torque);
    void setVelocity(Eigen::VectorXd velocity);
    Eigen::VectorXd getTorque();
    Eigen::VectorXd getVelocity();
    void leastSquareIdentification();
    void getInfo();
    
};