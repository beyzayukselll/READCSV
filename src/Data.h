#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <iterator>
#include <vector>

class Data
{
private:
    std::string mFile;
    Eigen::VectorXd mVelocity;
    Eigen::VectorXd mTorque;

public:
    void setFile(const std::string & file);
    void setVelocity(Eigen::VectorXd velocity);
    void setTorque(Eigen::VectorXd torque);
    
    std::string getFile();
    Eigen::VectorXd getTorque();
    Eigen::VectorXd getVelocity();
    void dataRead();

};