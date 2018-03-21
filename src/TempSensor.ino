#include "MedianFilter.h"
#include "Temp.h"
#include "AveragingFilter.h"
#include "ParticleCloud.h"

#define A_SYSTEMTEMP    A0

Temp* tempSensor = new Temp(A_SYSTEMTEMP);
MedianFilter* medianFilter = new MedianFilter();
AveragingFilter* averagingFilter = new AveragingFilter();

// setup() runs once, when the device is first turned on.
void setup()
{
  Serial.begin(9600);
  ParticleCloud::GetDeviceName();

  // Initialise the median filter.
  delay(100);
  medianFilter->Initialise(tempSensor->getTempDegC());
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  delay(100); // allow the ADC to settle.
  float tempC = tempSensor->getTempDegC();
  float medianValue = medianFilter->Filter(tempC);
  averagingFilter->Add(medianValue);
  Serial.printf("::loop: tempC: %5.2f, medianValue: %5.2f\n", tempC, medianValue);

  if(averagingFilter->Full())
  {
      float averageMeasurement = averagingFilter->GetAverage();
      Serial.printf("::loop.publish: averageMeasurement: %5.2f\n", averageMeasurement);
      ParticleCloud::PublishTemperature(averageMeasurement);
  }

  delay(900);
}
