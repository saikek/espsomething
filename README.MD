# ESP-O-MATIC


Few questions that I need answers for:

# Software:

## Wifi

### [Client] Is it possible to scan for available wifi networks
Yes, there is a function to scan for networks, you can see type of networks and see signal strength. See [example][https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/scan-examples.html]

### [Server] Getting information about surrounding clients even before they had conencted to endpoint
Apparently it is possible to track if your endpoint is being probed (even before connection was establised).
There is and event `WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestPrint);` that tells you what endpoint was trying to probe your host. 

Parameters are MAC and RSSI.

See [Association explained][https://documentation.meraki.com/MR/WiFi_Basics_and_Best_Practices/802.11_Association_process_explained]


### Getting RSSI of already connected clients


### How can you use Wifi in both endpoint and station mode

### Is it possible to put interrupt on acceleromer

### Is it possible to get noise level from microphone without too much processing power

### How to produce sound using buzzer

### How to control buzzer volume

### How to vibrate with motor

### How to add menu system

### How to adjust backlight brightness 




# Hardware (Remember JLPCB can only make one side and SMD components only):

### Display connection - cheapest and most convinient

