#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Wi-Fi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// DHT config
#define DHTPIN 2        // GPIO2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);

void handleRoot();
void handleMetrics();

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  // Define route
  server.on("/", handleRoot);
  server.on("/metrics", handleMetrics);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<meta http-equiv='refresh' content='5' />";
  html += "<title>Umbra's DHT11</title>";
  
  // Inline CSS for cyberpunk vibe
  html += "<style>";
  html += "body { background-color: #0f0f0f; color:#940711; font-family: monospace; text-align: center; padding: 20px; }"; 
  html += "h1 { color: #ff00ff; text-shadow: 0 0 5px #4507a3, 0 0 10px #ff00ff; }";
  html += "p { font-size: 1.5em; margin: 20px 0; }";
  html += ".card { border: 2px solid #00ffff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px #00ffff; display: inline-block; }";
  html += "</style>";
  html += "</head><body>";
  
  
  html += "<h1>😈My Room Sensor😈</h1>";
  html += "<div class='card'>";

  if (isnan(h) || isnan(t)) {
    html += "<p>⚠️ Sensor Error</p>";
  } else {
    html += "<p>🌡️ Temperature: <strong>" + String(t) + " °C</strong></p>";
    html += "<p>💧 Humidity: <strong>" + String(h) + " %</strong></p>";
    // Purple Digital clock
    html += "<iframe scrolling='no' frameborder='no' clocktype='html5' "
            "style='overflow:hidden;border:0;margin:0;padding:0;width:120px;height:40px;' "
            "src='https://www.clocklink.com/html5embed.php?clock=004&timezone=EET&color=purple&size=120&Title=&Message=&Target=&From=2025,1,1,0,0,0&Color=purple'>"
            "</iframe>";
    //link
    html += "<a href='https://open.spotify.com/playlist/6wGqdbUTSxF3CHsaGD7Zi2?si=c49b2b5cdba64dee' target='_blank' class='cyber-btn'>🎧 My Spotify Playlist</a>"; 


  }

  html += "</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
  }

  // Prometheus metrics
void handleMetrics() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  String metrics = "";
  if (!isnan(t)) metrics += "temperature_celsius " + String(t) + "\n";
  if (!isnan(h)) metrics += "humidity_percent " + String(h) + "\n";

  server.send(200, "text/plain", metrics);
}
