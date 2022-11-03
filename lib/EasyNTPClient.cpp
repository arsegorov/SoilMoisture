/*
  EasyNTPClient - Arduino library to read time from Network Time Protocol (NTP) servers.
  Created by Harsha Alva, June 29, 2017.
  Released into the public domain.

  Based on work by:
  * Francesco Potortì, 2013
  * https://playground.arduino.cc/Code/NTPclient
  * 
  * Sandeep Mistry, 2016
  * https://github.com/arduino-libraries/NTPClient
*/

// #pragma once
#include "Arduino.h"
#include "EasyNTPClient.h"

EasyNTPClient::EasyNTPClient (UDP &udp) {
  this->mUdp = &udp;
}

EasyNTPClient::EasyNTPClient (UDP &udp, const char* serverPool) {
  this->mUdp = &udp;
  this->mServerPool = serverPool;
}

EasyNTPClient::EasyNTPClient (UDP &udp, const char* serverPool, int offset) {
  this->mUdp = &udp;
  this->mServerPool = serverPool;
  this->mOffset = offset;
}

int EasyNTPClient::getTimeOffset() {
  return this->mOffset;
}

void EasyNTPClient::setTimeOffset (int offset) {
  this->mOffset = offset;
}


boolean EasyNTPClient::sendRequest () {
    // Only the first four bytes of an outgoing NTP packet need to be set
    const long NTP_FIRST_4_BYTES = 0xEC0600E3;

    // open socket on arbitrary port
    static int udpInited = this->mUdp->begin(123);
    if (!udpInited) {
      // Serial.println("ERROR - NTP: Couldn't get UDP initialized");
      return false;
    }

    // Clear received data from possible stray received packets
    this->mUdp->flush();

    // Send an NTP request
    if (!(
      this->mUdp->beginPacket(this->mServerPool, 123) // 123 is the NTP port
      && this->mUdp->write((byte *) & NTP_FIRST_4_BYTES, 48) == 48
      && this->mUdp->endPacket()
    )) {
      // Serial.println("ERROR - NTP: Couldn't send UDP request");
      return false;
    }

    // Serial.println("INFO - NTP: request sent");
    return true;
}


unsigned long EasyNTPClient::getServerTime () {
    const unsigned long POLL_INTERVAL = 125UL;
    const byte MAX_POLLS = 16;
    int pktLen;

    // Wait for response
    for (byte i = 0; i < MAX_POLLS; i++) {
      pktLen = this->mUdp->parsePacket();
      if (pktLen == 48) { break; }

      // Serial.print("INFO - NTP: current packet length ");
      // Serial.println(pktLen);
      delay(POLL_INTERVAL);
    }
    if (pktLen != 48) {
      // Serial.println("ERROR - NTP: No correct packet received");
      return 0;
    }

    // Read and discard the first useless bytes
    // Set useless to 32 for speed; set to 40 for accuracy.
    const byte useless = 40;
    for (byte i = 0; i < useless; ++i) {
      this->mUdp->read();
    }

    // Read the integer part of sending time
    unsigned long time = this->mUdp->read();  // NTP time
    for (byte i = 1; i < 4; i++) {
      time = time << 8 | this->mUdp->read();
    }

    // Serial.print("INFO - NTP: server time received: ");
    // Serial.println(time - 2208988800ul);

    // Round to the nearest second if we want accuracy.
    // The fractional part is the next byte divided by 256,
    //  if it is > 500 ms, we round to the next second;
    //  we also account for an assumed network delay of 50 ms
    //    (0.5 - 0.05) * 256 = 115;
    //  additionally, we account for how much we delayed reading the packet
    //  since its arrival, which we assume on average to be POLL_INTERVAL/2.
    time += (this->mUdp->read() > 115 - 256UL*POLL_INTERVAL/2UL/1000UL);

    // Serial.print("INFO - NTP: server time adjusted for delays: ");
    // Serial.println(time - 2208988800ul);

    // Discard the rest of the packet
    this->mUdp->flush();

    return time + this->mOffset - 2208988800ul;   // convert NTP time to Unix time
}

unsigned long EasyNTPClient::getUnixTime() {
  unsigned long delta = millis() - this->mLastUpdate;

  if (this->mServerTime <= 0UL || this->mLastUpdate == 0UL || delta >= this->mUpdateInterval) {
    // Count the successful sent requests
    this->requestsSent += this->sendRequest();

    if (this->requestsSent) {
      // Serial.println("INFO - NTP: waiting for response...");
      this->mServerTime = this->getServerTime();

      // Decrease the count for each valid response
      if (this->mServerTime > 0UL) {  // The response is valid
        this->requestsSent--;

        while (this->requestsSent) {
          // Serial.println("INFO - NTP: another request pending. Waiting for another response...");
          if(this->getServerTime() > 0UL) {
            this->requestsSent--;
          }
        }
      }

      this->mLastUpdate = millis();
    }
  }
  return this->mServerTime + ((millis() - this->mLastUpdate) / 1000);
}
