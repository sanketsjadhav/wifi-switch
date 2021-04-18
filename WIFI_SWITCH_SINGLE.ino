#include <ESP8266WiFi.h>
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "SWITCH1" ;
 
WiFiServer server(80);
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>SWITCH Control</title></head><body><div id='main'><h2>SWITCH Control</h2>";
String html_2 = "";
String html_5 = "<input class='button' type='submit' value='CHANGE SWITCH NAME' ></form><br>";
String html_6 = "<input class='button' type='submit' value='CHANGE SWITCH PASS' ></form><br>";
String html_4 = "</div></body></html>";
 
String request = "";
int LED_Pin1 = 0;
 
void setup() 
{
    pinMode(LED_Pin1, OUTPUT); 
 
    boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
    server.begin();
 
} // void setup()
 
 
 
void loop() 
{
 
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    if       ( request.indexOf("LED1ON") > 0 )  { digitalWrite(LED_Pin1, HIGH);  }
    else if  ( request.indexOf("LED1OFF") > 0 ) { digitalWrite(LED_Pin1, LOW);   }
 
 
    // Get the LED pin status and create the LED status message
    if (digitalRead(LED_Pin1) == HIGH) 
    {
        // the LED is on so the button needs to say turn it off
       html_2 = "<form id='F1' action='LED1OFF'><input class='button' type='submit' value='SWITCH1 OFF' ></form><br>";
    }
    else                              
    {
        // the LED is off so the button needs to say turn it on
        html_2 = "<form id='F1' action='LED1ON'><input class='button' type='submit' value='SWITCH1 ON' ></form><br>";
    }

 
    client.flush();
 
    client.print( header );
    client.print( html_1 );    
    client.print( html_2 );
     client.print( html_5);
    client.print( html_6);
    client.print( html_4);
   
 
    delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} // void loop()
