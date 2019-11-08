

#include "DHTesp.h"

// DHT Settings
#define DHT_INDOOR_PIN 2      // indoor DHT sensor pin
#define DHTTYPE DHT21         // DHT 21 (AM2301)

// LEDs
#define LOW_WATER_LED 13
#define STATUS_LED    2

// Update every 30 seconds = 0,5 minutes. Min with Thingspeak is ~20 seconds
const int UPDATE_INTERVAL_SECONDS = 60;

DHTesp dht_indoor;


// BH1750 light sensor
#include <Wire.h>
#include <BH1750FVI.h>

// Settings
uint8_t ADDRESSPIN = 13;
BH1750FVI::eDeviceAddress_t DEVICEADDRESS = BH1750FVI::k_DevAddress_H;
BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;

// Create the Lightsensor instance
BH1750FVI LightSensor(ADDRESSPIN, DEVICEADDRESS, DEVICEMODE);


// Water level sensor

const int TANK_FULL = 560;
const int TANK_LOW = 60;

int depthSensor = 0; //Set depthSensor input pin to Analog 0.
int lastWaterLevel = 0;

void LEDOn(){
    digitalWrite(STATUS_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void LEDOff(){
  digitalWrite(STATUS_LED, LOW);   // turn the LED on (HIGH is the voltage level)  
}

void setup() {
  Serial.begin(115200);
  delay(10);

  networkSetup();

//  dht_outdoor.setup(DHT_OUTDOOR_PIN, DHTesp::DHT22);
  dht_indoor.setup(DHT_INDOOR_PIN, DHTesp::DHT22);

  LightSensor.begin();  

  // initialize LEDs
  pinMode(STATUS_LED, OUTPUT);
  pinMode(LOW_WATER_LED, OUTPUT);
}

void loop() {      

    LEDOn();

    uint16_t lux = LightSensor.GetLightIntensity();
 
    float humidity_indoor = dht_indoor.getHumidity();
    float temperature_indoor = dht_indoor.getTemperature();

    if (isnan(humidity_indoor) || isnan(temperature_indoor)) {
      Serial.println("Can't receive data from indoor DHT");
      delay(1000);
      return;
    }

    int water_level = analogRead(depthSensor); // Read the sensor values.

    if(water_level <= TANK_LOW){
      digitalWrite(LOW_WATER_LED, HIGH);
    } else {
      digitalWrite(LOW_WATER_LED, LOW);
    }
    
    sendData(temperature_indoor, humidity_indoor, lux, water_level);
    
    Serial.print("Indoor temp: ");
    Serial.print(temperature_indoor);
    Serial.print("C Indoor humidity: "); 
    Serial.print(humidity_indoor);
    Serial.print("% "); 
    
    Serial.print("Water level: ");
    Serial.print(water_level);
    Serial.print(" ");

    Serial.print("Light: ");
    Serial.print(lux);
    Serial.print(" lux");
    Serial.println();

    LEDOff();

    delay(1000 * UPDATE_INTERVAL_SECONDS);
}
