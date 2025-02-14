


#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Firebase.h>
#include <Firebase_ESP_Client.h>

/* Put your SSID & Password */
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "123456789";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t LED1pin = 2;
bool LED1status = LOW;

uint8_t LED2pin = 2;
bool LED2status = LOW;
 
 // Provide the token generation process info.
 #include <addons/TokenHelper.h>
 
 // Provide the RTDB payload printing info and other helper functions.
 #include <addons/RTDBHelper.h>
 
 /* 1. Define the WiFi credentials */
//  #define WIFI_SSID "ESP32"
//  #define WIFI_PASSWORD "123456789"


 
 // For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino
 
 /* 2. Define the API Key */
 #define API_KEY "AIzaSyCKMN2pLzuy5DBLTXsOjH10kg4hUgWRvpo"
 
 /* 3. Define the RTDB URL */
 #define DATABASE_URL "fir-iot-e9926-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
 
 /* 4. Define the user Email and password that alreadey registerd or added in your project */
 #define USER_EMAIL "admin@gmail.com"
 #define USER_PASSWORD "admin12345@"
 
 // Define Firebase Data object
 FirebaseData fbdo;
 FirebaseAuth auth;
 FirebaseConfig config;
 unsigned long sendDataPrevMillis = 0;
 unsigned long count = 0;
 

 
 void setup()
 {
  
   Serial.begin(115200);
   pinMode(LED1pin, OUTPUT);
   pinMode(LED2pin, OUTPUT);
   WiFi.softAP(ssid, password);
   WiFi.softAPConfig(local_ip, gateway, subnet);
   WiFi.begin(ssid, password);
 

   Serial.print("Connecting to Wi-Fi");
   unsigned long ms = millis();
   while (WiFi.status() != WL_CONNECTED)
   {
     Serial.print(".");
     delay(300);
   }
   Serial.println();
   Serial.print("Connected with IP: ");
   Serial.println(WiFi.localIP());
   Serial.println();
 
   Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
 
   /* Assign the api key (required) */
   config.api_key = API_KEY;
 
   /* Assign the user sign in credentials */
   auth.user.email = USER_EMAIL;
   auth.user.password = USER_PASSWORD;
 
   /* Assign the RTDB URL (required) */
   config.database_url = DATABASE_URL;
 
   /* Assign the callback function for the long running token generation task */
   config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

   // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
   Firebase.reconnectNetwork(true);
 
   // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
   // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
   fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
 
   // Limit the size of response payload to be collected in FirebaseData
   fbdo.setResponseSize(2048);
 
   Firebase.begin(&config, &auth);

   Firebase.setDoubleDigits(5);
 
   config.timeout.serverResponse = 10 * 1000;
 
   
 }
 
 void loop()
 {
 
   // Firebase.ready() should be called repeatedly to handle authentication tasks.
 
   if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
   {
     sendDataPrevMillis = millis();
 
     Serial.printf("Set bool... %s\n", Firebase.RTDB.setBool(&fbdo, F("/test/bool"), count % 2 == 0) ? "ok" : fbdo.errorReason().c_str());
 
     Serial.printf("Get bool... %s\n", Firebase.RTDB.getBool(&fbdo, FPSTR("/test/bool")) ? fbdo.to<bool>() ? "true" : "false" : fbdo.errorReason().c_str());
 
     bool bVal;
     Serial.printf("Get bool ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/test/bool"), &bVal) ? bVal ? "true" : "false" : fbdo.errorReason().c_str());
 
     Serial.printf("Set int... %s\n", Firebase.RTDB.setInt(&fbdo, F("/test/int"), count) ? "ok" : fbdo.errorReason().c_str());
 
     Serial.printf("Get int... %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/int")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
 
     int iVal = 0;
     Serial.printf("Get int ref... %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/int"), &iVal) ? String(iVal).c_str() : fbdo.errorReason().c_str());
 
     Serial.printf("Set float... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/test/float"), count + 10.2) ? "ok" : fbdo.errorReason().c_str());
 
     Serial.printf("Get float... %s\n", Firebase.RTDB.getFloat(&fbdo, F("/test/float")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());
 
     Serial.printf("Set double... %s\n", Firebase.RTDB.setDouble(&fbdo, F("/test/double"), count + 35.517549723765) ? "ok" : fbdo.errorReason().c_str());
 
     Serial.printf("Get double... %s\n", Firebase.RTDB.getDouble(&fbdo, F("/test/double")) ? String(fbdo.to<double>()).c_str() : fbdo.errorReason().c_str());
 
     Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("Hello World!")) ? "ok" : fbdo.errorReason().c_str());
 
     Serial.printf("Get string... %s\n", Firebase.RTDB.getString(&fbdo, F("/test/string")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
 
     // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create_Edit_Parse.ino
     FirebaseJson json;
 
    //  if (count == 0)
    //  {
    //    json.set("value/round/" + String(count), F("cool!"));
    //    json.set(F("value/ts/.sv"), F("timestamp"));
    //    Serial.printf("Set json... %s\n", Firebase.RTDB.set(&fbdo, F("/test/json"), &json) ? "ok" : fbdo.errorReason().c_str());
    //  }
    //  else
    //  {
    //    json.add(String(count), F("smart!"));
    //    Serial.printf("Update node... %s\n", Firebase.RTDB.updateNode(&fbdo, F("/test/json/value/round"), &json) ? "ok" : fbdo.errorReason().c_str());
    //  }
 
     Serial.println();

     count++;
   }
 }
 
 