
int LED_PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  
}

void loop() {


  float startTime = micros();
  float f = 40;
  float lightTime = 400;
  
  digitalWrite(LED_PIN, LOW);
  
  float millisDelay = ((1/f) * 1000 ) - (lightTime/1000);
  float microDelay = (millisDelay - floor(millisDelay)) * 1000;

 
  delay(floor(millisDelay));
  delayMicroseconds(round(microDelay));
  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(lightTime);


  //Serial.println(microDelay);
  //Serial.println((microDelay/1000) + (lightTime/1000) + floor(millisDelay));
}


