# TempSensor

A basic temperature sensor project for the [Particle Photon](https://docs.particle.io/guide/getting-started/intro/photon/) board.

## Features
 - Measures temperature (in Degrees C) using a [TMP36](http://www.analog.com/en/products/analog-to-digital-converters/integrated-special-purpose-converters/digital-temperature-sensors/tmp36.html#product-overview) analogue temperature sensor
 - Measurements taken every second and averaged:
     - Median filtering applied over the last five measurements
     - Averaging applied over a one minute rolling window
 - Publishes the measured temperature to the Particle cloud once a minute
 - Published messages include the user controlled (as set in the [Particle admin console](https://console.particle.io/devices)) sensor name. This allows users to control the name and have consumers adjust accordingly without recompiling.

## Published message syntax
- Channel: `Sensor/Temperature`
- Data: `[DeviceId],[Temp]`
    - `[DeviceId]` is the user specified name of the Particle device.
    - `[Temp]` is a float in degrees C
