namespace ParticleCloud
{
    const char DATACHANNEL[] = "Sensor/Temperature";
    extern String deviceId;
    void NamePublishHandler(const char *topic, const char *data);
    void GetDeviceName();
    void PublishTemperature(float temperature);
};
