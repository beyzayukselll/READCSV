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
    double mSampleTime;
     Eigen::VectorXd time;
public:
    void setFile(const std::string &file);

    std::string getFile();
    Eigen::VectorXd getTorque();
    Eigen::VectorXd getVelocity();
    Eigen::VectorXd getTime();
    double getSampleTime();
    void dataRead();

};  