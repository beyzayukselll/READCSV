#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <iterator>
#include <fstream>
#include "../include/json.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class Write
{
public:
    void dataWrite (Eigen::VectorXd leastSquareResult, std::string fileName);
    void dataWriteNew (Eigen::VectorXd leastSquareResult, std::string fileName);
};


