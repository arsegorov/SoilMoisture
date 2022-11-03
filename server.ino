#include <SPI.h>
#include <WiFiNINA.h>

#include "rgb.h"
#include "time.h"
#include "sensor.h"
#include "server.h"
#include "utils.h"


WiFiServer server(SERVER_PORT);

void server_setup() {
  Serial.print("Starting server on ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.print(SERVER_PORT);
  Serial.print("...");

  server.begin();
  Serial.println("Done\n");
  blink(WHITE, BRIGHT, TENTH, 5);
}


void listen_for_clients(float sensor_val, String local_time) {
  WiFiClient client = server.available();
  if (!client) return;

  blink(WHITE, VERY_DIM, QUARTER, 2);
  Serial.println("New client");

  // an HTTP request ends with a blank line
  boolean currentLineIsBlank = true;
  while (client.connected()) {
    if (!client.available()) {
      continue;
    }

    char c = client.read();
    Serial.write(c);

    // if you've gotten to the end of the line (received a newline
    // character) and the line is blank, the HTTP request has ended,
    // so you can send a reply
    if (c == '\n' && currentLineIsBlank){
      // send a standard HTTP response header
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");  // close the connection after response
      client.println("Refresh: 600\n");  // refresh the page automatically

      client.print("<!DOCTYPE HTML>\n");
      client.print("<html>\n");
      client.print("\t<div style=\"font-family: Consolas, monospace; font-size: 20px;\"'>\n");
      client.print("\t\tLocal date and time: ");
      client.print(local_time);
      client.print("<br />\n");
      client.print("\t\tMoisture sensor reading: ");
      client.println(sensor_val);
      client.print("\t</div>\n");
      client.print("<html>\n");
      break;
    }

    if (c == '\n') {
      // you're starting a new line
      currentLineIsBlank = true;
    } else if (c != '\r') {
      // you've gotten a character on the current line
      currentLineIsBlank = false;
    }
  }

  // give the web browser time to receive the data
  delay_secs(1);

  // close the connection:
  client.stop();
  blink(WHITE, BRIGHT, TENTH, 5);
  Serial.println("Client disconnected\n");
}
