# Aerogarden monitor

Arduino sketch that monitors an [Aerogarden](https://www.aerogarden.com/).  It captures temperature, humidity, light intensity and the water tank level, and sends the data to [Thingsboard](https://thingsboard.io/) using MQTT.

Sensors:
  * DHT21 (AM2301) temperature/humidity
  * BH1750 light sensor
  * [Water level sensor](https://www.makershop.de/sensoren/feuchtigkeit/wasser-fuellstand-sensor/)
  
It runs on a NodeMCU v3 (ESP8266 12E) board.

Measurements are taken once every minute.

### Dependencies:

 * ArduinoJSON
 * WiFiManager
 * ThingsBoard

