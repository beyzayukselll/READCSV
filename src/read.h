#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <iterator>
#include <fstream>
#include "../include/json.hpp"
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class Read
{
private:
public:
    std::vector<std::string> inputName;
    std::vector<double> d;
    void readJson(std::string fileName);
};