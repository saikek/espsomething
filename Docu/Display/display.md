# Display information

I found this relatively cheap display for $1.79 for screen and $2.62. (May 2020) with resolution of 160x128, SPI interface 3.3V logic and backlight.

# WIRING

| Display Pin | ESP Pin | Description                |
|-------------|---------|----------------------------|
| LED         | 3.3V    | Backlight power, 3.3V      |
| SCK         | 18      | SCLK - Clock OUT           |
| SDA         | 23      | MOSI                       |
| A0          | 19      | DC, can be any pin         |
| RESET       | 3.3V    | 3.3V or IC pin for control |
| CS          | 5       | Chip Select                |
| GND         | GND     | Ground pin                 |
| VCC         | 3.3V    | IC Power, 3.3V             |

# Links
[Wiki page](http://www.lcdwiki.com/1.8inch_Arduino_SPI_Module_ST7735S_SKU:MAR1801)
[Ali page with description](https://www.aliexpress.com/item/32841982669.html)