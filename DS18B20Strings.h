#ifdef Ds18B20_Enable

/*
*************************PROGMEM DEFINITIONS***************************************

keep always the same order in table definition below

*/
// CHARACTER RULER                    PROGMEM = "12345678901234567892123456789";
const char cPOWER_TYPE[]              PROGMEM = "POWER_TYPE";
const char cPARASITE_POWER[]          PROGMEM = "PARASITE";
const char cNORMAL_POWER[]            PROGMEM = "NORMAL";
const char cDS18B20_SENSORS_ON_BUS[]  PROGMEM = "SENSORS_ON_BUS";
const char cADDRESSES[]               PROGMEM = "ADDRESSES";
const char cPRECISION[]               PROGMEM = "PRECISION";
const char cSCAN_ADDRESSES[]          PROGMEM = "SCAN_ADDRESSES";
const char cRESTORE_PRECISION[]       PROGMEM = "RESTORE_PRESISION";
const char cDS18B20[]                 PROGMEM = "Ds18B20";
/*Defining Strings ID */
#define ID_POWER_TYPE                0
#define ID_PARASITE_POWER            1
#define ID_NORMAL_POWER              2
#define ID_DS18B20_SENSORS_ON_BUS    3
#define ID_ADDRESSES                 4
#define ID_PRECISION                 5
#define ID_SCAN_ADDRESSES            6
#define ID_RESTORE_PRECISION         7
#define ID_DS18B20                   8
/* Then set up a table to refer to your strings.*/

const char* const Ds18B20_StringTable[] PROGMEM = {\
cPOWER_TYPE,    cPARASITE_POWER,    cNORMAL_POWER,        cDS18B20_SENSORS_ON_BUS,\
cADDRESSES,     cPRECISION,         cSCAN_ADDRESSES,      cRESTORE_PRECISION,\
cDS18B20\
};

/**************Use this function to retrieve strings ***********/
String ReadDS18B20StringFromFlash(byte StringID)
{
    char mybuffer[30];
    
    strcpy_P(mybuffer, (char*)pgm_read_word(&(Ds18B20_StringTable[StringID]))); 
    return String(mybuffer);

}

#endif
