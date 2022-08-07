#pragma once
#include <iostream>
#include <matplotlibcpp.h>
#include <Eigen/Dense>

class Plot
{
public:
    void torquePlot(const Eigen::VectorXd & torque);

    void frfPlot(const Eigen::VectorXd & frequencySeries, const Eigen::VectorXd & frf);
};