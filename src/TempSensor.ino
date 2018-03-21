#include "MedianFilter.h"
#include "Temp.h"
#include "AveragingFilter.h"

#define A_SYSTEMTEMP    A0

String deviceId;
const char dataChannel[] = "Sensor/Temperature";

Temp* tempSensor = new Temp(A_SYSTEMTEMP);
MedianFilter* medianFilter = new MedianFilter();
AveragingFilter* averagingFilter = new AveragingFilter();

void ParticlePublishHandler(const char *topic, const char *data) {
    deviceId = String(data);
    Particle.unsubscribe();
}

// setup() runs once, when the device is first turned on.
void setup()
{
  Serial.begin(9600);
  Particle.subscribe("particle/device/name", ParticlePublishHandler);
  Particle.publish("particle/device/name");

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
      String tempString = String(averageMeasurement);
      Particle.publish(dataChannel, deviceId + "," + tempString, PRIVATE);
  }

  Serial.printf("System temp: %3.2fC\n", tempC);
  char buff[50];
  deviceId.toCharArray(buff, 50);
  Serial.printf("%s\n", buff);

  delay(900);
}
