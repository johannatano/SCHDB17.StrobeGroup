
#include <TM1637Display.h>

int LED_PIN = 13;
int PWN_PIN_TRIG = 5;
int PWN_PIN_ECHO = 6;
int BTN_PIN = 7;
int MIC_PIN = A5;
int POT_PIN = A0;
int CLK = 9;
int DIO = 8;

float FREQ_BASE = 36;
float FREQ_SPAN = 1;
float LIGHT_TIME = 500;
float freq_offset;

int state_index = 1;

int STATE_SONAR = 0;
int STATE_POT = 1;
int STATE_MIC = 2;

int spinDir = 1;
int beatDetect_time = 0;

bool is_beat;

unsigned int sample;

TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  pinMode(PWN_PIN_TRIG, OUTPUT);
  pinMode(PWN_PIN_ECHO, INPUT);

  pinMode(BTN_PIN, INPUT);
  pinMode(MIC_PIN, INPUT);
 
  
  display.setBrightness(0x0a);
  
}

void loop() {
  
//  float startLoop_time = millis();
//  
//  int btnVal = digitalRead(BTN_PIN);
//
//
//  bool isStateChange = false;
//  if(btnVal == HIGH){
//
//    isStateChange = true;
//    freq_offset = 0;
//    
//    state_index++;
//    if(state_index >= 3) state_index = 0;
//    /*while(digitalRead(BTN_PIN)){
//      delay(100);
//    }*/
//     
//  }
//
// 
//  float potVal;
//  float micVal;
//  
//  float maxVal;
//  float minVal;
//  
//  float sonarVal;
//  
//  switch(state_index){
//    case 0:
//      sonarVal = ping();
//      maxVal = 100;
//      minVal = 30;
//      sonarVal = max(sonarVal, minVal);
//      sonarVal = min(sonarVal, maxVal);
//      freq_offset = map(sonarVal, minVal, maxVal, -1000, 1000);
//     break;
//
//     case 1:
//       potVal = analogRead(POT_PIN);
//       freq_offset = map(potVal, 0, 1023, -1000, 1000);
//
//       //Serial.println(freq_offset);
//      break;
//
//     case 2:
//      break;
//  }
//
//  int f = ((FREQ_BASE - ( (freq_offset/1000) * FREQ_SPAN ))) * 100;
//  //display.showNumberDec(f);
//
//  if(startLoop_time - beatDetect_time > 300){
//    is_beat = false;
//  }
//  
//  
//  float delay_seconds;
//  float delay_millis;
//
//  //Calc how long time since start of loop
//  float programDur_time = millis() - startLoop_time;
//  
//
//  //calc how much longer delay we need, to match freq
//  delay_seconds = (1/(FREQ_BASE - ( (freq_offset/1000) * FREQ_SPAN ))) - (LIGHT_TIME/1000000) - (programDur_time/1000);
//
//
//  //Make sure delay is between 0 - 1000ms
//  //delay_millis = max(delay_seconds * 1000, 0);
//  //delay_millis = min(delay_millis, 1000);
//
//
//  //Serial.println(delay_seconds);
//  
//  
//  if(state_index == STATE_MIC){
//    
//    float safeMargin = 3;
//
//    /*while(millis() - nTime + safeMargin <  dMillis ){
//      if(!isBeat && beatDetect(analogRead(MIC_PIN))){
//        isBeat = true;
//        Serial.println("BEAT DETECTED");
//        beatTime = millis();
//        if(spinDir > 0) spinDir = -1;
//        else spinDir = 1;
//        
//      }
//    }*/
//
//    //float diff = (dTime * 1000) - (millis() - nTime);
//    //value = isBeat ? 1000 : 0;
//    //value = 0;
//    //Serial.println(diff);
//   // delay(diff);
//  }else{
//    //dTime = (1/(frequency + ( (value/1000)*freqSpan ))) - (lightTime/1000000) - (dur/1000);
//  }

  digitalWrite(LED_PIN, LOW);

  //display.showNumberDec(15);
  
  delay(27);
  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(500);
}


bool beatDetect(int val){
  if(val > 670) return true;
  return false;
}


long ping(){
  // establish variables for duration of the ping, 
  // and the distance result in centimeters:
  long duration, distance;
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(PWN_PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PWN_PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PWN_PIN_TRIG, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(PWN_PIN_ECHO, HIGH);
  distance = microsecondsToCentimeters(duration);
  return distance;
}


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
