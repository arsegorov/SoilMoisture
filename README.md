# Automated Plant Watering System

An Arduino UNO WiFi Rev. 2 project

## Purpose
Monitoring a planter soil moisture levels and watering it when necessary

## Requirements
1. Arduino UNO WiFi Rev. 2
1. An Arduino development environment. For an IDE, Arduino IDE or VS Code (which also needs Arduino IDE < 2.0 for the executables) works, but Arduino CLI should also work.
1. The following Arduino libraries:
   * Time
   * Timezone
   * WiFiNINA
   * EasyNTPClient
1. A moisture sensor
1. An immersible water pump with a hose

## Code Deployment
1. Put the root folder where your Arduino IDE is looking for the projects (by default, in `~/Documents/Arduino/`).
1. Install the required libraries using the IDE's Library Manager. After the **EasyNTPClient** library is installed, replace the `.h` and `.cpp` library files with the ones from this repo's `lib/` folder.
1. Put your secrets, such as `SECRET_SSID` and `SECRET_PASSWORD`, in `secrets.h`, but don't commit the file to the repo to prevent security issues.
1. Update the code to your local timezone by changing the `TimeChangeRule` items in `time.h` and the `local_tz` assignment in `time.ino/time_setup()`.
1. Upload to Arduino

## Physical assembly
1. Connect the sensor's wires to Arduino, directly or using a breadboard:
   * the ground wire to a `GND` pin
   * the power wire to the digital pin 2
   * the signal wire to the analog pin A0
   > **Note**  
   >  Before using the device on your plants, you may want to run Arduino in this state with
   >  the sensor dry, and then stuck in 100% water-saturated soil, to calibrate the
   >  `DRY_READING` and `SATURATED_READING` values in `sensor.h`. When calibrating
   >  `SATURATED_READING`, let the sensor itself absorb as much moisture as it will take
   >  before updating the value.
   * stick the sensor into the planter soil
1. Connect the pump's wires:
   * the ground wire to a `GND` pin
   * the power wire to the digital pin 4
1. Immerse the pump into a water reservoir and prime it
   * You may connect and disconnect its power wire to / from the 5V pin a few times until the pump reliably pumps a strong stream
1. Connect the hose and put the open end of the hose over the planter
