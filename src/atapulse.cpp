#include "atapulse.h"

AtaPulse::AtaPulse(double amplitude, double duration, int offsetInGroup)
: mAmplitude(amplitude), mDuration(duration), mOffsetInGroup(offsetInGroup)
{
}

void AtaPulse::setAmplitude(double amplitude)
{
    mAmplitude = amplitude;
}
void AtaPulse::setDuration(double duration)
{
    mDuration = duration;
}
void AtaPulse::setOffsetInGroup(int offsetInGroup)
{
    mOffsetInGroup = offsetInGroup;
}
double AtaPulse::getAmplitude()
{
    return mAmplitude;
}
double AtaPulse::getDuration()
{
    return mDuration;
}
int AtaPulse::getOffsetInGroup()
{
    return mOffsetInGroup;
}

