
// #include <Arduino.h>

// #define LED 2

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(115200);
//   pinMode(LED, OUTPUT);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   digitalWrite(LED, HIGH);
//   Serial.println("LED is on");
//   delay(1000);
//   digitalWrite(LED, LOW);
//   Serial.println("LED is off");
//   delay(1000);
// }

// WiFi credentials
#define WIFI_SSID "Your WiFi SSID"
#define WIFI_PASSWORD "Your WiFi Password"

// LED pin
#define LED_PIN

// Web server object
AsyncWebServer server(80);

// LED state
int LED_state = LOW;

// Function to generate the HTML and CSS code for the web page
String getHTML() {
  String html = "<!DOCTYPE HTML>";
  html += "<html>";
  html += "<head>";
  html += "<style>";
  html += "body {background-color: #F0F0F0; font-family: Arial, Helvetica, sans-serif;}";
  html += "h1 {color: #333333; text-align: center;}";
  html += "button {width: 150px; height: 50px; font-size: 20px; margin: 10px;}";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>ESP32 Web Server</h1>";
  html += "<p>LED state: <span style='color: red;'>";
  if (LED_state == LOW) html += "OFF";
  else html += "ON";
  html += "</span></p>";
  html += "<button onclick=\"window.location.href='/led/on'\">Turn ON</button>";
  html += "<button onclick=\"window.location.href='/led/off'\">Turn OFF</button>";
  html += "</body>";
  html += "</html>";
  return html;
}

// Function to connect to WiFi network
void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to handle HTTP requests
void handleRequest(AsyncWebServerRequest *request) {
  // Get the request path
  String path = request->url();
  // Check if the request is to turn the LED on
  if (path == "/led/on") {
    // Set the LED pin to HIGH
    digitalWrite(LED_PIN, HIGH);
    // Update the LED state
    LED_state = HIGH;
    // Send a confirmation message
    request->send(200, "text/plain", "LED turned on");
  }
  // Check if the request is to turn the LED off
  else if (path == "/led/off") {
    // Set the LED pin to LOW
    digitalWrite(LED_PIN, LOW);
    // Update the LED state
    LED_state = LOW;
    // Send a confirmation message
    request->send(200, "text/plain", "LED turned off");
  }
  // Otherwise, send the web page
  else {
    // Get the HTML and CSS code
    String html = getHTML();
    // Send the web page
    request->send(200, "text/html", html);
  }
}

void setup() {
  // Initialize the serial monitor
  Serial.begin(115200);

  // Initialize the LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_state);

  // Connect to WiFi network
  connectWiFi();

  // Start the web server
  server.onNotFound(handleRequest);
  server.begin();
}

void loop() {
  // Nothing to do here
}
