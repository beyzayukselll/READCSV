#include "signal.h"


void Signal::setTorqueInput()
{
    totalTime = 4 * pulseNumber * duration;
    torqueInput.resize(totalTime);

    for (int i = 0; i < totalTime; ++i)
    {
            torqueInput(i)=0;
    }


    for (int t = 0; t < totalTime; ++t)
    {
        for (int i = 0; i < pulseNumber; ++i)
        {
            if (t > (2*i ) * duration && t < (2*i+1) * duration)
            {
                torqueInput(t) = (i) * (maxTorque - minTorque) / (pulseNumber - 1) + minTorque;
            }
            else if (t > (2 *i + 1) * duration && t < 2 * (i+1) * duration)
            {
                torqueInput(t) = -(i) * (maxTorque - minTorque) / (pulseNumber - 1) - minTorque;
            }
        }
    }
    std::vector<double> temp;
    temp.resize(totalTime);

    for (int i = 0; i < totalTime; ++i)
    {
        temp.push_back(torqueInput(i));
    }

    std::reverse (temp.begin(), temp.end());
    
    for (int i = 0; i < totalTime; ++i)
    {
        temp[i] = temp[i]*-1;
    }
    
    Eigen::VectorXd temp1;
    temp1.resize(totalTime);
    for (int i = 0; i < totalTime; ++i)
    {
        temp1(i) = temp[i];
    }

    torqueInput.tail((totalTime/2)+1) = temp1.tail((totalTime/2)+1);

}

Eigen::VectorXd Signal::getTorqueInput()
{
    return torqueInput;
}

void Signal::plotTorqueInput()
{
    std::vector<double> x;
    x.resize(torqueInput.size());
    for (int i = 0; i < torqueInput.size(); i++)
    {
        x[i] = torqueInput(i);
    }
    std::vector<double> time;
    time.resize(torqueInput.size());
    for (int i = 0; i < torqueInput.size(); i++)
    {
        time[i] = i;
    }
    matplotlibcpp::figure();
    matplotlibcpp::plot(x);
    matplotlibcpp::xlabel("Time [s]");
    matplotlibcpp::ylabel("Torque [Nm]");
    matplotlibcpp::grid(true);
    matplotlibcpp::title("Trajectory");
    matplotlibcpp::show();
}