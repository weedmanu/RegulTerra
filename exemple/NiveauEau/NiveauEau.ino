#include <RegulTerra.h>         // On importe la librairie RegulTerra

#define pin_Flotteur 2			// D4 pin du Flotteur
#define pin_Buzzer 15			// D8 pin du Buzzer

Niveau Flotteur(pin_Flotteur);  // On crée l'objet Flotteur
Alarme Buzzer(pin_Buzzer);		// On crée l'objet Buzzer

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(5000);
  if (Flotteur.verif()) { 
	  Serial.println("Niveau OK"); 
  } else { 
	Serial.println("Niveau KO"); 
	Buzzer.Alerte_Sonore();
  } 
}
