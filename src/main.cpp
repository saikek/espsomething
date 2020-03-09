#include <ESP8266WiFi.h>
#include <stdio.h>

#define WIFI_HOTSPOT_NAME "WZA"
#define WIFI_HOTSPOT_PASSWORD "1234567890"

String macToString(const unsigned char *mac)
{
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;
WiFiEventHandler probeRequestPrintHandler;

void onProbeRequestPrint(const WiFiEventSoftAPModeProbeRequestReceived &evt)
{
  
  String mac = macToString(evt.mac);
  
  //TODO - It is preferred to take average RSSI here since it can wiledly differ with each probe request. Collect from few probes or 1 second time ? 
  Serial.print("Probe request from: ");
  Serial.print(mac);
  Serial.print(" RSSI: ");
  Serial.println(evt.rssi);
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected &evt)
{
  Serial.print("Station connected: ");
  Serial.println(macToString(evt.mac));
  Serial.print(evt.aid);
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected &evt)
{
  Serial.printf("Station disconnected: ");
  Serial.println(macToString(evt.mac));
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP(WIFI_HOTSPOT_NAME, WIFI_HOTSPOT_PASSWORD);
  if (result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }

  probeRequestPrintHandler = WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestPrint);

  stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);

  stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);
}

void testTone(){
  tone(13, 2000, 1000);
}

void loop()
{
  Serial.printf("Stations connected = %d  %d \n", WiFi.softAPgetStationNum(), 0);

  //testTone();

  delay(3000);
}