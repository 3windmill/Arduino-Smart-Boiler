#ifdef Hardware_Enable
      
      boolean BoilerHeating=false;
      boolean BoilerCooling=false;
      boolean BoilerOFF=false;

     
      byte  BoilerRelayOnOff=0;
      const int BoilerRelayPin = 3;
      
      void HardwareInit()
      {
          BoilerRelayInit();

      }

      void BoilerRelayInit()
      {
           pinMode(BoilerRelayPin, OUTPUT); 
      }
     

void Boiler_Relay_OnOff(){
    
    if ((BoilerRelayOnOff == 1) && (DeviceSensor[1].Temperature <= (BoilerDesiredTemperature - BoilerDifferentialTemperature)))
    {
        digitalWrite(BoilerRelayPin, LOW);
        BoilerHeating=true;
        BoilerCooling=false;
        BoilerOFF=false;
    }
    
    if ((BoilerRelayOnOff == 1) && (DeviceSensor[1].Temperature >= (BoilerDesiredTemperature + BoilerDifferentialTemperature)))
    {
         digitalWrite(BoilerRelayPin, HIGH);
         BoilerCooling=true;
         BoilerHeating=false;
         BoilerOFF=false;
    }
     if (BoilerRelayOnOff == 0)
   {
        digitalWrite(BoilerRelayPin, HIGH);
        BoilerOFF=true;
        BoilerHeating=false;
        BoilerCooling=false;
        
   }   

  
}


#endif


