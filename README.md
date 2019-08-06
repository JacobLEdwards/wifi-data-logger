# wifi-data-logger

ESP-12 based wifi-enabled data logger experiments.

## Contents

1. Experiments & Testing.

## 1. Experiments & Testing

### Battery Operation.

The ESP8266 runs fine using 2 AA batteries when fully charged. The 'HelloServer' script did not start properly when using low-charge batteries, a threshold of around 2.5v is needed.

Running the HelloServer script using fully charged AA batteries, the server ran from for a total of `<PENDING RESULTS>`.

The voltage dropped to 2.7v within approximately an hour. This reflects the discharge pattern of NiMH batteries.

### Data Logging.

For the final logger, a DHT22 temperature/humidity sensor will be used, since it has a larger operating range including freezing temperatures.

While testing, a DHT11 was used, since I already had one. This may affect current draw while logging somewhat, so this should be considered.

