#include "Write.h"

using json = nlohmann::json;
namespace pt = boost::property_tree;

void Write::dataWrite(Eigen::VectorXd leastSquareResult, std::string fileName)
{
    std::string ResultName[4] = {"inertia",
                                 "ViscousDamping",
                                 "CoulombTorquePositive",
                                 "CoulombTorqueNegative"};

    std::ofstream myfile;
    myfile.open(fileName);
    myfile << "{";
    //  myfile << "\n\t";

    myfile << "\n"
              "\"leastSquareResult\":\n{\n\t";
    for (int i = 0; i < leastSquareResult.size(); ++i)
    {
        // ResultName[i] = "\"" + ResultName[i] + "\"";
        myfile << "\"" << ResultName[i] << "\":" << leastSquareResult(i);
        if (i < leastSquareResult.size() - 1)
        {
            myfile << ",\n\t";
        }
    }
    myfile << "\n}\n";
    myfile << "}";
    myfile.close();
}

void Write::dataWriteNew(Eigen::VectorXd leastSquareResult, std::string fileName)
{
    std::string ResultName[4] = {"inertia",
                                 "ViscousDamping",
                                 "CoulombTorquePositive",
                                 "CoulombTorqueNegative"};
    pt::ptree root;

    // Create a node
    pt::ptree animals_node;

    std::vector<std::pair<std::string, std::string>> leastSquareResults;

    for (int i = 0; i < leastSquareResult.size(); ++i)
    {
        std::stringstream ss;
        ss << leastSquareResult(i);
        std::string str = ss.str();
        std::pair<std::string, std::string> pair = std::make_pair(ResultName[i], str);
        leastSquareResults.push_back(pair);
    }

    // Add animals as childs
    for (auto &animal : leastSquareResults)
        animals_node.put(animal.first, animal.second);
    // Add the new node to the root
    root.add_child("leastSquareResults", animals_node);

    pt::write_json("/home/bcd/programming/least_square_identification/data/write.json", root);
}
