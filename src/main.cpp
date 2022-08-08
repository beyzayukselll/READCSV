#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <vector>

#include "leastsquareid.h"
#include "Data.h"
#include "write.h"
#include "read.h"
#include "sinesweep.h"
#include "torquesignal.h"
#include "frequency.h"
#include "pulse.h"
#include "plot.h"


int main(int argc, char *argv[])
{


    std::cout << "Program is starting ..." << std::endl;
    Read commandSettings;
    Read sineSweepSettings;
    Read leastSquareSettings;
    Read signalBuilderSettings;

    // Read data from file
    Data data;

    LeastSquareID ls;

    Write write;
    
    TorqueSignal torquesignal;

    SineSweep sinesweep;
    Pulse pulse;
    Plot plot;

    while (1)
    {
        std::cout << "reading settings ..." << std::endl;

        const std::string tempFile = "/home/beyza/SytemID/least_square_identification/data/";

        commandSettings.readJson(tempFile + "setting.json", "commandSettings");
        sineSweepSettings.readJson(tempFile + "setting.json", "sineSweepSettings");
        leastSquareSettings.readJson(tempFile + "setting.json", "leastSquareSettings");
        signalBuilderSettings.readJson(tempFile + "setting.json", "signalBuilderSettings");

        std::cout << "Reading data from file ..." << std::endl;
        if (commandSettings.mResult.at(3) == 0 && commandSettings.mResult.at(4) == 1) // frf data
        {
            data.setFile(tempFile + "sineSweept_y_Axis_torqueMode_0To70Hz_2tor_05sample_27062022.csv");
        }
        else if (commandSettings.mResult.at(3) == 1 && commandSettings.mResult.at(4) == 0) // ls data
        {
            data.setFile(tempFile + "leastSquare_y_v5_500interval_24062022.csv");
        }
        else
        {
            std::cout << "Error: Wrong command settings" << std::endl;
            return 0;
        }

        data.dataRead();
        Eigen::VectorXd torque = data.getTorque();
        Eigen::VectorXd velocity = data.getVelocity();
        Eigen::VectorXd time = data.getTime();
        double sampleTime = data.getSampleTime();
        if (commandSettings.mResult.at(0) == 1) // start
        {
            if (commandSettings.mResult.at(1) == 1 && commandSettings.mResult.at(2) == 0) // generate pulse torque
            {
                std::cout << "Generating pulse torque" << std::endl;
                // set signal builder settings
                pulse.setDuration(signalBuilderSettings.mResult.at(0));
                pulse.setMaxTorque(signalBuilderSettings.mResult.at(1));
                pulse.setMinTorque(signalBuilderSettings.mResult.at(2));
                pulse.setPulseNumber(signalBuilderSettings.mResult.at(3));
                pulse.setSampleTime(signalBuilderSettings.mResult.at(4));
                pulse.calculatePulseInput();

                std::cout << "Pulse torque generated" << std::endl;
                // write the parameters to file
                std::cout << "plotting" << std::endl;


                plot.torquePlot(pulse.getTorqueInput());

                std::cout << "plotting done" << std::endl;

                write.write_csv(tempFile + "torqueInput.csv", "Torque Input", pulse.getTorqueInput());
            }

            else if (commandSettings.mResult.at(1) == 0 && commandSettings.mResult.at(2) == 1) // generate sineseep torque
            {
                std::cout << "Generating sine sweep torque" << std::endl;
                sinesweep.setSampleTime(sineSweepSettings.mResult.at(0));
                sinesweep.setTotalTime(sineSweepSettings.mResult.at(1));
                sinesweep.setMinimumFrequency(sineSweepSettings.mResult.at(2));
                sinesweep.setMaximumFrequency(sineSweepSettings.mResult.at(3));
                sinesweep.setTorqueAmplitude(sineSweepSettings.mResult.at(4));
                sinesweep.calculateSineSweepInput();

                std::cout << "Sine sweep torque generated" << std::endl;

                std::cout << "Pulse torque generated" << std::endl;
                // write the parameters to file
                std::cout << "plotting" << std::endl;
                Plot plot;

                plot.torquePlot(sinesweep.getTorqueInput());

                std::cout << "plotting done" << std::endl;

                write.write_csv(tempFile + "torqueInput.csv", "Torque Input", sinesweep.getTorqueInput());
            }
            else
            {
                std::cout << "Error: Wrong command settings" << std::endl;
                return 0;
            }

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // wait for embaded command and logfiles to be ready

            // when done
            if (commandSettings.mResult.at(3) == 1 && commandSettings.mResult.at(4) == 0) // calculate parameters with using least square method
            {
                std::cout << "Calculating parameters with using least square method" << std::endl;
                ls.setDeadBand(leastSquareSettings.mResult.at(0));

                // set least square settings,
                ls.setTorque(torque);
                ls.setVelocity(velocity);
                ls.setSampleTime(sampleTime);
                ls.calculateLeastSquareIdentification();
                const Eigen::VectorXd &myresult = ls.getCalculationResult();

                std::cout << "Parameters calculated" << std::endl;

                write.dataWriteJson(myresult, tempFile + "write.json");
            }
            else if (commandSettings.mResult.at(3) == 0 && commandSettings.mResult.at(4) == 1) // calculate parameters with using frf method
            { 
                std::cout << "Calculating parameters with using frf method" << std::endl;
                //double sampleTime = data.getSampleTime();
                
                Frequency frequency(sampleTime, velocity, torque);

                Eigen::VectorXd frequencyResponseFunction = frequency.getFrequencyResponseFunction();
              
                Eigen::VectorXd frequencySeries = frequency.getFrequencySeries();
                std::cout << "Parameters calculated" << std::endl;

                std::cout << "Frequency response function plotting" << std::endl;

                std::vector<double> frequencyResponseFunctionVector;
                std::vector<double> frequencySeriesVector;
                for (int i = 0; i < frequencyResponseFunction.size(); i++)
                {
                    frequencyResponseFunctionVector.push_back(frequencyResponseFunction(i));
                    frequencySeriesVector.push_back(frequencySeries(i));
                }
               // plot.frfPlot(frequencySeries,frequencyResponseFunction);
            }
            else
            {
                std::cout << "Error: Wrong command settings" << std::endl;
                return 0;
            }

            // Aşağıdaki kodlar eigen::vector ler csv dosyasına yazılamadığı için yapılmıştır.
            std::vector<double> torquee;
            torquee.resize(torque.size());
            std::vector<double> velocityy;
            velocityy.resize(torque.size());
            std::vector<double> times;
            times.resize(torque.size());

            for (int i = 0; i < torque.size(); i++)
            {
                torquee[i] = torque(i);
                velocityy[i] = velocity(i);
                times[i]=time(i);
            }

            std::vector<std::pair<std::string, std::vector<double>>> vals = {{"Time", times},{"Actual Torque", torquee}, {"Actual Velocity", velocityy}};

            write.write_csv_col(tempFile + "ActualValues.csv", vals);
        }

        else if (commandSettings.mResult.at(0) == 0)
        {
            std::cout << "waiting for starting conditions" << std::endl;
        }
        else
        {
            std::cout << "error start" << std::endl;
        }
    }
    return 0;
}
