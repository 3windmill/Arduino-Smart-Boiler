#ifdef MqttClient_Enable
      
      /*
       * PROGMEM - DEFINITIONS IN FLASH 
       *
       */
      
      /*keep always the same order in table definition and in Strings Id definition below */
      // CHARACTER RULER                                PROGMEM = "12345678901234567892123456789";
      const char cMQTT_TOPIC_SUBSCRIBE[]                PROGMEM = "Boiler/In/#";
      const char cMQTT_TOPIC_OUT_ALIVE[]                PROGMEM = "Boiler/Out/Alive";
      const char cMQTT_TOPIC_OUT_BOILER_TEMPERATURE[]   PROGMEM = "Boiler/Out/Temp";
      const char cMQTT_TOPIC_OUT_TIME_LEFT[]            PROGMEM = "Boiler/Out/TimeLeft"; 
      const char cMQTT_TOPIC_OUT_Status[]               PROGMEM = "Boiler/Out/Status";
      const char cMQTT_TOPIC_OUT_DESIRED_TEMPERATURE[]  PROGMEM = "Boiler/Out/DesiredTemp";
      const char cMQTT_TOPIC_IN_DESIRED_TEMPERATURE[]   PROGMEM = "Boiler/In/DesiredTemp";
      const char cMQTT_TOPIC_IN_ONOFF[]                 PROGMEM = "Boiler/In/OnOff";
      const char cMQTT_TOPIC_IN_Time[]                  PROGMEM = "Boiler/In/Time";
      const char cMQTT_TOPIC_OUT_STARTED[]              PROGMEM = "STARTED";
      const char cMQTT_CHECKING_STATUS[]                PROGMEM = "CHECKING STATUS...";
      const char cMQTT_CONNECTION_TIMEOUT[]             PROGMEM = "CONNECTION TIMEOUT ";
      const char cMQTT_CONNECTION_LOST[]                PROGMEM = "CONNECTION LOST ";
      const char cMQTT_CONNECT_FAILED[]                 PROGMEM = "NETWORK CONNECTION FAILED ";
      const char cMQTT_DISCONNECTED[]                   PROGMEM = "DISCONNECTED ";
      const char cMQTT_CONNECTED[]                      PROGMEM = "CONNECTED ";
      const char cMQTT_CONNECT_BAD_PROTOCOL[]           PROGMEM = "BAD MQTT PROTOCOL ";
      const char cMQTT_CONNECT_BAD_CLIENT_ID[]          PROGMEM = "BAD CLIENT ID ";
      const char cMQTT_CONNECT_UNAVAILABLE[]            PROGMEM = "SERVER DONT ACCEPTS CONNECTION ";
      const char cMQTT_CONNECT_BAD_CREDENTIALS[]        PROGMEM = "BAD USERNAME/PASWORD ";
      const char cMQTT_CONNECT_UNAUTHORIZED[]           PROGMEM = "CLIENT UNAUTHORIZED ";
      const char cMQTT_SUSCRIBED[]                      PROGMEM = "SUSCRIBED ";
      const char cMQTT_NOT_SUSCRIBED[]                  PROGMEM = "NOT SUSCRIBED ";
      const char cMQTT_CONNECTING[]                     PROGMEM = "CONNECTING..";
      const char cMQTT_STATUS[]                         PROGMEM = "STATUS";
      const char cMQTT_ON_HEATING[]                     PROGMEM = "HEATING";
      const char cMQTT_ON_COOLING[]                     PROGMEM = "COOLING";
      const char cMQTT_OFF[]                            PROGMEM = "STOPPED";
      const char cMQTT_TOPIC_OUT_INTERNAL_TEMPERATURE[] PROGMEM = "Boiler/Out/InternalTemp";
      const char cMQTT_TOPIC_OUT_BOILER_HEAT_CAPACITY[] PROGMEM = "Boiler/Out/HeatCapacity";
      
      
      /* Defining of Strings ID */
      #define ID_MQTT_TOPIC_SUBSCRIBE                     0
      #define ID_MQTT_TOPIC_OUT_ALIVE                     1
      #define ID_MQTT_TOPIC_OUT_BOILER_TEMPERATURE        2
      #define ID_MQTT_TOPIC_OUT_TIME_LEFT                 3
      #define ID_MQTT_TOPIC_OUT_Status                    4
      #define ID_MQTT_TOPIC_OUT_DESIRED_TEMPERATURE       5
      #define ID_MQTT_TOPIC_IN_DESIRED_TEMPERATURE        6
      #define ID_MQTT_TOPIC_IN_ONOFF                      7
      #define ID_MQTT_TOPIC_IN_Time                       8
      #define ID_MQTT_TOPIC_OUT_STARTED                   9
      #define ID_MQTT_CHECKING_STATUS                    10
      #define ID_MQTT_CONNECTION_TIMEOUT                 11
      #define ID_MQTT_CONNECTION_LOST                    12
      #define ID_MQTT_CONNECT_FAILED                     13
      #define ID_MQTT_DISCONNECTED                       14
      #define ID_MQTT_CONNECTED                          15
      #define ID_MQTT_CONNECT_BAD_PROTOCOL               16
      #define ID_MQTT_CONNECT_BAD_CLIENT_ID              17
      #define ID_MQTT_CONNECT_UNAVAILABLE                18
      #define ID_MQTT_CONNECT_BAD_CREDENTIALS            19
      #define ID_MQTT_CONNECT_UNAUTHORIZED               20
      #define ID_MQTT_SUSCRIBED                          21
      #define ID_MQTT_NOT_SUSCRIBED                      22
      #define ID_MQTT_CONNECTING                         23
      #define ID_MQTT_STATUS                             24
      #define ID_MQTT_ON_HEATING                         25
      #define ID_MQTT_ON_COOLING                         26
      #define ID_MQTT_OFF                                27
      #define ID_MQTT_TOPIC_OUT_INTERNAL_TEMPERATURE     28
      #define ID_MQTT_TOPIC_OUT_BOILER_HEAT_CAPACITY     29
      /*Set up a table to refer to your strings and store them in Flash memory.*/
      
      const char* const Mqtt_StringTable[] PROGMEM = { \
      cMQTT_TOPIC_SUBSCRIBE,                cMQTT_TOPIC_OUT_ALIVE,                  cMQTT_TOPIC_OUT_BOILER_TEMPERATURE,\
      cMQTT_TOPIC_OUT_TIME_LEFT,            cMQTT_TOPIC_OUT_Status,                 cMQTT_TOPIC_OUT_DESIRED_TEMPERATURE,\
      cMQTT_TOPIC_IN_DESIRED_TEMPERATURE,   cMQTT_TOPIC_IN_ONOFF,                   cMQTT_TOPIC_IN_Time,\
      cMQTT_TOPIC_OUT_STARTED,              cMQTT_CHECKING_STATUS,                  cMQTT_CONNECTION_TIMEOUT,\
      cMQTT_CONNECTION_LOST,                cMQTT_CONNECT_FAILED,                   cMQTT_DISCONNECTED,\
      cMQTT_CONNECTED,                      cMQTT_CONNECT_BAD_PROTOCOL,             cMQTT_CONNECT_BAD_CLIENT_ID,\ 
      cMQTT_CONNECT_UNAVAILABLE,            cMQTT_CONNECT_BAD_CREDENTIALS,          cMQTT_CONNECT_UNAUTHORIZED,\ 
      cMQTT_SUSCRIBED,                      cMQTT_NOT_SUSCRIBED,                    cMQTT_CONNECTING,\
      cMQTT_STATUS,                         cMQTT_ON_HEATING,                       cMQTT_ON_COOLING,\
      cMQTT_OFF,                            cMQTT_TOPIC_OUT_INTERNAL_TEMPERATURE,   cMQTT_TOPIC_OUT_BOILER_HEAT_CAPACITY\ 
      };
      
      /* Function to retrive strings from flash*/
      String ReadMqttStringFromFlash(byte MqttStringID)
      {
          char mybuffer[32];
          
          strcpy_P(mybuffer, (char*)pgm_read_word(&(Mqtt_StringTable[MqttStringID]))); 
          return String(mybuffer);
      
      }
#endif
