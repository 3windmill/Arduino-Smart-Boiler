#ifdef Ds18B20_Enable
        
        #include <OneWire.h>
        #include <DallasTemperature.h>
        
        
        //#include "DEVICES.h"
        byte Device_1_Internal_id=0;
        byte Device_1_Boiler_id=1;
        
        /* Pin for ONEWIRE bus   */
        #define ONE_WIRE_BUS 2
        
        /* Value for DS18B20 sensor precision - resolution
         * 9  bits  0.5°C     93.75 ms
           10 bits  0.25°C    187.5 ms
           11 bits  0.125°C   375 ms
           12 bits  0.0625°C  750 ms
        
        The EEPROM will then save this resolution in order that after 
        a power disconnection, the component will keep this resolution as default.
        */
        #define INITIAL_TEMPERATURE_PRECISION 9
        
         /*Max number of DS18B20 sensors on bus
         It must be the same with definitions cDevice1[]......on <DS18B20Strings.h> 
         */
        #define MaxNumberDs18B20SensorsOnBus 3
        
        /* Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)*/
        OneWire _OneWire(ONE_WIRE_BUS);
        /* Pass our oneWire reference to Dallas Temperature.*/ 
        DallasTemperature Ds18B20Sensors(&_OneWire);
        /* An array of 8 elements in DECIMAL format. We'll use this variable to temporary store a device address on wire bus*/
        DeviceAddress Ds18B20DeviceAddress[MaxNumberDs18B20SensorsOnBus]; 
        
        /* Number of Ds18B20 sensors found on bus after scanning */
        byte Number0fDs18B20SensorsFoundOnBus; 
        //String DS18B20Message;
        
        
        struct Device_Sensor{
         byte   Id;
         byte   NamePointer;
         float  Temperature;
         float  PreviousTemperature;
        };
        
        Device_Sensor DeviceSensor[MaxNumberDs18B20SensorsOnBus];
        
        void Ds18b20Init(){
                   
                DeviceSensor[0].Id=1;
                DeviceSensor[0].NamePointer=ID_Internal;
                DeviceSensor[0].Temperature=-1000;
                DeviceSensor[0].PreviousTemperature=-1000;
                
                DeviceSensor[1].Id=0;
                DeviceSensor[1].NamePointer=ID_Boiler;
                DeviceSensor[1].Temperature=-1000;
                DeviceSensor[1].PreviousTemperature=-1000;
                
                Ds18B20Sensors.begin();
                Number0fDs18B20SensorsFoundOnBus=LocateDevices();
                ScanAddresses(Number0fDs18B20SensorsFoundOnBus);
                
                for (int i=0;i<Number0fDs18B20SensorsFoundOnBus; i++)
                {
                        Ds18B20RestorePrecision(DeviceSensor[i].Id, Number0fDs18B20SensorsFoundOnBus, INITIAL_TEMPERATURE_PRECISION);
                }
                       
                #ifdef Ds18B20_Debug
                
                      SerialDebugPrint(ReadDS18B20StringFromFlash("DS18B20_Debug"));
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_DS18B20_SENSORS_ON_BUS)+ "\n" + String(Number0fDs18B20SensorsFoundOnBus) + "\n");
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_POWER_TYPE) + "\n" + PowerMode()+ "\n" );
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_SCAN_ADDRESSES)+ "\n" + ScanAddresses(Number0fDs18B20SensorsFoundOnBus) + "\n");
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_ADDRESSES) + "\n" + PrintAddresses(Number0fDs18B20SensorsFoundOnBus)+ "\n" );
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_RESTORE_PRECISION) + "\n" + Ds18B20RestorePrecision(DeviceSensor[0].Id, Number0fDs18B20SensorsFoundOnBus, INITIAL_TEMPERATURE_PRECISION) + "\n");
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_RESTORE_PRECISION) + "\n" + Ds18B20RestorePrecision(DeviceSensor[1].Id, Number0fDs18B20SensorsFoundOnBus, INITIAL_TEMPERATURE_PRECISION) + "\n");
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_PRECISION) + "\n" + Ds18b20GetPrecision(DeviceSensor[0].Id,Number0fDs18B20SensorsFoundOnBus)  + "\n" );
                      SerialDebugPrint(ReadDS18B20StringFromFlash(ID_PRECISION) + "\n" + Ds18b20GetPrecision(DeviceSensor[1].Id,Number0fDs18B20SensorsFoundOnBus)  + "\n") ;
              
              #endif
                
        }
        
        /* Function locates how many devices are connected on the bus and return the number of them
        */
        byte LocateDevices(){
           return  Ds18B20Sensors.getDeviceCount();
        }
        
        /********* Function scans bus power type *******************/
        
        String PowerMode(){
          
          if (Ds18B20Sensors.isParasitePowerMode()){
            
             return ReadDS18B20StringFromFlash(ID_PARASITE_POWER);
          }
          else{
            
            return ReadDS18B20StringFromFlash(ID_NORMAL_POWER);
          }
        
        }
        
        /************Function Scan DS18B20 Addresses ******************************************/
        
        byte ScanAddresses(byte Number_0f_Devices ){
                 byte counter=0;          
                /*Loop through each device, print out address and set resolution*/
                if(Number_0f_Devices > 0)
                {
                      for(int i=0;i<Number_0f_Devices; i++) 
                      {
        
                          Ds18B20Sensors.getAddress(Ds18B20DeviceAddress[i], i);
                          counter = counter +1;
                      }
                }
                else
                {
                      return counter;  
                }
                
        }
        
        /************Function Print for one DS18B20's Address ******************************/
        
        String PrintAddress(byte Number_0f_Devices, byte Sensor_ID)
        {
          String Output;
          if(Number_0f_Devices>0)
          {
            
          
                
              for (int j = 0; j < 8; j++) 
              {
                  Output= Output+ (Ds18B20DeviceAddress[Sensor_ID][j]);
              }
              Output= Output+ "\n";
        
              return Output;
        
          }
          else
          {
                return "0";
          }
          
        }
        
        /************Function Print for all DS18B20's Address  ********************************/
        
        String PrintAddresses(byte Number_0f_Devices)
        {
          String Output;
          if(Number_0f_Devices>0)
          {
            
          
                for (int i=0; i< Number_0f_Devices;i++)
                {
                      for (int j = 0; j < 8; j++) 
                      {
                          Output= Output+ (Ds18B20DeviceAddress[i][j]);
                      }
                      Output= Output+ "\n";
                }
                return Output;
        
          }
          else
          {
                return "0";
          }
          
        }
        
        /************Function read precision for a DS18B20  ***********************************/
        
        int Ds18b20GetPrecision(byte SensorId, byte Number_0f_Devices ){
          if(Number_0f_Devices>0)
          {
              return Ds18B20Sensors.getResolution(Ds18B20DeviceAddress[SensorId]);
          }
          else
          {
            return 0; 
          }
        }
        
        /************Function restore precision for a DS18B20  ***********************************/
        
        boolean Ds18B20RestorePrecision(int SensorId,byte Number_0f_Devices,int TEMPERATURE_PRECISION ){
          if((Number_0f_Devices>0) && (Ds18b20GetPrecision(SensorId, Number_0f_Devices)!=TEMPERATURE_PRECISION)){
                
              return Ds18B20Sensors.setResolution(Ds18B20DeviceAddress[SensorId], TEMPERATURE_PRECISION);
          }
          else
          {
            return false;
          }
        }
        
        /************Function set precision for a DS18B20  ***********************************/
        
        boolean Ds18B20SetPrecision(int SensorId,byte Number_0f_Devices,int TEMPERATURE_PRECISION ){
          if(Number_0f_Devices>0)
          {
              return Ds18B20Sensors.setResolution(Ds18B20DeviceAddress[SensorId], TEMPERATURE_PRECISION);
          }
          else
          {
            return false; 
          }
        
        }
        
        /************Function read temperature for a DS18B20  ***********************************/
        
        float GetDs18b20Temperatures(byte SensorId, byte Number_0f_Devices){
               if(Number_0f_Devices>0)
               {
                    Ds18B20Sensors.requestTemperatures();
                    return Ds18B20Sensors.getTempC(Ds18B20DeviceAddress[SensorId]);
               }
               else
               {
                     return 1000;
               }
        }
        
        
        /************Function read temperature for all DS18B20 and store it to a data type  ***********************************/
        void Ds18b20_Running()
        {
         
            if(Number0fDs18B20SensorsFoundOnBus>0)
                {
                    for (int SensorId=0;SensorId<Number0fDs18B20SensorsFoundOnBus; SensorId++)
                    {
                          
                          DeviceSensor[SensorId].Temperature = GetDs18b20Temperatures(DeviceSensor[SensorId].Id, Number0fDs18B20SensorsFoundOnBus);
                    
                          #ifdef Ds18B20_Debug
                                
                                SerialDebugPrint(String(SensorId));
                                SerialDebugPrint(String(DeviceSensor[SensorId].Temperature));
                                
                        #endif 
                    } 
                }
        }

#endif
