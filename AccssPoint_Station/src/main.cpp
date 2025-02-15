#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Station Mode Credentials
// const char* sta_ssid = ".";
// const char* sta_password = "Sooner419abasss@";

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
  // ... styling and Links ...
  html += "<style>";
  html += ".menu {height:200px;background:blue;color:white}\n";
  html += "</style>";
  html += "</head>";

  html += "<nav class=\"menu\">\n";
   // ...navigation  
  html += "</nav>";

  html += "<div>";
  html += content;
  html += "</div>";

  html += "<footer>";
  //......and footer...
  html += "<ul> <li> Footer</li> </ul>";
  html += "</footer>";

  html += "</body></html>";
  return html;
}
void HomePage() {
  String content = "<h1>Welcome to ESP32 Web Server</h1>";
  // ... page content ...
  server.send(200, "text/html", getPage(content));
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
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
  // WiFi.mode(WIFI_AP_STA);  // Enable both AP and Station modes
  WiFi.softAP(ap_ssid, ap_password);  // Start the access point
  // WiFi.begin(sta_ssid, sta_password); // Connect to existing network
  
  server.on("/power", HomePage);
  server.on("/", HomePage);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

