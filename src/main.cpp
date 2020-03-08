#include <ESP8266WiFi.h>

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
  Serial.print("Probe request from: ");
  Serial.print(macToString(evt.mac));
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
  Serial.print("Station disconnected: ");
  Serial.println(macToString(evt.mac));
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("WZA", "1234567890");
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

void loop()
{
  Serial.printf("Stations connected = %d  %d \n", WiFi.softAPgetStationNum(), 0);

  delay(3000);
}