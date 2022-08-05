#include "plot.h"

void Plot::torquePlot(const Eigen::VectorXd & torque)
{
    std::vector<double> torque_vec;

    for (int i = 0; i < torque.size(); i++)
    {
        torque_vec.push_back(torque(i));
    }

    matplotlibcpp::figure();
    matplotlibcpp::plot(torque_vec);
    matplotlibcpp::grid(true);
    matplotlibcpp::show();
}

void Plot::frfPlot(const Eigen::VectorXd & frequencySeries, const Eigen::VectorXd & frf)
{
    std::vector<double> frf_vec;
    std::vector<double> frequencySeries_vec;
    for (int i = 0; i < frf.size(); i++)
    {
        frf_vec.push_back(frf(i));
    }
    for (int i = 0; i < frequencySeries.size(); i++)
    {
        frequencySeries_vec.push_back(frequencySeries(i));
    }
    matplotlibcpp::figure();
    matplotlibcpp::plot(frf_vec, frequencySeries_vec);
    matplotlibcpp::grid(true);
    matplotlibcpp::show();
}