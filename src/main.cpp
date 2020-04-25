#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>
#include <llp.h>

#include <constants.h>
#include <connect.h>
#include <proximity_sensor.h>

WiFiClient net;
MQTTClient client;
DataPack input = DataPack();
ProximitySensor sensor = ProximitySensor(0x64, 1, 100);



long reportTimer = millis();
long alarmTimer = millis();

long distance = 0;


void setup() {
  
 
  Serial.begin(115200);
  WiFi.begin(SSID, SSID_PASSWORD);
  client.begin(BROKER, net);
  connect(Serial, net, client);
  sensor.init(4, 5);
 
}

void loop() {
  client.loop();
  delay(10);

  distance = sensor.read();
  Serial.println(distance);

  if (!client.connected()) {
    connect(Serial, net, client);
  }

  if(millis()-reportTimer >= REPORT_FREQ){
    reportTimer=millis();
    client.publish(String(MQTT_ID)+"/report", String(distance));
    }



}