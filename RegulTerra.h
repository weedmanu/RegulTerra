#ifndef REGULTERRA_H
#define REGULTERRA_H

#include <Arduino.h>

class Eclairage { 
  private:
    int8_t pin_Relais_Eclairage;
  public:    	
    Eclairage(int8_t pin_Relais_Eclairage);      
    bool gestion(int8_t Maintenant_H, int8_t Maintenant_M, int8_t Lever_H, int8_t Lever_M, int8_t Coucher_H, int8_t Coucher_M); 
};

class RegulTemp { 
  private:
    int8_t pin_Relais_Chauffage; 
  public:    
    RegulTemp(int8_t pin_Relais_Chauffage);      
    bool gestion(float value_Temp, int8_t target_Temp, float Hys_Temp);    
};

class RegulHumi { 
  private:
    int8_t pin_Relais_Brumisateur;
  public:  
    RegulHumi(int8_t pin_Relais_Brumisateur);      
    bool gestion(float value_Humi, int8_t target_Humi, int8_t Hys_Humi); 
};

class Niveau { 
  private:
    int8_t pin_Flotteur;
  public:  		
    Niveau(int8_t pin_Flotteur);      
    bool verif(); 
};

class Alarme { 
  private:
    int8_t pin_Buzzer;
    const int NOTE_G4 = 392;
    const int NOTE_AS4 = 466;
  public:  
	Alarme(int8_t pin_Buzzer);      
	void beep(int note, int duree); 
    void Alerte_Sonore(); 
    int8_t Alerte_Temp(float value_Temp, int8_t TempMin, int8_t TempMax);
};

#endif
