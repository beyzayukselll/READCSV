#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <iterator>
#include <fstream>
#include "../include/json.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <string>

class Write
{
public:
   // void dataWrite (Eigen::VectorXd leastSquareResult, std::string fileName);
   
    void dataWriteNew (Eigen::VectorXd leastSquareResult, std::string fileName);
    void write_csv(std::string filename, std::string colname, Eigen::VectorXd vals);
    void write_csv_col(std::string filename, std::vector<std::pair<std::string, std::vector<double>>> dataset);


};


