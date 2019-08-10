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

While testing over serial, it seems the voltage supplied by 2 AA NiMH batteries is not enough, and the reads from the DHT11 either fail or return 0.

Different battery options will be explored.

A program was made to post the current temperature and humidity to a local server, which logs the data to a file. This is next to be tested, along with the deep sleep mode to monitor current usage while sleeping and starting up.

### Testing with 18650 Cells.

Testing with 18650 cells gave a huge improvement to life and stability. While testing, I am yet to use up the charge of 2 18650s.

These are somewhat large, so some ~3.7v nominal AA-size Li-ion batteries would be good to test.

Deep sleep, and posting readings to a python server were both tested successfully, although some stability issues were experienced.
These have been solved by adding a relatively large (470uF) capacitor across Vcc and GND of the ESP. This fixes most problems.

A voltage divider circuit was used to step the battery voltage down to a readable range (0-1v) for the ESP's ADC. This allows monitoring of the battery voltage, and this will allow the ESP to stay in deep sleep mode once the batteries run low, and hopefully they can be replaced before any damage is caused by the very low current while in sleep.

This also seems to have fixed issues reading signals reliably.

While in operation, the system draws 200-500mA. In deep sleep this drops to ~20uA. This could potentially be improved with a LDO linear regulator. The use of a proper circuit board will improve efficiency and stability too, once the project leaves experimental phase.
