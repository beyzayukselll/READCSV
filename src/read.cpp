#include "read.h"
using json = nlohmann::json;
namespace pt = boost::property_tree;

void Read::readJson(std::string fileName)
{
    pt::ptree root;
    pt::read_json(fileName, root);

    std::vector<std::string> s;
   
    for (pt::ptree::value_type & v : root.get_child("signal"))
    {
        //std::cout << v.first << std::endl;
        //std::cout << "  " << v.second.data() << std::endl;
        s.push_back(v.second.data());
        inputName.push_back(v.second.data());
    }

    // int d;
    
    d.resize(s.size());

    for (int i=0; i<s.size(); ++i)
    {
        d[i] = std::stod(s[i]);
        std::cout << d[i] << std::endl;
    }
    
    
}