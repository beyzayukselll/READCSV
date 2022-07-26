#include "read.h"
using json = nlohmann::json;
namespace pt = boost::property_tree;


void Read::readJson(const std::string & fileName, const std::string & objectName )
{
    pt::ptree root;
   
    pt::read_json(fileName, root);

    std::vector<std::string> s;
   
    for (pt::ptree::value_type & v : root.get_child(objectName))
    {
        //std::cout << v.first << std::endl;
        //std::cout << "  " << v.second.data() << std::endl;
        s.push_back(v.second.data());
        inputName.push_back(v.second.data());
    }

  

    result.resize(s.size());

    for (int i=0; i<s.size(); ++i)
    {
        result[i] = std::stod(s[i]);
        
    }
    
   //bool roll = root.get<bool>("start");  //read and save the roll no in *roll*
    double roll = root.get<double>("start"); 
    
}
