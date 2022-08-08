#include "Data.h"



void Data::setFile(const std::string & file)
{
    mFile = file;
}


std::string Data::getFile()
{
    return mFile;
}

Eigen::VectorXd Data::getVelocity()
{
    return mVelocity;
}

Eigen::VectorXd Data::getTorque()
{
    return mTorque;
    
}
Eigen::VectorXd Data::getTime()
{
    return time;
}

    double Data::getSampleTime()
{
    return mSampleTime;
}
void Data::dataRead()
{
    std::ifstream is(mFile);
    std::istream_iterator<double> start(is), end;
    std::vector<double> numbers(start, end);
    int num_of_data = numbers.size();
    int num_of_cols = 66;
    int num_of_rows = num_of_data / num_of_cols;
    int initial_value = 0;

    std::vector<std::vector<double>> matrix;
    Eigen::MatrixXd res = Eigen::MatrixXd(num_of_rows, num_of_cols);

    for (int i = 0; i < num_of_data; i++)
    {
        res(i / num_of_cols, i % num_of_cols) = numbers[i];
    }

 

    time = res.col(0);

    mVelocity = res.col(29) / 10000.0 * 2.0 * atan(1)*4.0 / 60.0; // mColOfVel = 29

    mTorque = res.col(11) / 1000.0 * 2.37; // mColOfTor = 11

    mSampleTime = (time(1)-time(0))/1000;
}
