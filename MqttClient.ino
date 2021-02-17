#ifdef MqttClient_Enable
  
    IPAddress MqttServerIP(192, 168, 1,10 );
    EthernetClient EthernetForMqttClient;

   char* chrClientId="SMARTBOILER_v1";
   char* chrUserName="ymis";
   char* chrPassword="1234";
    
    boolean HeatingPublished =false;
    boolean CoolingPublished =false;
    boolean OffPublished =false;

    #define IntervalForPublishTimeLeft 5000 
    float PreviousTimeForPublishTimeLeft=0;

    
    void callback(char* topic, byte* payload, unsigned int length) {
          
          String MqttInCommingData="";
          boolean MqttHasInCommingData_Flag = false;
                
          #ifdef MqttCallback_Debug
              SerialDebugPrint("MqttCallback_Debug");
              SerialDebugPrint("MqttHasInCommingData_Flag");
              SerialDebugPrint(String(MqttHasInCommingData_Flag));
              SerialDebugPrint("Payload");
              SerialDebugPrint(payload);
              SerialDebugPrint("Length");
              SerialDebugPrint(String(length));
          #endif
    
          if(length>0)
          {
              MqttHasInCommingData_Flag=true;
              MqttInCommingData=String(topic) +"#";
              MqttInCommingData.trim();
         
              for (int i=0;i<length;i++) 
              {
              
                  MqttInCommingData=MqttInCommingData + String((char)payload[i]);
              }
          
              #ifdef MqttCallback_Debug
                  SerialDebugPrint(MqttInCommingData);
                  SerialDebugPrint("MqttHasInCommingData_Flag");
                  SerialDebugPrint(String(MqttHasInCommingData_Flag)); 
              #endif
          
              MqttClientHandleIncomming(MqttInCommingData, MqttHasInCommingData_Flag);//,"",false);
          }
          
          
    }

    PubSubClient MqttClient(MqttServerIP, 1883, callback, EthernetForMqttClient);

    void MqttCheckConnection() { 
         char MqttTopic[30];
         int TopicLength;
         
         TopicLength=ReadMqttStringFromFlash(ID_MQTT_TOPIC_SUBSCRIBE).length();
         ReadMqttStringFromFlash(ID_MQTT_TOPIC_SUBSCRIBE).toCharArray( MqttTopic,TopicLength+1); 
        
              
        #ifdef MqttCheckConnection_Debug
              SerialDebugPrint("MqttCheckConnection_Debug");
              SerialDebugPrint(ReadMqttStringFromFlash(ID_MQTT_CHECKING_STATUS)); 
              SerialDebugPrint(CheckMqttClientStatus(MqttClient.state()));
        #endif
         
        if(!MqttClient.connected())
        {
                                
                  #ifdef MqttCheckConnection_Debug
                          
                         SerialDebugPrint(ReadMqttStringFromFlash(ID_MQTT_CONNECTING));
                  #endif
            
                  if (MqttClient.connect(chrClientId, chrUserName, chrPassword))
                  {
                         #ifdef MqttCheckConnection_Debug
                                SerialDebugPrint(CheckMqttClientStatus(MqttClient.state()));
                          #endif
                      
                          if (MqttClient.subscribe(MqttTopic))
                          {
                                                            
                                #ifdef MqttCheckConnection_Debug 
                                       SerialDebugPrint( (ReadMqttStringFromFlash(ID_MQTT_SUSCRIBED) + String(MqttTopic)));
                                #endif
                                
                                MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_ALIVE),ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_STARTED ),true);
                                                        
                          }
                          else
                          {
                                
                                #ifdef MqttCheckConnection_Debug
                                   SerialDebugPrint(ReadMqttStringFromFlash(ID_MQTT_NOT_SUSCRIBED));
                                #endif
                          }
                           
                  }
                  else
                  {
                                        
                          #ifdef MqttCheckConnection_Debug
                                 SerialDebugPrint(CheckMqttClientStatus(MqttClient.state()));
                          #endif
                          delay(1000);    
                  }
    
    
            
         }
            
    }



    boolean MqttKeepRunning(){
         if(MqttClient.loop()==0)
         {
                MqttCheckConnection();
                   
                #ifdef MqttKeepRunning_Debug
                      SerialDebugPrint("MqttKeepRunning_Debug"); 
                      SerialDebugPrint("After connection"); 
                #endif
              
               return false;
         }
         else
         {
        
                if( DeviceSensor[0].Temperature!=DeviceSensor[0].PreviousTemperature)
               {
                      MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_INTERNAL_TEMPERATURE), String( DeviceSensor[0].Temperature), true);
                      DeviceSensor[0].PreviousTemperature=DeviceSensor[0].Temperature;
               }
                
               if( DeviceSensor[1].Temperature!=DeviceSensor[1].PreviousTemperature)
               {
                      MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_BOILER_TEMPERATURE), String( DeviceSensor[1].Temperature), true);
                      DeviceSensor[1].PreviousTemperature=DeviceSensor[1].Temperature;
               }
              
               
                if(BoilerHeating==true)
                {
                      OffPublished =false;
                      CoolingPublished=false;
                      if(HeatingPublished==false)
                      {
                            MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_Status),ReadMqttStringFromFlash(ID_MQTT_ON_HEATING),true );
                            HeatingPublished=true;
                            
                            
                      }

                      
                      if (millis() < PreviousTimeForPublishTimeLeft)
                      {
                            PreviousTimeForPublishTimeLeft=millis();
                      }
                      else if ((millis() - PreviousTimeForPublishTimeLeft) > IntervalForPublishTimeLeft)
                      {
                            MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_TIME_LEFT),Calulate_Time_And_Boiler_Heat_Capacity(BoilerDesiredTemperature, DeviceSensor[1].Temperature, BoilerDifferentialTemperature ),true);
                            MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_BOILER_HEAT_CAPACITY),String(Boiler_Heat_Capacity),true);
                            PreviousTimeForPublishTimeLeft=millis();
                      }
                      
                      
                }
              
                if(BoilerCooling==true)
                {
                      OffPublished =false;
                      HeatingPublished=false;
                      if(CoolingPublished==false)
                      {
                             MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_Status),ReadMqttStringFromFlash(ID_MQTT_ON_COOLING),true );
                             MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_TIME_LEFT),"0",true);
                             CoolingPublished=true;
                             
                                      
                      }
                      
                      
                      
              
                }
                
                if(BoilerOFF==true)
                {
                      HeatingPublished=false;
                      CoolingPublished=false;
                      if(OffPublished ==false)
                      {
                              MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_Status),ReadMqttStringFromFlash(ID_MQTT_OFF),true );
                              MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_TIME_LEFT),"0",true);
                              OffPublished =true;
                              
                      }
                  
                     
                }
                            
                return true;
         }
    }

    /* 
        -4 : MQTT_CONNECTION_TIMEOUT - the server didn't respond within the keepalive time
        -3 : MQTT_CONNECTION_LOST - the network connection was broken
        -2 : MQTT_CONNECT_FAILED - the network connection failed
        -1 : MQTT_DISCONNECTED - the client is disconnected cleanly
        0 : MQTT_CONNECTED - the cient is connected
        1 : MQTT_CONNECT_BAD_PROTOCOL - the server doesn't support the requested version of MQTT
        2 : MQTT_CONNECT_BAD_CLIENT_ID - the server rejected the client identifier
        3 : MQTT_CONNECT_UNAVAILABLE - the server was unable to accept the connection
        4 : MQTT_CONNECT_BAD_CREDENTIALS - the username/password were rejected
        5 : MQTT_CONNECT_UNAUTHORIZED - the client was not authorized to connect
    */
    String CheckMqttClientStatus(int StateCode)
    {
      
      switch (StateCode) {
        case -4:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECTION_TIMEOUT);
          break;
        case -3:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECTION_LOST);
          break;
        case -2:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECT_FAILED);
          break;
        case -1:
          return ReadMqttStringFromFlash(ID_MQTT_DISCONNECTED) ;
          break;
        case 0:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECTED) ;
          break;
        case 1:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECT_BAD_PROTOCOL);
          break;
        case 2:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECT_BAD_CLIENT_ID);
          break;
        case 3:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECT_UNAVAILABLE);
          break;
        case 4:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECT_BAD_CREDENTIALS);
          break;
        case 5:
          return ReadMqttStringFromFlash(ID_MQTT_CONNECT_UNAUTHORIZED);
          break;
        default:
          
        break;
      }
    }
#endif

