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
#include "signal.h"
#include "read.h"
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "sinesweep.h"
#include "torquesignal.h"

int main()
{
    std::cout << "Program is starting ..." << std::endl;

    // Read data from file
    Data data;
    data.setFile("../../data/leastSquare_y_v5_500interval_24062022.csv");
    data.dataRead();
    Eigen::VectorXd torque = data.getTorque();
    Eigen::VectorXd velocity = data.getVelocity();
    // yukarıdaki kodları tek satırda yapmak mantıklımıdır. Constructer kullanımı ile ilgili yorumlarınızı merak ediyoruz.

    // Data frequencyData;
    // frequencyData.setFile("../../data/y_Axis_ImpulseTest_23torq_27062022.csv");
    // frequencyData.dataRead();
    // Eigen::VectorXd torque = frequencyData.getTorque();
    // Eigen::VectorXd velocity = frequencyData.getVelocity();


    LeastSquareID ls;

    Read commandSettings;
    Read frequencySettings;
    Read leastSquareSettings;
    Read signalBuilderSettings;

    Write write;

    SineSweep sinesweep;
    TorqueSignal torquesignal;  

     frequencySettings.readJson("../../data/setting.json", "frequencySettings");
     sinesweep.setSampleTime(frequencySettings.result[0]);
     sinesweep.setTotalTime(frequencySettings.result[1]);
     sinesweep.setMinimumFrequency(frequencySettings.result[2]);
     sinesweep.setMaximumFrequency(frequencySettings.result[3]);
     sinesweep.setTorqueAmplitude(frequencySettings.result[4]);
     sinesweep.calculateSineSweepInput();
     
    while (1)
    {
        commandSettings.readJson("../../data/setting.json", "commandSettings");
        leastSquareSettings.readJson("../../data/setting.json", "leastSquareSettings");
        signalBuilderSettings.readJson("../../data/setting.json", "signalBuilderSettings");

        
        if (commandSettings.result[2] == 1)
         {

           
             if (commandSettings.result[1] == 1)
            {
                Signal signal;
                // set signal builder settings
                signal.maxTorque = signalBuilderSettings.result[0];
                signal.minTorque = signalBuilderSettings.result[1];
                signal.pulseNumber = signalBuilderSettings.result[2];
                signal.duration = signalBuilderSettings.result[3];
                signal.setTorquePulse();

                // write the parameters to file
                write.write_csv("../../data/torqueInput.csv", "Torque Input", signal.torqueInput);

                if (commandSettings.result[0] == 1)
                {
                    signal.plotTorqueInput();
                    sinesweep.plotTorqueInput();
                }
            }

            else 
            write.write_csv("../../data/torqueInput.csv", "Torque Input", sinesweep.getTorqueInput());


            // wait for embaded command and logfiles to be ready

            // when done
            if (commandSettings.result[3] == 1)
            {
                leastSquareSettings.readJson("../../data/setting.json", "leastSquareSettings");
                ls.deadBand = leastSquareSettings.result[0];

                // set least square settings
                ls.calculateLeastSquareIdentification(torque, velocity, ls.deadBand);
                const Eigen::VectorXd &myresult = ls.getCalculationResult();
                write.dataWriteJson(myresult, "../../data/write.json");
            }

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

        else if (commandSettings.result[1] == 0)
        {
            
            std::cout << "waiting for starting conditions" << std::endl;
        }
        else
        {
            std::cout << "error" << std::endl;
        }
    }
    return 0;
}