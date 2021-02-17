#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <SPI.h>


#include <Ethernet.h>

#include "MainStrings.h"

#define Ds18B20_Enable
#define Ethernet_Enable
#define Hardware_Enable
#define MqttClient_Enable
//#define Serial_Debug_Enable
#define WebServer_Enable


#ifdef Ds18B20_Enable
     #include "DS18B20Strings.h"
#endif

#ifdef MqttClient_Enable
    #include <PubSubClient.h>
    #include "MqttClientStrings.h"
#endif

#ifdef WebServer_Enable
    #include "WebServerStrings.h"
#endif

#ifdef Serial_Debug_Enable
    
    /****** RAM MEMORY ******/
    //#define Memory_Debug
  
    /********* Mqtt DEBUG ****************/
    #ifdef MqttClient_Enable
      //#define MqttCheckConnection_Debug
      //#define MqttCallback_Debug
      //#define MqttClientHanldeIncomming_Debug
      //#define MqttKeepRunning_Debug
      //#define MqttPublishData_Debug
    #endif
    
    /********  DS18B20 DEBUG *********/
    #ifdef Ds18B20_Enable
        #define Ds18B20_Debug
    #endif


#endif


