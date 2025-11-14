# Umbra's DHT11 ESP8266
<img width="1141" height="463" alt="image" src="https://github.com/user-attachments/assets/c5b00bd2-c114-4b65-85f5-f52b13632767" />

This is my first project using a DHT11 sensor with ESP8266, featuring a dark aesthetic minimalistic style. 

The ESP8266 serves a simple web page displaying **temperature** and **humidity** with a cyberpunk-inspired style.  
It also exposes a **Prometheus metrics endpoint** for monitoring purposes.

## Features
- 🌡️ Temperature and 💧 Humidity readings
- 🖤 Dark, minimalistic web interface
- 🔄 Auto-refresh every 5 seconds
- 📊 Prometheus metrics at `/metrics`
- 🎧 Optional Spotify playlist link embedded
- ⏱️  Uses [Clocklink.com]([clocklink.com](https://www.clocklink.com/gallery/view/html5-004)) for a digital clock (GMT+2 by default; you can add your own clock if you want :D)

## Hardware
- ESP8266 (NodeMCU, Wemos D1 Mini)
- DHT11 sensor connected to GPIO2

## Usage
1. Update your Wi-Fi credentials in `DHT11.ino`:
```cpp
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

2. Flash the sketch to your ESP8266.
3. Open the IP printed in the Serial Monitor in your browser.
