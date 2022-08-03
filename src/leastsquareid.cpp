#include "leastsquareid.h"

void LeastSquareID::setDeadBand(const double & deadBand)
{
    mDeadBand = deadBand;
}

void LeastSquareID::setTorque(const Eigen::VectorXd & torque)
{
    mTorque = torque;
}

void LeastSquareID::setVelocity(const Eigen::VectorXd & velocity)
{
    mVelocity = velocity;
}

void LeastSquareID::setSampleTime(const double & sampleTime)
{
    mSampleTime = sampleTime;
}


double LeastSquareID::getDeadBand()
{
    return mDeadBand;
}

Eigen::VectorXd LeastSquareID::getTorque()
{
    return mTorque;
}

Eigen::VectorXd LeastSquareID::getVelocity()
{
    return mVelocity;
}

double LeastSquareID::getSampleTime()
{
    return mSampleTime;
}


void LeastSquareID::calculateLeastSquareIdentification()
{
    int num_of_rows = mTorque.size();
    Eigen::VectorXd signum;
    signum.setZero(mTorque.size());

    Eigen::VectorXd positiveVelociy;
    positiveVelociy.resize(mTorque.size());
    Eigen::VectorXd negativeVelociy;
    negativeVelociy.resize(mTorque.size());

    for (int i = 0; i < mTorque.size(); i++)
    {
        if (mVelocity(i) <= mDeadBand && mVelocity(i) >= -1.0 * mDeadBand)
        {
            signum(i) = 0;
        }
        else if (mVelocity(i) > mDeadBand)
        {
            signum(i) = 1;
        }
        else if (mVelocity(i) < mDeadBand)
        {
            signum(i) = -1;
        }
        positiveVelociy(i) = 1.0 / 2.0 * signum(i) * (1.0 + signum(i));
        negativeVelociy(i) = -1.0 / 2.0 * signum(i) * (1.0 - signum(i));
    }

    Eigen::VectorXd outputVector;
    outputVector.resize(mTorque.size());
    outputVector = mVelocity.tail(num_of_rows - 1);

    Eigen::MatrixXd regresserMatrix;
    regresserMatrix.resize(num_of_rows - 1, 4);
    regresserMatrix.col(0) = mVelocity.head(num_of_rows - 1);
    regresserMatrix.col(1) = mTorque.head(num_of_rows - 1);
    regresserMatrix.col(2) = -1.0 * positiveVelociy.head(num_of_rows - 1);
    regresserMatrix.col(3) = -1.0 * negativeVelociy.head(num_of_rows - 1);

    Eigen::VectorXd estimatedState;
    estimatedState.resize(4);

    estimatedState = (regresserMatrix.adjoint() * regresserMatrix).inverse() * regresserMatrix.adjoint() * (outputVector);

    double p_wd = estimatedState(0);
    double p_w = log(p_wd) / mSampleTime;
    double K_wd = estimatedState(1);
    double K_w = K_wd * (-1.0 * p_w) / (1.0 - exp(p_w * mSampleTime));

    mCalculationResult.resize(4);

    mCalculationResult(0) = mInertia = 1 / K_w;
    mCalculationResult(1) = mViscousDamping = -1.0 * mInertia * p_w;
    mCalculationResult(2) = mCoulombTorquePositive = estimatedState(2) / K_wd;
    mCalculationResult(3) = mCoulombTorqueNegative = estimatedState(3) / K_wd;
}

void LeastSquareID::getInfo()
{
    std::cout << "inertia : " << mInertia << std::endl;
    std::cout << "viscousDamping : " << mViscousDamping << std::endl;
    std::cout << "coulombTorquePositive : " << mCoulombTorquePositive << std::endl;
    std::cout << "coulombTorqueNegative : " << mCoulombTorqueNegative << std::endl;
}

const Eigen::VectorXd & LeastSquareID::getCalculationResult() const
{
    return mCalculationResult;
}