#define BLYNK_TEMPLATE_ID "TMPL36Mvych4x"
#define BLYNK_TEMPLATE_NAME "Irragiation system"
#define BLYNK_AUTH_TOKEN "VXqxUFdGKv_RbpFlTdKkpqRQNVTbOD7E"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN; // the auth code that you got on your gmail
char ssid[] = "Andy Dufresne"; // your Wi-Fi SSID
char pass[] = "sana@001"; // your Wi-Fi password

#define SOIL_MOISTURE_PIN A0
#define RELAY_PIN 5

int moistureLevel = 0;
int threshold = 300; // Adjust this value based on your soil moisture sensor

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Ensure the relay is off at the beginning

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  moistureLevel = analogRead(SOIL_MOISTURE_PIN);
  Serial.print("Soil Moisture Level: ");
  Serial.println(moistureLevel);

  if (moistureLevel < threshold) {
    digitalWrite(RELAY_PIN, LOW); // Turn on the water pump
    Serial.println("Pump Started, Watering the plants");
    //Blynk.notify("Pump Started, Watering the plants");
  } 
  else {
    digitalWrite(RELAY_PIN, HIGH); // Turn off the water pump
    Serial.println("Pump Stopped, Soil Moisture is sufficient");
  }

  Blynk.virtualWrite(V1, moistureLevel); // Send soil moisture level to Blynk app
  delay(1000); // Adjust the delay as needed
}
