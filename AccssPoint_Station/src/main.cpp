#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Station Mode Credentials
const char* sta_ssid = ".";
const char* sta_password = "Sooner419abasss@";

// AP Mode Credentials
const char* ap_ssid = "ESP32_AP";
const char* ap_password = "12345678";

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

String getPage(String content) {
  String html = "<!DOCTYPE html><html><head>";
  // ... styling and navigation ...
  html += content;
  html += "</div></body></html>";
  return html;
}
void HomePage() {
  String content = "<h1>Welcome to ESP32 Web Server</h1>";
  // ... page content ...
  server.send(200, "text/html", getPage(content));
}

bool is_authenticated() {
  if (!server.authenticate("admin", "admin")) {
    server.requestAuthentication();
    return false;
  }
  return true;
}



void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_AP_STA);  // Enable both AP and Station modes
  WiFi.softAP(ap_ssid, ap_password);  // Start the access point
  WiFi.begin(sta_ssid, sta_password); // Connect to existing network
  server.on("/power", HomePage);
  server.on("/", HomePage);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

