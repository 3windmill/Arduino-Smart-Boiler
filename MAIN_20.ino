
#include  "Definitions.h"

void setup() {

     wdt_enable(WDTO_4S);
     
     StartEtherenet();
    
     #ifdef Serial_Debug_Enable 
           SerialDebugStart();
     #endif
    
     #ifdef Hardware_Enable
          HardwareInit();
    #endif
   
      
    #ifdef Ds18B20_Enable
        Ds18b20Init();
    #endif
     
    #ifdef MqttClient_Enable
        MqttCheckConnection();
    #endif
    
    #ifdef WebServer_Enable
        WebServerInit();
   #endif
 
  wdt_reset();
}

void loop() {

#ifdef Ds18B20_Enable
       Ds18b20_Running();
#endif
 
Boiler_Relay_OnOff();
 
#ifdef MqttClient_Enable
    MqttKeepRunning();
#endif

#ifdef WebServer_Enable
    WebServerRunning();
#endif

// #ifdef Hardware_Enable
//    HardwareRunning();
// #endif
 
#ifdef Memory_Debug
   SerialDebugMemoryUsage();
#endif

wdt_reset();

}


