#include <SPI.h>
#include <WiFiNINA.h>

#include "rgb.h"
#include "wifi.h"
#include "secrets.h"


void print_wifi_status() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println();
}


boolean wifi_setup() {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("ERROR - WiFi setup: Communication with WiFi module failed");
    return false;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("WARN - WiFi setup: Please upgrade the firmware");
    Serial.println();
  }

  char ssid[] = SECRET_SSID;
  char pass[] = SECRET_PASS;

  int status = WL_IDLE_STATUS;

  while (status != WL_CONNECTED) {
    Serial.print("INFO - WiFi setup: Attempting to connect to SSID: ");
    Serial.println(ssid);
    Serial.println();

    status = WiFi.begin(ssid, pass);
    blink(BLUE, REALLY_DIM, HALF, 3);
  }

  Serial.println("Connected!");
  blink(BLUE, BRIGHT, TENTH, 5);

  print_wifi_status();
  return true;
}
