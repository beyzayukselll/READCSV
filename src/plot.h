#pragma once
#include <iostream>
#include <matplotlibcpp.h>
#include <Eigen/Dense>

class Plot
{
public:
  void logPlot(Eigen::VectorXd position,Eigen::VectorXd velocity,Eigen::VectorXd acc,double sampleTime);


    // void torquePlot(const Eigen::VectorXd & torque);

    // void frfPlot(const Eigen::VectorXd & frequencySeries, const Eigen::VectorXd & frf);
};