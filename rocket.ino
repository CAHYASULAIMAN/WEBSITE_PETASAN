#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

#define HEATER 23

void callback(char* topic, byte* payload, unsigned int length) {

String msg="";

for(int i=0;i<length;i++){
msg += (char)payload[i];
}

if(msg=="ON"){
digitalWrite(HEATER,HIGH);
}

if(msg=="OFF"){
digitalWrite(HEATER,LOW);
}

}

void reconnect(){

while(!client.connected()){

client.connect("ESP32heater");

client.subscribe("esp32/heater");

}

}

void setup(){

Serial.begin(115200);

pinMode(HEATER,OUTPUT);

WiFi.begin(ssid,password);

while(WiFi.status()!=WL_CONNECTED){
delay(500);
}

client.setServer(mqtt_server,1883);

client.setCallback(callback);

}

void loop(){

if(!client.connected()){
reconnect();
}

client.loop();

}
