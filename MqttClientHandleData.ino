#ifdef MqttClient_Enable

      void MqttClientHandleIncomming(String HandleInCommingData,boolean HandleInCommingData_Flag){
            byte   Index;
            String SubStringPart1;
            String SubStringPart2;
                
            #ifdef MqttClientHanldeIncomming_Debug
                   SerialDebugPrint("MqttClientHanldeIncomming_Debug");
                   SerialDebugPrint(HandleInCommingData);
                   SerialDebugPrint("HandleInCommingData_Flag");
                   SerialDebugPrint(String(HandleInCommingData_Flag)); 
            #endif
            
            if(HandleInCommingData_Flag==true)
            {
                  Index=HandleInCommingData.indexOf("#");
                  SubStringPart1=HandleInCommingData.substring(0,(Index));
                  SubStringPart2=HandleInCommingData.substring(Index+1);
                  
                  if(SubStringPart1.equals(ReadMqttStringFromFlash(ID_MQTT_TOPIC_IN_ONOFF)))
                  {
                        if((SubStringPart2.equals("On")) || (SubStringPart2.equals("1")))
                        {
                              BoilerRelayOnOff=1;
                                  
                        }
                        else
                        {
                              BoilerRelayOnOff=0;
                        }
                  }
      
                   if(SubStringPart1.equals(ReadMqttStringFromFlash(ID_MQTT_TOPIC_IN_Time)))
                  {
                        MqttPublishData(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_ALIVE),SubStringPart2,true );
                        
                  }
      
                  if(SubStringPart1.equals(ReadMqttStringFromFlash(ID_MQTT_TOPIC_IN_DESIRED_TEMPERATURE)))
                  {
                    
                        BoilerDesiredTemperature=SubStringPart2.toFloat();
                   
                  }
                  
            }
            
            #ifdef MqttClientHanldeIncomming_Debug
                   SerialDebugPrint(SubStringPart1);
                   SerialDebugPrint(SubStringPart2);
                   SerialDebugPrint("BoilerRelayOnOff");
                   SerialDebugPrint(String(BoilerRelayOnOff));
                   SerialDebugPrint("DesiredTemperature");
                   SerialDebugPrint(String(DesiredTemperature));
            #endif
      
      }
      
      boolean MqttPublishData(String MqttTopic, String DataToPublish, boolean Retain)
      {
                char  MqttPayload[15] ;
                int   Length1=0;
                int   Length2=0;
                char  _MqttTopic[30];
                
                Length1 =DataToPublish.length();
                DataToPublish.toCharArray( MqttPayload,Length1+1);
                Length2=MqttTopic.length();
                MqttTopic.toCharArray( _MqttTopic,Length2+1);
                 
                 #ifdef MqttPublishData_Debug;
                        SerialDebugPrint("MqttPublishData_Debug");
                        SerialDebugPrint("Length1");
                        SerialDebugPrint(String(Length1));
                        SerialDebugPrint("DataToPublish");
                        SerialDebugPrint(DataToPublish);
                        SerialDebugPrint("MqttPayload");
                        SerialDebugPrint(MqttPayload);
                        
                #endif  
                
                return MqttClient.publish(_MqttTopic,MqttPayload,Length1,Retain);
      }



#endif
