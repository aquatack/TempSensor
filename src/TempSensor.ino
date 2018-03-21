#include "MedianFilter.h"

#define A_SYSTEMTEMP    A0

double tempC = -999.0;
String deviceId;
const int AVERAGECOUNT = 60;
int reportCountIndex;
float measurements[AVERAGECOUNT];

MedianFilter* medianFilter = new MedianFilter();

float getTempDegC(int adcInput)
{
    const float offset_mV = 500.0;
    const float scale_mV_degC = 10.0;
    const float valPermV = 0.8; // 4096 steps between 0 and 3.3V

    float mVOut = adcInput * valPermV;

    // mVOut = offset_mV + T * scale_mV_degC
    // (mVOut - offset_mV)/scale_mV_degC

    float temperature = (mVOut - offset_mV) / scale_mV_degC;
    return temperature;
}

void handler(const char *topic, const char *data) {
    deviceId = String(data);
    Particle.unsubscribe();
}

// setup() runs once, when the device is first turned on.
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Particle.subscribe("particle/device/name", handler);
  Particle.publish("particle/device/name");
  reportCountIndex = AVERAGECOUNT;

  // Initialise the median filter.
  delay(100);
  medianFilter->Initialise(getTempDegC(analogRead(A_SYSTEMTEMP)));
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  delay(100); // allow the ADC to settle.
  tempC = getTempDegC(analogRead(A_SYSTEMTEMP));
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
      Particle.publish("Sensor/Temperature", deviceId + "," + tempString, PRIVATE);
  }

  Serial.printf("System temp: %3.2fC\n", tempC);
  char buff[50];
  deviceId.toCharArray(buff, 50);
  Serial.printf("%s\n", buff);

  delay(900);
}
