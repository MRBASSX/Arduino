
void glow(int LED,int high,int low){
    Serial.begin(115200);
    digitalWrite(LED,high);
    Serial.println("LED is on");
    delay(100);
    digitalWrite(LED,low);
    Serial.println("LED is off");
    delay(100);


    
  
  }

