# wifi-data-logger

ESP-12 based wifi-enabled data logger experiments.

## Contents

1. Experiments & Testing.

## 1. Experiments & Testing

### NiMH Battery Operation.

The ESP8266 runs fine using 2 AA NiMH batteries when fully charged. The 'HelloServer' script did not start properly when using low-charge batteries, a threshold of around 2.5v is needed.

Running the HelloServer script using fully charged AA batteries, the server ran from for a total of ~270 mins. Logging every 30 mins, with an uptime of ~30 seconds this would give around 11 days of battery life without accounting for sleep current. This is not much, but further experiments will be made.

The voltage dropped to 2.7v within approximately an hour. This reflects the discharge pattern of NiMH batteries.

The server became unstable and unable to reboot at 2.5v. This must be the minimum voltage for operation. It may be worth experimenting with LiFePO4 batteries. These Have a max voltage of ~3.6v and maintain ~3v while discharging.

### Data Logging.

For the final logger, a DHT22 temperature/humidity sensor will be used, since it has a larger operating range including freezing temperatures.

While testing, a DHT11 was used, since I already had one. This may affect current draw while logging somewhat, so this should be considered.

A program was made to post the current 
