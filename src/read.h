#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <complex>
#include <valarray>
#include <iterator>
#include <fstream>
#include "../include/json.hpp"
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <Eigen/Dense>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost::algorithm;

class Read
{
private:
public:
    std::vector<std::string> inputName;
    std::vector<double> result;
    void readJson(const std::string & fileName, const std::string & objectName);
   

};