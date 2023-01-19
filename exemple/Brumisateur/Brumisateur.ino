#include <RegulTerra.h>
#include "DHT.h"

#define DHTPIN 0					
#define pin_Relais_Brumisateur 16   

#define DHTTYPE DHT21

DHT dht(DHTPIN, DHTTYPE);
RegulHumi Brumisateur(pin_Relais_Brumisateur);

int consigne = 55;
int hysteresis = 5;

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(5000);
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  
  if (isnan(temp) || isnan(humi)) {
    Serial.println(F("Échec de la lecture du capteur DHT !"));
  }
  
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F(" °C Humidité: "));
  Serial.print(h);
  Serial.println(F(" %"));
    
  Brumisateur.gestion(humi, consigne, hysteresis);
  
}
