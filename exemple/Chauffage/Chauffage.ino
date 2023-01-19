#include <RegulTerra.h>
#include "DHT.h"

#define DHTPIN 0
#define pin_Relais_Chauffage 14
#define pin_Buzzer 15

#define DHTTYPE DHT21

DHT dht(DHTPIN, DHTTYPE);
RegulTemp chauffage(pin_Relais_Chauffage);
Alarme Buzzer(pin_Buzzer);

int consigne = 20;
float hysteresis = 0.25;
int tempMax = 23;
int tempMin = 17;

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
  
  chauffage.gestion(temp, consigne, hysteresis);
  if (Buzzer.Alerte_Temp(TempC, TempMin, TempMax) == 0) { 
        Serial.println("Alerte temp min !!!"); 
        Buzzer.Alerte_Sonore();
      } else if (Buzzer.Alerte_Temp(TempC, TempMin, TempMax) == 2) { 
        Serial.println("Alerte temp max !!!"); 
        Buzzer.Alerte_Sonore();
      } else { 
        Serial.println("Température OK"); 
      }
  }  
}
