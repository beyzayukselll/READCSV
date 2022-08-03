#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <matplotlibcpp.h>
#include <complex>
#include <cmath>
#include "leastsquareid.h"
#include "Data.h"
#include <vector>
#include "write.h"
#include "read.h"
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "sinesweep.h"
#include "torquesignal.h"
#include "frequency.h"
#include "pulse.h"

int main()
{
    std::cout << "Program is starting ..." << std::endl;

    Read commandSettings;
    Read frequencySettings;
    Read leastSquareSettings;
    Read signalBuilderSettings;

    commandSettings.readJson("../../data/setting.json", "commandSettings");
    frequencySettings.readJson("../../data/setting.json", "frequencySettings");
    leastSquareSettings.readJson("../../data/setting.json", "leastSquareSettings");
    signalBuilderSettings.readJson("../../data/setting.json", "signalBuilderSettings");

    // Read data from file
    Data data;
    if (commandSettings.result[4] == 0 && commandSettings.result[5] == 1)
    {
        data.setFile("../../data/y_Axis_ImpulseTest_23torq_27062022.csv");
    }
    else if (commandSettings.result[4] == 1 && commandSettings.result[5] == 0)
    {
        data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
    }
    else
    {
        std::cout << "Error: Wrong command settings" << std::endl;
        return 0;
    }
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();

    // yukarıdaki kodları tek satırda yapmak mantıklımıdır. Constructer kullanımı ile ilgili yorumlarınızı merak ediyoruz.

    LeastSquareID ls;
    Frequency fr;

    Write write;

    SineSweep sinesweep;
    TorqueSignal torquesignal;
    while (1)
    {
        if (commandSettings.result[3] == 1) // start
        {
            if (commandSettings.result[1] == 1 && commandSettings.result[2] == 0) // generate pulse torque
            {
                Pulse pulse;
                // set signal builder settings
                pulse.setDuration(signalBuilderSettings.result[0]);
                pulse.setMaxTorque(signalBuilderSettings.result[1]);
                pulse.setMinTorque(signalBuilderSettings.result[2]);
                pulse.setPulseNumber(signalBuilderSettings.result[3]);
                pulse.setSampleTime(signalBuilderSettings.result[4]);
                pulse.calculatePulseInput();

                  std::cout << "gecti" << std::endl;
                // write the parameters to file
                write.write_csv("../../data/torqueInput.csv", "Torque Input", pulse.getTorqueInput());
            }

            else if (commandSettings.result[1] == 0 && commandSettings.result[2] == 1) // generate sineseep torque
            {
                sinesweep.setSampleTime(frequencySettings.result[0]);
                sinesweep.setTotalTime(frequencySettings.result[1]);
                sinesweep.setMinimumFrequency(frequencySettings.result[2]);
                sinesweep.setMaximumFrequency(frequencySettings.result[3]);
                sinesweep.setTorqueAmplitude(frequencySettings.result[4]);
                sinesweep.calculateSineSweepInput();

                write.write_csv("../../data/torqueInput.csv", "Torque Input", sinesweep.getTorqueInput());
            }
            else
            {
                std::cout << "Error: Wrong command settings" << std::endl;
                return 0;
            }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // wait for embaded command and logfiles to be ready

            // when done
            if (commandSettings.result[4] == 1 && commandSettings.result[5] == 0) // calculate parameters with using least square method
            {
                ls.setDeadBand(leastSquareSettings.result[0]);

                // set least square settings
                ls.calculateLeastSquareIdentification();
                const Eigen::VectorXd &myresult = ls.getCalculationResult();
                write.dataWriteJson(myresult, "../../data/write.json");
            }
            else if (commandSettings.result[4] == 0 && commandSettings.result[5] == 1) // calculate parameters with using frf method
            {
                fr.setSampleTime(0.001);
                fr.setVelocity(velocity);
                fr.setTorque(torque);
                fr.calculateFrequencyResponseFunction();
                fr.calculateFrequencySeries();
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

            for (int i = 0; i < torque.size(); i++)
            {
                torquee[i] = torque(i);
                velocityy[i] = velocity(i);
            }

            std::vector<std::pair<std::string, std::vector<double>>> vals = {{"Actual Torque", torquee}, {"Actual Velocity", velocityy}};

            write.write_csv_col("../../data/ActualValues.csv", vals);
        }

        else if (commandSettings.result[3] == 0)
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