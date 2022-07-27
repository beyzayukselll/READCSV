#include "write.h"

using json = nlohmann::json;
namespace pt = boost::property_tree;

// void Write::dataWrite(Eigen::VectorXd leastSquareResult, std::string fileName)
// {
//     std::string ResultName[4] = {"inertia",
//                                  "ViscousDamping",
//                                  "CoulombTorquePositive",
//                                  "CoulombTorqueNegative"};

//     std::ofstream myfile;
//     myfile.open(fileName);
//     myfile << "{";
//     //  myfile << "\n\t";

//     myfile << "\n"
//               "\"leastSquareResult\":\n{\n\t";
//     for (int i = 0; i < leastSquareResult.size(); ++i)
//     {
//         // ResultName[i] = "\"" + ResultName[i] + "\"";
//         myfile << "\"" << ResultName[i] << "\":" << leastSquareResult(i);
//         if (i < leastSquareResult.size() - 1)
//         {
//             myfile << ",\n\t";
//         }
//     }
//     myfile << "\n}\n";
//     myfile << "}";
//     myfile.close();
// }

void Write::dataWriteJson(Eigen::VectorXd leastSquareResult, std::string fileName)
{
    std::string ResultName[4] = {"inertia",
                                 "ViscousDamping",
                                 "CoulombTorquePositive",
                                 "CoulombTorqueNegative"};
    pt::ptree root;

    // Create a node
    pt::ptree least_square_node;

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
        least_square_node.put(animal.first, animal.second);
    // Add the new node to the root
    root.add_child("leastSquareResults", least_square_node);
    
    pt::write_json(fileName, root);

}

void Write:: write_csv (std::string filename, std::string colname,  Eigen::VectorXd vals){
  
    std::ofstream myFile(filename);
    
    // Send the column name to the stream
    myFile << colname << "\n";
    
    // Send data to the stream
    for(int i = 0; i < vals.size(); ++i)
    {
        myFile << vals(i) << "\t\n";
    }
    
    // Close the file
    myFile.close();
}

void Write::write_csv_col(std::string filename, std::vector<std::pair<std::string, std::vector<double>>> dataset){

    std::ofstream myFile(filename);
    
    // Send column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << "\t"; // No comma at end of line
    }
    myFile << "\n";
    
    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << "\t"; // No comma at end of line
        }
        myFile << "\n";
    }
    
    // Close the file
    myFile.close();
};

