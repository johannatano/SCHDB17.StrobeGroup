


float value; //save analog value
int LED_PIN = 13;

float frequency = 40;
float freqSpan = 2;
float lightTime = 5;
void setup() {
  Serial.begin(9600);
  //pinMode(A0, INPUT); //Optiona
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  value = analogRead(A0);
  value = map(value, 0, 1023, -1000, 1000);
  
  float dTime = (1/(frequency- ( (value/1000)*freqSpan ))) - (lightTime/1000000);
  
  digitalWrite(LED_PIN, LOW);
  delay(dTime*1000);

  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(lightTime);
  
  //Serial.println(dTime*1000);

  Serial.println((frequency- ( (value/1000)*freqSpan )));
}
