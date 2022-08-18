#include "plot.h"

void Plot::logPlot(Eigen::VectorXd position, Eigen::VectorXd velocity, Eigen::VectorXd acc, double sampleTime)
{

    std::vector<double> pos_vec;
    std::vector<double> vec_vec;
    std::vector<double> acc_vec;
    std::vector<double> time_vec;

    for (int i = 0; i < position.size(); i++)
    {
        pos_vec.push_back(position(i));
        vec_vec.push_back(velocity(i));
        acc_vec.push_back(acc(i));
        time_vec.push_back(i * sampleTime);
    }

    matplotlibcpp::figure();

    matplotlibcpp::plot(time_vec, pos_vec, "r");
    matplotlibcpp::plot(time_vec, vec_vec, "b");
    matplotlibcpp::plot(time_vec, acc_vec, "g");
    matplotlibcpp::xlabel("Time [ms]");
    matplotlibcpp::ylabel("amplitude");
    matplotlibcpp::title("Test Log");
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