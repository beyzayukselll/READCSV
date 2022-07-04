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

class leastSquare
{
private:
    double Inertia;
    double ViscousDamping;
    double CoulombTorquePositive;
    double CoulombTorqueNegative;

public:
    Eigen::VectorXd Torque;
    Eigen::VectorXd Velocity;
    void leastSquareIdentification()
    {

        double deadBand = 0.7;
        int num_of_rows = Torque.size();
        Eigen::VectorXd signum;
        signum.setZero(Torque.size());

        Eigen::VectorXd positiveVelociy;
        positiveVelociy.resize(Torque.size());
        Eigen::VectorXd negativeVelociy;
        negativeVelociy.resize(Torque.size());

        for (int i = 0; i < Torque.size(); i++)
        {
            if (Velocity(i) <= deadBand && Velocity(i) >= -deadBand)
            {
                signum(i) = 0;
            }
            else if (Velocity(i) > deadBand)
            {
                signum(i) = 1;
            }
            else if (Velocity(i) < deadBand)
            {
                signum(i) = -1;
            }
            positiveVelociy(i) = 1.0 / 2.0 * signum(i) * (1.0 + signum(i));
            negativeVelociy(i) = -1.0 / 2.0 * signum(i) * (1.0 - signum(i));
        }

        Eigen::VectorXd outputVector;
        outputVector.resize(Torque.size());
        outputVector = Velocity.tail(num_of_rows - 1);

        Eigen::MatrixXd regresserMatrix;
        regresserMatrix.resize(num_of_rows - 1, 4);
        regresserMatrix.col(0) = Velocity.head(num_of_rows - 1);
        regresserMatrix.col(1) = Torque.head(num_of_rows - 1);
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

        Inertia = 1 / K_w;
        ViscousDamping = -1.0 * Inertia * p_w;
        CoulombTorquePositive = estimatedState(2) / K_wd;
        CoulombTorqueNegative = estimatedState(3) / K_wd;
    }
    void getInfo()
    {

        std::cout << "inertia : " << Inertia << std::endl;
        std::cout << "viscousDamping : " << ViscousDamping << std::endl;
        std::cout << "coulombTorquePositive : " << CoulombTorquePositive << std::endl;
        std::cout << "coulombTorqueNegative : " << CoulombTorqueNegative << std::endl;
    }
};

class Data
{
public:
    std::string File;
    Eigen::VectorXd Velocity;
    Eigen::VectorXd Torque;
    void dataRead()
    {

        std::ifstream is(File);
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

        
        Velocity = res.col(29) / 10000.0 * 5.0 / 60.0;

        Torque = res.col(11) / 1000.0 * 2.37;
    }

    Eigen::VectorXd getTorque()
    {
        return Torque;
    }
    Eigen::VectorXd getVelocity()
    {
        return Velocity;
    }
};

int main()
{
    Data data;
    data.File = "/home/kose/programming/least_square_identification/leastSquare_y_v5_500interval_24062022.csv";
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    leastSquare ls;
    ls.Torque = torque;
    ls.Velocity = velocity;
    ls.leastSquareIdentification();
    ls.getInfo();

    return 0;
}