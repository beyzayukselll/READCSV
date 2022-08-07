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
        frequencySeries_vec.push_back(frequencySeries(i));
    }

    std::vector<double> frf_vec_logaritmic;
    std::vector<double> frequencySeries_vec_logaritmic;

    for (int i = 0; i < frf.size(); i++)
    {
        frf_vec_logaritmic.push_back(20.0*log10(frf(i)));
        frequencySeries_vec_logaritmic.push_back(log10(frequencySeries(i)));
    }


    matplotlibcpp::figure();
    matplotlibcpp::plot(frequencySeries_vec, frf_vec);
    matplotlibcpp::grid(true);
    matplotlibcpp::show();
}