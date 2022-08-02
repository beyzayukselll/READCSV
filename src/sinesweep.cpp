#include "sinesweep.h"

void SineSweep::setMinimumFrequency(double minimumFrequency)
{
    mMinimumFrequency = minimumFrequency;
}

void SineSweep::setMaximumFrequency(double maximumFrequency)
{
    mMaximumFrequency = maximumFrequency;
}

void SineSweep::setTorqueAmplitude(double torqueAmplitude)
{
    mTorqueAmplitude = torqueAmplitude;
}

double SineSweep::getMinimumFrequency()
{
    return mMinimumFrequency;
}

double SineSweep::getMaximumFrequency()
{
    return mMaximumFrequency;
}

double SineSweep::getTorqueAmplitude()
{
    return mTorqueAmplitude;
}

Eigen::VectorXd SineSweep::calculateSineSweepInput()
{

    double sampleTime = getSampleTime();
    double totalTime = getTotalTime();
    Eigen::VectorXd sineSweepInput;
    sineSweepInput.resize(totalTime/sampleTime);

    for (int i = 1; i < sineSweepInput.size(); i ++)
    {
        double time = i * sampleTime;
        sineSweepInput(i) = mTorqueAmplitude*(sin(2*atan(1)*4*(mMinimumFrequency*time+(mMaximumFrequency-mMinimumFrequency)/(2*totalTime)*time*time)));
    }
    setTorqueInput(sineSweepInput);
    //std::cout << sineSweepInput << std::endl;
}


void SineSweep::plotTorqueInput()
{
    Eigen::VectorXd torqueInput = getTorqueInput();
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
    matplotlibcpp::plot(time,x);
    matplotlibcpp::xlabel("Time [s]");
    matplotlibcpp::ylabel("Torque [Nm]");
    matplotlibcpp::grid(true);
    matplotlibcpp::title("Trajectory");
    matplotlibcpp::show();

}