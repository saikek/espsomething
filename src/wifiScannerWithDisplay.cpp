#ifdef false

#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
// #include <EasyButton.h>
#include <LinkedList.h>

#define SDA 5
#define SCL 4

#define BUTTON_PROGRAM 0

#define DISPLAY_W 64
#define DISPLAY_H 128

#define SINGAL_GRAPH_SIZE DISPLAY_W - 5

#define WIFI_ENDPOINT_NAME "WZA"

// EasyButton button(BUTTON_PROGRAM);

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R1, SCL, SDA);

LinkedList<int> signalHistoryValues = LinkedList<int>();

struct networks
{
  String Name;
  int Signal;
};

networks discoveredNetworks[20];

int reMap(int value)
{
  return map(value, -99, -30, 0, 50);
}

void get_and_sort_networks(byte available_networks)
{
  // First get all network names and their signal strength
  for (int i = 0; i < available_networks; i++)
  {
    discoveredNetworks[i].Signal = WiFi.RSSI(i);
    discoveredNetworks[i].Name = WiFi.SSID(i);
  }

  String temp_name;
  int temp_signal, iteration = 0;
  while (iteration < available_networks)
  {
    for (int i = 1; i < available_networks; i++)
    {
      if (discoveredNetworks[i].Signal > discoveredNetworks[i - 1].Signal)
      {
        temp_name = discoveredNetworks[i - 1].Name;
        temp_signal = discoveredNetworks[i - 1].Signal;
        discoveredNetworks[i - 1].Name = discoveredNetworks[i].Name;
        discoveredNetworks[i - 1].Signal = discoveredNetworks[i].Signal;
        discoveredNetworks[i].Name = temp_name;
        discoveredNetworks[i].Signal = temp_signal;
      }
    }
    iteration++;
  }

  for (byte i = 0; i < available_networks; i++)
  {
    if (WiFi.SSID(i).equals(WIFI_ENDPOINT_NAME))
    {
      if (signalHistoryValues.size() >= SINGAL_GRAPH_SIZE)
      {
        signalHistoryValues.shift();
      }

      signalHistoryValues.add(reMap(WiFi.RSSI(i)));
      break;
    }
  }
}

char signalStr[8];
char networkName[16];
char numNetworks[1];
int chartValues[50];

int maxNumElements = 15;
int offset = 6;

void onSinglePress()
{
  byte available_networks = WiFi.scanNetworks();

  u8g2.clearBuffer();

  if (available_networks == 0)
  {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0, 0, "No Networks Found!");
    delay(1000);
    return;
  }

  get_and_sort_networks(available_networks);

  u8g2.setFont(u8g2_font_4x6_tf);

  // HEADER
  u8g2.drawStr(0, 6, "SIG");
  u8g2.drawStr(30, 6, "SSID");

  //Number of connected devices
  itoa(available_networks, numNetworks, 10);
  u8g2.drawStr(50, 6, numNetworks);

  u8g2.drawLine(0, 8, 63, 8);         //horizontal
  u8g2.drawLine(4 * 3, 0, 4 * 3, 70); //vertical

  // WIFI networks
  // for (int i = 0; i < _max(10, available_networks); i = i + 1)
  for (int i = 0; i < 10; i = i + 1)
  {
    memset(signalStr, 0, sizeof(signalStr));
    memset(networkName, 0, sizeof(networkName));

    itoa(discoveredNetworks[i].Signal, signalStr, 10);
    discoveredNetworks[i].Name.toCharArray(networkName, sizeof(networkName));

    int firstOffset = 2 + (i + 2) * offset + 1;

    u8g2.drawStr(0, firstOffset, signalStr);
    u8g2.drawStr(4 * 4 + 1, firstOffset, networkName);
  }

  // ------------- Draw graph -------------
  u8g2.drawFrame(0, 70, DISPLAY_W - 1, DISPLAY_H - 70);

  for (int i = 0; i < signalHistoryValues.size(); i++)
  {
    // drawPoint(i, signalHistoryValues.get(i));
    u8g2.drawPixel(i, DISPLAY_H - signalHistoryValues.get(i));
  }

  u8g2.sendBuffer();
}

void setup(void)
{
  u8g2.begin();
  Serial.begin(115200);

  //   button.onPressed(onSinglePress);
}

void loop()
{
  //   button.read();
  onSinglePress();
  // delay(200);
}

#endif