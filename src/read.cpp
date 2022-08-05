#include "read.h"
using json = nlohmann::json;
namespace pt = boost::property_tree;

void Read::readJson(const std::string & fileName, const std::string & objectName )
{
    pt::ptree root;
   
    pt::read_json(fileName, root);

    std::vector<double> s;
   
    for (pt::ptree::value_type & v : root.get_child(objectName))
    {        
        s.push_back(v.second.get_value<double>());
        // s.push_back(v.second.data());
    }
    
    mResult.resize(s.size());

    for (int i=0; i<s.size(); ++i)
    {
        mResult[i] = s[i];
    }
}
