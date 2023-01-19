#include <RegulTerra.h>                     // On importe la librairie RegulTerra https://github.com/weedmanu/RegulTerra

#define pin_Flotteur 2			                // pin du Flotteur  ( GPIO 2  : D4 )
#define pin_Buzzer  15			                // pin du Buzzer    ( GPIO 15 : D8 ) 
 
Niveau Flotteur(pin_Flotteur);              // On crée l'objet Flotteur sur le modèle Niveau
Alarme Buzzer(pin_Buzzer);		              // On crée l'objet Buzzer sur le modèle Alarme

void setup() {
  Serial.begin(115200);                     // On démarre la com série
}

void loop() {
  delay(5000);                              // Toutes les 5 secondes
  if (Flotteur.verif()) {                   // Si la fonction verif() de l'objet Flotteur retourne 1
	  Serial.println("Niveau: bon");          // On informe dans la com série que le niveau d'eau est bon 
  } else {                                  // Sinon (la fonction verif() de l'objet Flotteur retourne 0)
	Serial.println("Niveau: insuffisant");    // On informe dans la com série que le niveau d'eau est insufissant
	Buzzer.Alerte_Sonore();                   // On lance la fonction Alerte_Sonore() de l'objet Buzzer
  } 
}
