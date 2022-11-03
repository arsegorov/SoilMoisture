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

## Deployment
1. Put the root folder where your Arduino IDE is looking for the projects (by default, in `~/Documents/Arduino/`).
1. Install the required libraries using the IDE's Library Manager. After the **EasyNTPClient** library is installed, replace the `.h` and `.cpp` library files with the ones from this repo's `lib/` folder.
1. Put your secrets, such as `SECRET_SSID` and `SECRET_PASSWORD`, in `secrets.h`, but don't commit the file to the repo to prevent security issues.
1. Update the code to your local timezone by changing the `TimeChangeRule` items in `time.h` and the `local_tz` assignment in `time.ino/time_setup()`.
