float BoilerDesiredTemperature=1000;
float BoilerDifferentialTemperature=0.5;  /* can't be zero , if you want to set it to zero you must change if conditions 
                                            in Boiler_Relay_OnOff() function,  cause it can't be <= and >=
                                            one condition must be only equal
                                            so instead of
                                            if ((BoilerRelayOnOff == 1) && (DeviceSensor[1].Temperature <= (BoilerDesiredTemperature - BoilerDifferentialTemperature)))
                                            if ((BoilerRelayOnOff == 1) && (DeviceSensor[1].Temperature >= (BoilerDesiredTemperature + BoilerDifferentialTemperature)))
                                            
                                            you have to set
                                            if ((BoilerRelayOnOff == 1) && (DeviceSensor[1].Temperature <= (BoilerDesiredTemperature - BoilerDifferentialTemperature)))
                                            if ((BoilerRelayOnOff == 1) && (DeviceSensor[1].Temperature > (BoilerDesiredTemperature + BoilerDifferentialTemperature)))
                                            
                                            */

float Electric_Power=4000;
float Water_Volume=119;
float Water_Mass=119;
float Water_C=4186;
float Boiler_Heat_Capacity=0;


