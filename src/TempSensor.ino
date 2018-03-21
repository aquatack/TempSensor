#include "MedianFilter.h"
#include "Temp.h"

#define A_SYSTEMTEMP    A0

double tempC = -999.0;
String deviceId;
const int AVERAGECOUNT = 60;
int reportCountIndex;
float measurements[AVERAGECOUNT];
const char dataChannel[] = "Sensor/Temperature";

Temp* tempSensor = new Temp(A_SYSTEMTEMP);
MedianFilter* medianFilter = new MedianFilter();

void ParticlePublishHandler(const char *topic, const char *data) {
    deviceId = String(data);
    Particle.unsubscribe();
}

// setup() runs once, when the device is first turned on.
void setup() {

  Serial.begin(9600);
  Particle.subscribe("particle/device/name", ParticlePublishHandler);
  Particle.publish("particle/device/name");
  reportCountIndex = AVERAGECOUNT;

  // Initialise the median filter.
  delay(100);
  medianFilter->Initialise(tempSensor->getTempDegC());
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  delay(100); // allow the ADC to settle.
  tempC = tempSensor->getTempDegC();
  measurements[--reportCountIndex] = medianFilter->Filter(tempC);
  Serial.printf("::loop: tempC: %5.2f, medianValue: %5.2f\n", tempC, measurements[reportCountIndex]);

  if(reportCountIndex <=0 )
  {
      float averageMeasurement = 0;
      reportCountIndex = AVERAGECOUNT;
      for(int i = 0; i<reportCountIndex; i++)
      {
          averageMeasurement += measurements[i] / reportCountIndex;
      }
      Serial.printf("::loop.publish: averageMeasurement: %f5.2\n", averageMeasurement);
      String tempString = String(averageMeasurement);
      Particle.publish(dataChannel, deviceId + "," + tempString, PRIVATE);
  }

  Serial.printf("System temp: %3.2fC\n", tempC);
  char buff[50];
  deviceId.toCharArray(buff, 50);
  Serial.printf("%s\n", buff);

  delay(900);
}
