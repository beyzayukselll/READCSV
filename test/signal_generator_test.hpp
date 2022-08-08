#pragma once
#include "catch.hpp"
#include "../src/pulse.h"
#include "../src/torquesignal.h"
#include "../src/read.h"

class SignalGeneratorTestFixture
{
public:
    const std::string tempFile = "../../data/";

    std::string SignalProporties[5] = {"maxTorque", "minTorque", "pulseNumber", "duration", "deadBand"};
};

TEST_CASE_METHOD(SignalGeneratorTestFixture, "Setting Signal test", "[Signal Test]")
{
    std::string fileName = tempFile + "setting.json";

    Read signalBuilderSettings;
    signalBuilderSettings.readJson(fileName, "signalBuilderSettings");

    Pulse pulse;
    // set signal builder settings
    pulse.setDuration(signalBuilderSettings.mResult.at(0));
    pulse.setMaxTorque(signalBuilderSettings.mResult.at(1));
    pulse.setMinTorque(signalBuilderSettings.mResult.at(2));
    pulse.setPulseNumber(signalBuilderSettings.mResult.at(3));
    pulse.setSampleTime(signalBuilderSettings.mResult.at(4));
    pulse.calculatePulseInput();

    SECTION("Signal Setting Test")
    {
        REQUIRE(pulse.getDuration() == signalBuilderSettings.mResult.at(0));
        REQUIRE(pulse.getMaxTorque() == signalBuilderSettings.mResult.at(1));
        REQUIRE(pulse.getMinTorque() == signalBuilderSettings.mResult.at(2));
        REQUIRE(pulse.getPulseNumber() == signalBuilderSettings.mResult.at(3));
        REQUIRE(pulse.getSampleTime() == signalBuilderSettings.mResult.at(4));   
    }

        CHECK(pulse.getTorqueInput().size() > 0);

        Eigen::VectorXd absTorqueInput;
        Eigen::VectorXd torqueInput = pulse.getTorqueInput();
        absTorqueInput.resize(torqueInput.size());

        THEN("Min Torque Test ")
        {
            for (int i = 0; i < pulse.getTorqueInput().size(); i++)
            {

                if (torqueInput(i) > 0)
                {
                    continue;   
                    torqueInput(i) = absTorqueInput(i);
                    CHECK(absTorqueInput.minCoeff() == signalBuilderSettings.mResult.at(2));
                }
            }
        }
        THEN("Max Torque Test")
        {
            CHECK(torqueInput.maxCoeff() == signalBuilderSettings.mResult.at(1));
        }
    
}


TEST_CASE_METHOD(SignalGeneratorTestFixture, "signalgeneratortest", "[signal generator test]")
{

    double maxTorque = 30.0;
    double minTorque = 10.0;
    double duration = 5.0;
    int pulseNumber = 3;

    Pulse p(maxTorque, minTorque, duration, pulseNumber);
    Eigen::VectorXd torqueInput = p.getTorqueInput();
    std::vector<double> torqueInputVector;

    for (int i = 0; i < torqueInput.size(); i++)
    {
        torqueInputVector.push_back(torqueInput(i));
    }

    double testset[59] = {0, 10, 10, 10, 10, 0, -10, -10, -10, -10, 0, 20, 20, 20, 20, 0, -20, -20, -20, -20, 0, 30, 30, 30, 30, 0, -30, -30, -30, 0, 30, 30, 30, 0, -30, -30, -30, -30, 0, 20, 20, 20, 20, 0, -20, -20, -20, -20, 0, 10, 10, 10, 10, 0, -10, -10, -10, -10, 0};
    for (int i = 0; i < 3; i++)
    {
        REQUIRE(torqueInputVector[i] == testset[i]);
    }
}