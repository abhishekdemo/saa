#include <WiFi.h>
#include <HTTPClient.h>

#define PIN_LED 2
#define PIN_BUTTON 0
#define DEBOUNCE_DELAY 300

#define WIFI_SSID "AK"
#define WIFI_PASS "diot12345"

#define HOST "http://192.168.77.204:8080/esp32"

unsigned long lastDebounceTime=0;
int numberToSend=1234;
void setup(){
pinMode(PIN_LED,OUTPUT);
pinMode(PIN_BUTTON,INPUT);
Serial.begin(115200);
Serial.println();
Serial.println("Connecting to");
Serial.println(WIFI_SSID);
WiFi.begin(WIFI_SSID,WIFI_PASS);


while (WiFi.status() !=WL_CONNECTED) {
Serial.print(" ");
delay(5000);
}
Serial.println("");
Serial.print("WiFi connected. IP adddress is:");
Serial.println(WiFi.localIP());
Serial.println(",with Mac Address:");
Serial.println(WiFi.macAddress());

digitalWrite(PIN_LED,HIGH);
delay(100);
digitalWrite(PIN_LED,LOW);

Serial.println("Setup Complete");

}

void loop()
{

  int reading =digitalRead(PIN_BUTTON);
  unsigned long  currentTime=millis();

  if((reading==LOW)&& ((currentTime-lastDebounceTime) >DEBOUNCE_DELAY)){
    lastDebounceTime=currentTime;

    String macAddr=WiFi.macAddress();
    String textToSend="Hello from ESP32 my MAC Address:"+macAddr+"Test Random Value:"+String(numberToSend);
    numberToSend++;

    Serial.print("Button Pressed ,sending:");
    Serial.println(textToSend);
    postRequest(textToSend);
  }
}

void postRequest(String message){
HTTPClient http;
http.begin(HOST);
http.addHeader("Content-Type","text/plain");
int httpCode=http.POST(message);
String payload=http.getString();

Serial.println(httpCode);
Serial.println(payload);

http.end();

}





