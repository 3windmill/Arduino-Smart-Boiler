#ifdef WebServer_Enable
        
        
        EthernetServer Webserver(80);       /*create a server at port 80*/
       
        #define REQ_BUF_SZ   50             /*size of buffer used to capture HTTP requests*/
        char HTTP_req[REQ_BUF_SZ] = {0};    /*buffered HTTP request stored as null terminated string*/
        char req_index = 0;                 /*index into HTTP_req buffer*/
        
        void WebServerInit()
        {
            Webserver.begin();
        }
        
        void WebServerRunning()
        {
        
            EthernetClient WebClient = Webserver.available();  /* try to get client*/
        
            if (WebClient)                                     /* got client*/
            {  
                boolean currentLineIsBlank = true;
                
                while (WebClient.connected()) 
                {
                        if (WebClient.available())          
                        {   
                              char c = WebClient.read();                /*read 1 byte (character) from client*/
                                                                        /*buffer first part of HTTP request in HTTP_req array (string)*/
                                                                        /* leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)*/
                              if (req_index < (REQ_BUF_SZ - 1)) 
                              {
                                  HTTP_req[req_index] = c;              /* save HTTP request character*/
                                  req_index++;
                              }
                       
                              if (c == '\n' && currentLineIsBlank)             /*last line of client request is blank and ends with \n
                                                                                respond to client only after last line received*/
                              {
                                 
                                    WebClient.println(ReadWebServerStringFromFlash(ID_HTML_RESPONSE_HEADER));  /*send a standard http response header ID_HTML_RESPONSE_HEADER*/
                                  
                                    if (StrContains(HTTP_req, "xmlreport")) 
                                    {
                                          XML_response(WebClient);
                                    }
                                  
                                    else 
                                    {  
                                          RootWebPageResponce(WebClient);           /* web page request*/
              
              
                                    }
                                  
                                  // display received HTTP request on serial port
                                  //Serial.print(HTTP_req);
                                  // reset buffer index and all buffer elements to 0
                                  
                                  req_index = 0;
                                  StrClear(HTTP_req, REQ_BUF_SZ);
                                  break;
                              }
                                                                                  /*every line of text received from the client ends with \r\n  
                                                                                  last character on line of received text
                                                                                  starting new line with next character read*/
                              if (c == '\n')                                               
                              {
                                  
                                  currentLineIsBlank = true;
                              } 
                              else if (c != '\r')
                              {
                                                                                  /* a text character was received from client*/
                                  currentLineIsBlank = false;
                              }
                      } /*end if (client.available())*/
                } /*end while (client.connected())*/
                
                delay(1);                                                         /*give the web browser time to receive the data*/
                WebClient.stop();                                                 /*close the connection*/
            } /*end if (client)*/  
        }
        
        void XML_response(EthernetClient Ethernet_Client)
        {
                
              Ethernet_Client.println(ReadWebServerStringFromFlash(ID_XML_RESPONSE_HEADER));
              Ethernet_Client.println(ReadWebServerStringFromFlash(ID_Connection_Close));
              Ethernet_Client.println();
              Ethernet_Client.print(ReadWebServerStringFromFlash(ID_XML_HEADER_1));
              Ethernet_Client.print(ReadWebServerStringFromFlash(ID_XML_HEADER_2));
        
              Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_SMARTBOILER)+ ">");
              
              Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_VERSION)+ ">");
              Ethernet_Client.print(ReadMainStringFromFlash(ID_VERSION_No));
              Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_VERSION)+ ">");
        
             
              Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_IP)+ ">");
              Ethernet_Client.print(PrintIP(SmartBoilerIp));
              Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_IP)+ ">");
        
             #ifdef MqttClient_Enable
             
                   Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_MQTT_SERVER)+ ">");
                   
                   Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_IP)+ ">");
                   Ethernet_Client.print(PrintIP(MqttServerIP));
                   Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_IP)+ ">");
                             
                   Ethernet_Client.print("<" + ReadMqttStringFromFlash(ID_MQTT_STATUS)+ ">");
                   Ethernet_Client.print(CheckMqttClientStatus(MqttClient.state()));
                   Ethernet_Client.print("</" + ReadMqttStringFromFlash(ID_MQTT_STATUS)+ ">");
                   
                   Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_MQTT_CLIENT_TOPICS)+ ">");
                   
                   Ethernet_Client.print(ReadMqttStringFromFlash(ID_MQTT_TOPIC_IN_ONOFF)) ;
                   Ethernet_Client.println(ReadWebServerStringFromFlash(ID_XML_SPACE)) ;
                   Ethernet_Client.print(ReadMqttStringFromFlash(ID_MQTT_TOPIC_IN_DESIRED_TEMPERATURE)) ;
                   Ethernet_Client.println(ReadWebServerStringFromFlash(ID_XML_SPACE)) ;
                   Ethernet_Client.print((ReadMqttStringFromFlash(ID_MQTT_TOPIC_IN_Time)) );
                   Ethernet_Client.println(ReadWebServerStringFromFlash(ID_XML_SPACE)) ;
                   Ethernet_Client.print((ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_ALIVE)) );
                   Ethernet_Client.println(ReadWebServerStringFromFlash(ID_XML_SPACE)) ;
                   Ethernet_Client.print((ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_BOILER_TEMPERATURE)) );
                   Ethernet_Client.println(ReadWebServerStringFromFlash(ID_XML_SPACE)) ;
                   Ethernet_Client.print((ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_TIME_LEFT)) );
                   Ethernet_Client.println(ReadWebServerStringFromFlash(ID_XML_SPACE)) ;
                   Ethernet_Client.print(ReadMqttStringFromFlash(ID_MQTT_TOPIC_OUT_Status ) );
                                      
                   Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_MQTT_CLIENT_TOPICS)+ ">");
                   
                   Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_MQTT_SERVER)+ ">");
            #endif
             
            Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_DEVICES)+ ">");
            
            #ifdef Ds18B20_Enable
                  Ethernet_Client.print("<" + ReadDS18B20StringFromFlash(ID_DS18B20) + ">");
                  Ethernet_Client.print("<" + ReadDS18B20StringFromFlash(ID_DS18B20_SENSORS_ON_BUS) + ">");
                  Ethernet_Client.print(String(Number0fDs18B20SensorsFoundOnBus));
                  Ethernet_Client.print("</" + ReadDS18B20StringFromFlash(ID_DS18B20_SENSORS_ON_BUS) + ">");
        
                  Ethernet_Client.print("<" + ReadDS18B20StringFromFlash(ID_POWER_TYPE) + ">");
                  Ethernet_Client.print(PowerMode());
                  Ethernet_Client.print("</" + ReadDS18B20StringFromFlash(ID_POWER_TYPE) + ">");
                            
                  for(int i=0;i<Number0fDs18B20SensorsFoundOnBus; i++) 
                  {
                       Ethernet_Client.print("<" + ReadMainStringFromFlash(DeviceSensor[i].NamePointer) + ">");
                       Ethernet_Client.print("<" + ReadDS18B20StringFromFlash(ID_ADDRESSES) + ">");
                       Ethernet_Client.print(PrintAddress(Number0fDs18B20SensorsFoundOnBus,DeviceSensor[i].Id));
                       Ethernet_Client.print("</" + ReadDS18B20StringFromFlash(ID_ADDRESSES) + ">");
                       Ethernet_Client.print("<" + ReadDS18B20StringFromFlash(ID_PRECISION) + ">");
                       Ethernet_Client.print(Ds18b20GetPrecision(DeviceSensor[i].Id,Number0fDs18B20SensorsFoundOnBus));
                       Ethernet_Client.print("</" + ReadDS18B20StringFromFlash(ID_PRECISION) + ">");
                       Ethernet_Client.print("<" + ReadMainStringFromFlash(ID_TEMPERATURE) + ">");
                       Ethernet_Client.print( DeviceSensor[i].Temperature);
                       Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_TEMPERATURE) + ">");
                       Ethernet_Client.print("</" + ReadMainStringFromFlash(DeviceSensor[i].NamePointer) + ">");
                          
                 }
            #endif
            Ethernet_Client.print("</" + ReadDS18B20StringFromFlash(ID_DS18B20) + ">");
            Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_DEVICES)+ ">");
                  
            Ethernet_Client.print("</" + ReadMainStringFromFlash(ID_SMARTBOILER)+ ">");;
              
        }
        
        
        /*sets every element of str to 0 (clears array)*/
        
        void StrClear(char *str, char length)
        {
            for (int i = 0; i < length; i++) {
                str[i] = 0;
            }
        }
        
        /*searches for the string sfind in the string str
        returns 1 if string found
        returns 0 if string not found*/
        
        char StrContains(char *str, char *sfind)
        {
            char found = 0;
            char index = 0;
            char len;
        
            len = strlen(str);
            
            if (strlen(sfind) > len) {
                return 0;
            }
            while (index < len) {
                if (str[index] == sfind[found]) {
                    found++;
                    if (strlen(sfind) == found) {
                        return 1;
                    }
                }
                else {
                    found = 0;
                }
                index++;
            }
            return 0;
        }
        
        
        void RootWebPageResponce(EthernetClient Ethernet_Client)
        {
         // send rest of HTTP headerID_HTML_HEADER 
                         Ethernet_Client.println(ReadWebServerStringFromFlash(ID_HTML_HEADER ));
                         Ethernet_Client.println(ReadWebServerStringFromFlash(ID_Connection_Close));
                         Ethernet_Client.println();
                         Ethernet_Client.println( ReadMainStringFromFlash(ID_SMARTBOILER));
                                
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_HTML_FORM_1));
                         Ethernet_Client.print(PrintIP(SmartBoilerIp));
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_HTML_FORM_2));
        
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_HTML_FORM_INPUT_1));
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_HTML_FORM_INPUT_2));
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_xml_report));
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_HTML_FORM_INPUT_1_CLOSE));
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_HTML_FORM_INPUT_2_CLOSE));
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_xml_report));
                         Ethernet_Client.print(ReadWebServerStringFromFlash(ID_HTML_FORM_1_CLOSE));
                          
                         Ethernet_Client.println(" ");
        }

#endif


/*                  
                          client.println("<form action=\"http://192.168.1.110/\" method=\"get\">");
                          client.println(" <label>IP: <input type=\"text\" name=\"ip\"></label>");
                          //client.println(" <label>Last Name: <input type=\"text\" name=\"ln\"></label>");
                          client.println(" <button type=\"submit\" value=\"submit\">submit</button>");
                          client.println(" <button type=\"reset\" value=\"reset\">reset</button>");
        //                  client.println("<input type=\"hidden\" name=\"switch\" value=\"xmlreport\"><input type=\"submit\" value=\"xmlreport\">");
                          client.println(" </form>");
                                
                                // send web page
        //                        webFile = SD.open("index.htm");        // open web page file
        //                        if (webFile) {
        //                            while(webFile.available()) {
        //                                client.write(webFile.read()); // send web page to client
        //                            }
        //                            webFile.close();
        //                        }
        */
