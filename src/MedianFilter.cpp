#include <Particle.h>
#include "MedianFilter.h"

void MedianFilter::Initialise(float initTemp)
{
    for(int i=0; i<filterDepth; i++)
    {
        Filter(initTemp);
    }
}

int MedianFilter::cmpfunc(const void *first, const void *second)
{
    return (*(int*)first - *(int*)second); // cast to ints. We only want sign out of this.
}

float MedianFilter::Filter(float nextValue)
{
    elements[filterIndexer] = nextValue;
    filterIndexer = (filterIndexer + 1) % 5;
    memcpy(filteredElements, elements, sizeof(float)*filterDepth);

    qsort(filteredElements, filterDepth, sizeof(float), cmpfunc);
    for(int i = 0; i < 5; i++)
    {
        Serial.printf("elements: %5.2f, filteredElements %5.2f\n", elements[i], filteredElements[i]);
    }
    float filteredValue = filteredElements[filterDepth / 2];
    Serial.printf("::medianFilter: Input Value: %5.2f, filterIndexer: %d, output value: %5.2f\n", nextValue, filterIndexer, filteredValue);
    return filteredValue;
}
