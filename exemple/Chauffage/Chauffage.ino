/*
 * Régule la température autour d'une consigne + ou - un hystérésis.
 * Alerte sonnore si la température dépasse le seuil max ou min en cas de pb.
 */

#include <RegulTerra.h>                     // On importe la librairie RegulTerra https://github.com/weedmanu/RegulTerra
#include "DHT.h"                            // On importe la librairie DHT        https://github.com/adafruit/DHT-sensor-library

#define DHTPIN 0                            // On défini le pin de la sonde ( GPIO 0  : D3 )
#define pin_Relais_Chauffage 14             // On défini le pin du relais   ( GPIO 14 : D5 )
#define pin_Buzzer 15                       // On défini le pin du buzzer   ( GPIO 18 : D8 )

#define DHTTYPE DHT21                       // On défini le type de sonde DHT (11, 21 ou 22)

DHT dht(DHTPIN, DHTTYPE);                   // On crée l'objet dht sur le modèle DHT.
RegulTemp Chauffage(pin_Relais_Chauffage);  // On crée l'objet Chauffage sur le modèle RegulTemp.
Alarme Buzzer(pin_Buzzer);                  // On crée l'objet Buzzer sur le modèle Alarme.

int consigne = 25;                          // On définie une consigne de température       
float hysteresis = 0.25;                    // On définie une hystérésis
int tempMax = 30;                           // On définie une température Maxi
int tempMin = 20;                           // On définie une température Mini

void setup() {
  Serial.begin(115200);                     // On démarre la com série
  dht.begin();                              // On initialise la sonde DHT
}

void loop() {
  delay(5000);                              // Toutes les 5 secondes
  float humi = dht.readHumidity();          // On récupère l'humidité
  float temp = dht.readTemperature();       // On récupère la température
  
  if (isnan(temp) || isnan(humi)) {                                 // Si la lecture échoue
    Serial.println(F("Échec de la lecture du capteur DHT !"));      // On informe dans la com série
  }
  
  Serial.print(F("Temperature: "));                                 // On affiche les datas dans la com série
  Serial.print(temp);
  Serial.print(F(" °C Humidité: "));
  Serial.print(humi);
  Serial.println(F(" %"));
  Serial.print(F("consigne: "));                                    
  Serial.print(consigne);
  Serial.print(F(" °C + ou - "));                                    
  Serial.print(hysteresis); 
  Serial.print(F(" °C tempMin: "));
  Serial.print(tempMin);
  Serial.print(F(" °C tempMax: "));
  Serial.print(tempMax);
  Serial.println(F(" °C"));
  
  if (Chauffage.gestion(temp, consigne, hysteresis)) {              // Si la fonction gestion() de l'objet Chauffage retourne 1
     Serial.println("Chauffage activé");                            // On informe dans la com série que le chauffage est activé.                                                               // Elle régule la température autour de la consigne + ou - l'hystérésis
  } else {                                                          // Sinon (la fonction gestion() de l'objet Chauffage retourne 0)
      Serial.println("Chauffage désactivé");                        // On informe dans la com série que le chauffage est désactivé. 
  }
  
  if (Buzzer.Alerte_Temp(temp, tempMin, tempMax) == 1) {            // Si la fonction Alerte_Temp() de l'objet Buzzer retourne 1
    Serial.println("Température OK");                               // On informe dans la com série que la température est ok.
  } else {                                                          // Sinon (la fonction Alerte_Temp() de l'objet Buzzer retourne 0 ou 2)
    Buzzer.Alerte_Sonore();                                         // On lance la fonction Alerte_Sonore() de l'objet Buzzer  
    if (Buzzer.Alerte_Temp(temp, tempMin, tempMax) == 0) {          // Si la fonction Alerte_Temp() de l'objet Buzzer retourne 0
      Serial.println("Alerte temp min !!!");                        // On informe dans la com série qu'il fait trop froid
    } else if (Buzzer.Alerte_Temp(temp, tempMin, tempMax) == 2) {   // Et si la fonction Alerte_Temp() de l'objet Buzzer retourne 2
      Serial.println("Alerte temp max !!!");                        // On informe dans la com série qu'il fait trop chaud    
    }
  }
}  
