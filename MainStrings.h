/*
*************************PROGMEM DEFINITIONS***************************************

keep always the same order in table definition below

*/
// CHARACTER RULER                    PROGMEM = "12345678901234567892123456789";
const char cBOILER[]                  PROGMEM = "BOILER";
const char cRELAY[]                   PROGMEM = "RELAY";
const char cINTERNAL[]                PROGMEM = "INTERNAL";
const char cDEVICES[]                 PROGMEM = "DEVICES";
const char cTEMPERATURE[]             PROGMEM = "TEMPERATURE";
const char cIP[]                      PROGMEM = "IP";
const char cMQTT_SERVER[]             PROGMEM = "MQTT_SERVER";
const char cSMARTBOILER[]             PROGMEM = "SMARTBOILER";
const char cVERSION[]                 PROGMEM = "VERSION";
const char cVERSION_No[]              PROGMEM = "20_2707170045";
const char cMQTT_CLIENT_TOPICS[]      PROGMEM = "TOPICS";

/*Defining Strings ID */
#define ID_Boiler                    0
#define ID_Relay                     1
#define ID_Internal                  2
#define ID_DEVICES                   3
#define ID_TEMPERATURE               4
#define ID_IP                        5
#define ID_MQTT_SERVER               6
#define ID_SMARTBOILER               7
#define ID_VERSION                   8
#define ID_VERSION_No                9
#define ID_MQTT_CLIENT_TOPICS        10
/* Then set up a table to refer to your strings.*/

const char* const Main_StringTable[] PROGMEM = {\
cBOILER,          cRELAY,             cINTERNAL,\
cDEVICES ,        cTEMPERATURE,       cIP,\
cMQTT_SERVER,  cSMARTBOILER,       cVERSION, \
cVERSION_No,  cMQTT_CLIENT_TOPICS \
};

/**************Use this function to retrieve strings ***********/
String ReadMainStringFromFlash(byte StringID)
{
    char mybuffer[30];
    
    strcpy_P(mybuffer, (char*)pgm_read_word(&(Main_StringTable[StringID]))); 
    return String(mybuffer);

}
