#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <iterator>
#include <vector>

class Data
{
private:
    std::string File;
    Eigen::VectorXd Velocity;
    Eigen::VectorXd Torque;

public:
    void setFile(std::string file);
    void setVelocity(Eigen::VectorXd velocity);
    void setTorque(Eigen::VectorXd torque);
    void dataRead();
    Eigen::VectorXd getTorque();
    Eigen::VectorXd getVelocity();
    
};