#include <RegulTerra.h>                         // On importe la librairie RegulTerra https://github.com/weedmanu/RegulTerra
#include "DHT.h"                                // On importe la librairie DHT        https://github.com/adafruit/DHT-sensor-library

#define DHTPIN 0                                // On défini le pin de la sonde ( GPIO 0  : D3 )
#define pin_Relais_Brumisateur 16               // On défini le pin du relais   ( GPIO 16 : D0 )

#define DHTTYPE DHT21                           // On défini le type de sonde DHT (11, 21 ou 22)

DHT dht(DHTPIN, DHTTYPE);                       // On crée l'objet dht sur le modèle DHT
RegulHumi Brumisateur(pin_Relais_Brumisateur);  // On crée l'objet Brumisateur sur le modèle RegulHumi
  
int consigne = 55;                              // On définie une consigne d'humidité
int hysteresis = 5;                             // On définie une hystérésis 

void setup() {
  Serial.begin(115200);                         // On démarre la com série
  dht.begin();                                  // On initialise la sonde DHT
}

void loop() {
  delay(5000);                                  // Toutes les 5 secondes
  float humi = dht.readHumidity();              // On récupère l'humidité
  float temp = dht.readTemperature();           // On récupère la température
  
  if (isnan(temp) || isnan(humi)) {                                 // Si la lecture échoue
    Serial.println(F("Échec de la lecture du capteur DHT !"));      // On informe dans la com série
  }
  
  Serial.print(F("Temperature: "));                                 // On affiche les datas dans la com série
  Serial.print(temp);
  Serial.print(F(" °C Humidité: "));
  Serial.print(humi);
  Serial.println(F(" %"));
    
  if (Brumisateur.gestion(humi, consigne, hysteresis)) {            // Si la fonction gestion() de l'objet Brumisateur retourne 1
     Serial.println("Brumisateur activé");                          // On informe dans la com série que le Brumisateur est activé.                                                               // Elle régule la température autour de la consigne + ou - l'hystérésis
  } else {                                                          // Sinon (la fonction gestion() de l'objet Chauffage retourne 0)
      Serial.println("Brumisateur désactivé");                      // On informe dans la com série que le Brumisateur est désactivé. 
  }  
}
