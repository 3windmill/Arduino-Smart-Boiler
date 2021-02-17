/* changing mac address beware of multicast broadcast mac adress*/
byte SmartBoilerMac[]    = { 0xDE, 0xAD, 0xBE, 0x5F, 0xEC, 0xC5 };

IPAddress SmartBoilerIp(192, 168, 1, 110);
IPAddress LocalDns(192,168,1,252); // default ethernet library by default sets to the device IP address with the last octet set to 1 
IPAddress Gateway(192, 168, 1,254 );// default ethernet library by default sets to the device IP address with the last octet set to 1 
IPAddress Subnet(255, 255, 255, 0);

void StartEtherenet(){
      
      Ethernet.begin(SmartBoilerMac, SmartBoilerIp,LocalDns,Gateway,Subnet);
}

String PrintIP(IPAddress IP)
{
   String _ip;
   for(int i=0;i<4; i++)
   { 
       _ip=_ip + String(IP[i]);
       
       if(i<3) {
          _ip=_ip + (".");
       }
   }
   return _ip;
}

