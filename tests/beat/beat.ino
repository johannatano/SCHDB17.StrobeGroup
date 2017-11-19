
int LED_PIN = 13;
int MIC_PIN = A1;


float freq_offset = 0;

float spin_dir = 1;
float beatDetect_time = 0;
float startLoop_time;

bool is_beat = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MIC_PIN, INPUT);
  
}

void loop() {

  //save startTime of program
  startLoop_time = micros();

  
  digitalWrite(LED_PIN, LOW);

    float beatDur = 200;
    float timeSinceBeat = (startLoop_time - beatDetect_time)/1000;
    if(timeSinceBeat > beatDur){
      is_beat = false;
    }
     while(micros() - startLoop_time < 5 * 1000){
      float val = analogRead(MIC_PIN);
      
      if(val > 500){
        if(!is_beat){
          if(spin_dir > 0){
            spin_dir = -1;
          }else{
            spin_dir = 1;
          }
          beatDetect_time = micros();
        }
        
        is_beat = true;
      }
       delayMicroseconds(500);
     }
     if(is_beat){
      freq_offset = 0;
     }else{
      freq_offset = spin_dir * 0.75;
     }

  
  float f = 40 + freq_offset;
  float lightTime = 400;  
  float runTime = (micros() - startLoop_time) / 1000;
  float millisDelay = ((1000/f) ) - (lightTime/1000) - runTime;
  float microDelay = (millisDelay - floor(millisDelay)) * 1000;

  
  delay(floor(millisDelay));
  delayMicroseconds(round(microDelay));

  float lightStart = micros();
  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(lightTime);


  //check to see total dur of program to match freq
  //Serial.println(micros() - startLoop_time);
}
