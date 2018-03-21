#include "AveragingFilter.h"

void AveragingFilter::Add(float measurement) {
    measurements[--measurementIndex] = measurement;
    if(measurementIndex == 0)
        measurementIndex = AVERAGECOUNT;
}

float AveragingFilter::GetAverage()
{
    float averageMeasurement = 0;
    for(int i = 0; i<AVERAGECOUNT; i++)
    {
        averageMeasurement += measurements[i] / AVERAGECOUNT;
    }
    return averageMeasurement;
}

int AveragingFilter::Length()
{
    return AVERAGECOUNT;
}

bool AveragingFilter::Full()
{
    if(measurementIndex == AVERAGECOUNT)
        return true;

    return false;
}
