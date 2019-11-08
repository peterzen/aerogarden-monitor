#include <ESP8266WiFi.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "ThingsBoard.h"



void networkSetup(){
  WiFiManager wifiManager;
  wifiManager.autoConnect("IOT");
  Serial.println("");
  Serial.println("WiFi connection");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Use WiFiClient class to create TCP connections
WiFiClient client;
ThingsBoard tb(client);

#define TOKEN               "pKVAnaW8IXKHUWWDHfZs"
#define THINGSBOARD_SERVER  "10.10.11.8"


void sendData(float temperature_indoor, float humidity_indoor, uint16_t lux, int water_level){

  if (!tb.connected()) {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  Serial.println("Sending data...");


  // Uploads new telemetry to ThingsBoard using MQTT. 
  // See https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api 
  // for more details

  tb.sendTelemetryFloat("temperature_indoor", temperature_indoor);
  tb.sendTelemetryFloat("humidity_indoor", humidity_indoor);
  tb.sendTelemetryInt("water_level", water_level);
  tb.sendTelemetryInt("light", lux);

  tb.loop();

}
