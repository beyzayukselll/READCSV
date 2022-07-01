#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/FFT>
#include <matplotlibcpp.h>
#include <iterator>
#include <vector>
#include <complex>
#include <cmath>
#include <Eigen/SVD>

void leastSquareIdentification(Eigen::VectorXd &torque, Eigen::VectorXd &velocity)
{
    double deadBand = 0.7;
    int num_of_rows = torque.size();
    Eigen::VectorXd signum;
    signum.setZero(torque.size());

    Eigen::VectorXd positiveVelociy;
    positiveVelociy.resize(torque.size());
    Eigen::VectorXd negativeVelociy;
    negativeVelociy.resize(torque.size());

    for (int i = 0; i < torque.size(); i++)
    {
        if (velocity(i) <= deadBand && velocity(i) >= -deadBand)
        {
            signum(i) = 0;
        }
        else if (velocity(i) > deadBand)
        {
            signum(i) = 1;
        }
        else if (velocity(i) < deadBand)
        {
            signum(i) = -1;
        }
        positiveVelociy(i) = 1.0 / 2.0 * signum(i) * (1.0 + signum(i));
        negativeVelociy(i) = -1.0 / 2.0 * signum(i) * (1.0 - signum(i));
    }

    Eigen::VectorXd outputVector;
    outputVector.resize(torque.size());
    outputVector = velocity.tail(num_of_rows - 1);

    Eigen::MatrixXd regresserMatrix;
    regresserMatrix.resize(num_of_rows - 1, 4);
    regresserMatrix.col(0) = velocity.head(num_of_rows - 1);
    regresserMatrix.col(1) = torque.head(num_of_rows - 1);
    regresserMatrix.col(2) = -1.0 * positiveVelociy.head(num_of_rows - 1);
    regresserMatrix.col(3) = -1.0 * negativeVelociy.head(num_of_rows - 1);

    Eigen::VectorXd estimatedState;
    estimatedState.resize(4);

    estimatedState = (regresserMatrix.adjoint() * regresserMatrix).inverse() * regresserMatrix.adjoint() * (outputVector);

    double sampleTime = 0.001;
    double p_wd = estimatedState(0);
    double p_w = log(p_wd) / sampleTime;
    double K_wd = estimatedState(1);
    double K_w = K_wd * (-1.0 * p_w) / (1.0 - exp(p_w * sampleTime));

    double inertia = 1 / K_w;
    double viscousDamping = -1.0 * inertia * p_w;
    double coulombTorquePositive = estimatedState(2) / K_wd;
    double coulombTorqueNegative = estimatedState(3) / K_wd;

    std::cout << "inertia : " << inertia << std::endl;
    std::cout << "viscousDamping : " << viscousDamping << std::endl;
    std::cout << "coulombTorquePositive : " << coulombTorquePositive << std::endl;
    std::cout << "coulombTorqueNegative : " << coulombTorqueNegative << std::endl;
};

int main()
{
    std::ifstream is("/home/bcd/programming/least_square_identification/leastSquare_y_v5_500interval_24062022.csv");
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

    Eigen::VectorXd time;
    time = res.col(0);

    Eigen::VectorXd velocity;
    velocity = res.col(29) / 10000.0 * 5.0 / 60.0;

    Eigen::VectorXd torque;
    torque = res.col(11) / 1000.0 * 2.37;

    std::vector<double> time_vec;
    std::vector<double> velocity_vec;
    std::vector<double> torque_vec;

    for (int i = 0; i < num_of_rows; i++)
    {
        time_vec.push_back(time(i));
        velocity_vec.push_back(velocity(i));
        torque_vec.push_back(torque(i));
    }

    leastSquareIdentification(torque, velocity);

    return 0;
}