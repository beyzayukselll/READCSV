#include "read.h"
using json = nlohmann::json;
namespace pt = boost::property_tree;


void Read::readJson(const std::string & fileName, const std::string & objectName )
{
    pt::ptree root;
   
    pt::read_json(fileName, root);

    std::vector<std::string> s;
   
     //bool roll = root.get<bool>("command");  //read and save the roll no in *roll*
    for (pt::ptree::value_type & v : root.get_child(objectName))
    {        
        s.push_back(v.second.data());
        inputName.push_back(v.second.data());
    }

  
    
    result.resize(s.size());

    for (int i=0; i<s.size(); ++i)
    {
        result[i] = std::stod(s[i]);
        
    }
          
    
    
}
