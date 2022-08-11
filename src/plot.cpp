#include "plot.h"

void Plot::logPlot(Eigen::VectorXd position,Eigen::VectorXd velocity,Eigen::VectorXd acc)
{

    std::vector<double> pos_vec;
    std::vector<double> vec_vec;
   std::vector<double> act_vec;


    for (int i = 0; i < position.size(); i++)
    {
        pos_vec.push_back(position(i));
        vec_vec.push_back(velocity(i));
        act_vec.push_back(acc(i));              

    }


    matplotlibcpp::figure();
   
     matplotlibcpp::plot(pos_vec,"r--");
    matplotlibcpp::plot(vec_vec,"b--");
    matplotlibcpp::xlabel("Time in lecture"); 
     matplotlibcpp::ylabel("velocity"); 
    matplotlibcpp::title("Test Log");
     matplotlibcpp::plot(act_vec,"b--");
    matplotlibcpp::grid(true);
    matplotlibcpp::show();

}

// void Plot::torquePlot(const Eigen::VectorXd & torque)
// {
//     std::vector<double> torque_vec;

//     for (int i = 0; i < torque.size(); i++)
//     {
//         torque_vec.push_back(torque(i));
//     }

//     matplotlibcpp::figure();
//     matplotlibcpp::plot(torque_vec);
//     matplotlibcpp::grid(true);
//     matplotlibcpp::show();
// }