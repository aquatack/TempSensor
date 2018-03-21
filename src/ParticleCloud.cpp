#include <Particle.h>
#include "ParticleCloud.h"

String ParticleCloud::deviceId;

void ParticleCloud::NamePublishHandler(const char *topic, const char *data)
{
    ParticleCloud::deviceId = String(data);
    Particle.unsubscribe();
}

void ParticleCloud::GetDeviceName()
{
    Particle.subscribe("particle/device/name", ParticleCloud::NamePublishHandler);
    Particle.publish("particle/device/name");
}

void ParticleCloud::PublishTemperature(float temperature)
{
    String tempString = String(temperature);
    String messageString = ParticleCloud::deviceId + "," + tempString;
    char buff[50];
    messageString.toCharArray(buff,50);
    Serial.printf("ParticleCloud::PublishTemperature: %s\n",buff);
    Particle.publish(DATACHANNEL, messageString, PRIVATE);
}
