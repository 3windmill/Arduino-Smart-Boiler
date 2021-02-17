#ifdef WebServer_Enable
        
        /*
        *************************PROGMEM DEFINITIONS***************************************
        
        keep always the same order in table definition below
        
        */
                                                                   
        // CHARACTER RULER                                PROGMEM ="12345678901234567892123456789";
        const char cXML_RESPONSE_HEADER[]                 PROGMEM ="Content-Type: text/xml";
        const char cXML_HEADER_1[]                        PROGMEM ="<?xml version=\"1.0\"";
        const char cXML_HEADER_2[]                        PROGMEM =" encoding=\"UTF-8\"?>";
        const char cxml_report[]                          PROGMEM =" xmlreport";
        const char cConnection_Close[]                    PROGMEM ="Connection: close";
        const char cHTML_RESPONSE_HEADER[]                PROGMEM ="HTTP/1.1 200 OK";
        const char cHTML_HEADER[]                         PROGMEM ="Content-Type: text/html";
        const char cHTML_FORM_1[]                         PROGMEM ="<form action=\"http://";
        const char cHTML_FORM_2[]                         PROGMEM ="/\" method=\"get\">";
        const char cHTML_FORM_INPUT_1[]                   PROGMEM ="<input type=\"hidden\" name";
        const char cHTML_FORM_INPUT_2[]                   PROGMEM ="=\"switch\" value=\"";
        const char cHTML_FORM_INPUT_1_CLOSE[]             PROGMEM ="\"><input type=\"submit\"";
        const char cHTML_FORM_INPUT_2_CLOSE[]             PROGMEM ="value=\"";
        const char cHTML_FORM_1_CLOSE[]                   PROGMEM ="\"></form>";
        const char cXML_SPACE[]                           PROGMEM =" | ";
        
        /*Defining Strings ID */
        #define ID_XML_RESPONSE_HEADER       0
        #define ID_XML_HEADER_1              1
        #define ID_XML_HEADER_2              2
        #define ID_xml_report                3
        #define ID_Connection_Close          4
        #define ID_HTML_RESPONSE_HEADER      5
        #define ID_HTML_HEADER               6
        #define ID_HTML_FORM_1               7
        #define ID_HTML_FORM_2               8
        #define ID_HTML_FORM_INPUT_1         9
        #define ID_HTML_FORM_INPUT_2         10
        #define ID_HTML_FORM_INPUT_1_CLOSE   11    
        #define ID_HTML_FORM_INPUT_2_CLOSE   12
        #define ID_HTML_FORM_1_CLOSE         13
        #define ID_XML_SPACE                 14
        /* Then set up a table to refer to your strings.*/
        
        const char* const WebServer_StringTable[] PROGMEM = {\
        cXML_RESPONSE_HEADER,  cXML_HEADER_1,   cXML_HEADER_2,\
        cxml_report,            cConnection_Close,     cHTML_RESPONSE_HEADER,\
        cHTML_HEADER,          cHTML_FORM_1,    cHTML_FORM_2,\
        cHTML_FORM_INPUT_1,    cHTML_FORM_INPUT_2,  cHTML_FORM_INPUT_1_CLOSE,\
        cHTML_FORM_INPUT_2_CLOSE, cHTML_FORM_1_CLOSE, cXML_SPACE\
        };
        
        /**************Use this function to retrieve strings ***********/
        String ReadWebServerStringFromFlash(byte StringID)
        {
            char mybuffer[30];
            
            strcpy_P(mybuffer, (char*)pgm_read_word(&(WebServer_StringTable[StringID]))); 
            return String(mybuffer);
        
        }


#endif
