
float PreviousMillis=0;
float RealTime_ToHeat_Boiler=0;
float Theoritical_TimeLeft=0;
float InititalTemperature=0;
boolean RunForFirstTime=true;

String Calulate_Time_And_Boiler_Heat_Capacity(float DesiredTemp, float Temperature , float Differential )
{   
  
  //Serial.println(TimeLeft);
  
  if (millis() < PreviousMillis)
  {
      PreviousMillis=millis();
  }
  else
  {
      if(RunForFirstTime==true)
      {
        InititalTemperature=Temperature;
        RunForFirstTime=false;
      }
      //Serial.println("Theoritical_TimeLeft");
      Theoritical_TimeLeft= (((Water_Mass*Water_C)*((DesiredTemp + Differential)-InititalTemperature))/(Electric_Power *60)); //unit min 
      
      //Serial.println(Theoritical_TimeLeft);
      if((DesiredTemp + Differential) > Temperature)
      {
            //Serial.println("millis()");
            //Serial.println(millis());
            //Serial.println("PreviousMillis");
            //Serial.println(PreviousMillis);
            
            //Serial.println("RealTime_ToHeat_Boiler");
            //Serial.println(RealTime_ToHeat_Boiler);
            RealTime_ToHeat_Boiler= RealTime_ToHeat_Boiler + ((millis()-PreviousMillis)/60000);// unit min
            if(RealTime_ToHeat_Boiler > Theoritical_TimeLeft)
            {
                  //Serial.println("Boiler_Heat_Capacity");
                  Boiler_Heat_Capacity=(Electric_Power*(RealTime_ToHeat_Boiler-Theoritical_TimeLeft)/((DesiredTemp + Differential)-InititalTemperature));
                  //Serial.println(Boiler_Heat_Capacity);
            }
            PreviousMillis=millis();
            //Serial.println("end function");
            return String(((((Water_Mass*Water_C)+Boiler_Heat_Capacity)*((DesiredTemp + Differential)-Temperature))/(Electric_Power *60)));     
      }
      else
      {
      RunForFirstTime=true;
      // store to memory
      return  "0" ;  
      }
  }
  
  
}  
