#include "LeastSquareID.h"

LeastSquareID::LeastSquareID(Eigen::VectorXd torque, Eigen::VectorXd velocity)
{
    Torque = torque;
    Velocity = velocity;
}

void LeastSquareID::setTorque(Eigen::VectorXd torque)
{
    Torque = torque;
}

void LeastSquareID::setVelocity(Eigen::VectorXd velocity)
{
    Velocity = velocity;
}

Eigen::VectorXd LeastSquareID::getTorque()
{
    return Torque;
}

Eigen::VectorXd LeastSquareID::getVelocity()
{
    return Velocity;
}

void LeastSquareID::leastSquareIdentification()
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

void LeastSquareID::getInfo()
{
    std::cout << "inertia : " << Inertia << std::endl;
    std::cout << "viscousDamping : " << ViscousDamping << std::endl;
    std::cout << "coulombTorquePositive : " << CoulombTorquePositive << std::endl;
    std::cout << "coulombTorqueNegative : " << CoulombTorqueNegative << std::endl;
}