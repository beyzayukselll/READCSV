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

    json j;
    j["leastSquareResults"] = {};
    for (int i = 0; i < leastSquareResult.size(); ++i)
    {
        j["leastSquareResults"][ResultName[i]] = leastSquareResult(i);
    }
    
    std::ofstream o(fileName);
    o << std::setw(4) << j << std::endl;
    o.close();
}

void Write::write_csv(std::string filename, std::string colname, Eigen::VectorXd vals)
{

    std::ofstream myFile(filename);

    // Send the column name to the stream
    myFile << colname << "\n";

    // Send data to the stream
    for (int i = 0; i < vals.size(); ++i)
    {
        myFile << vals(i) << "\t\n";
    }

    // Close the file
    myFile.close();
}

void Write::write_csv_col(std::string filename, std::vector<std::pair<std::string, std::vector<double>>> dataset)
{
    std::ofstream myFile(filename);

    // Send column names to the stream
    for (int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if (j != dataset.size() - 1)
            myFile << "\t"; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for (int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if (j != dataset.size() - 1)
                myFile << "\t"; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
};
