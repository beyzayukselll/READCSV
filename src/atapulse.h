#pragma once
#include <iostream>

class AtaPulse
{
public:

AtaPulse(double amplitude, double duration, int offsetInGroup);
void setAmplitude(double amplitude);
void setDuration(double duration);
void setOffsetInGroup(int offsetInGroup);

double getAmplitude();
double getDuration();
int getOffsetInGroup();

private:
    double mAmplitude;
    double mDuration;
    int mOffsetInGroup; //  zero base index
};
