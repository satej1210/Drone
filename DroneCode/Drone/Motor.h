#ifndef Motor
const int defaultSpeed = 20;
#include <Servo.h> 
struct Motor{
  Servo esc;
  int esc_Pin;
  int current_Speed;
  int lowest_Speed;
  int highest_Speed;
  int start_Speed;
  int scale_step;
  int current_ms;
}Motors[4];
int thr;


 
//Create the 4 esc objects
Servo esc[4];
 
//Esc pins
int escPin[] = {7, 5, 6, 4};

//Min and max pulse
int minPulseRate        = 1000;
int maxPulseRate        = 2000;
int throttleChangeDelay = 5;
 
//SETUP


void stabilize(){
  if(thr > 24){
    
    Yaw = ypr[0];
    Pitch = ypr[1] * 180/M_PI;
    Roll = ypr[2] * 180/M_PI;
    int c = Pitch*1;
    int d = 0;
    int Limit = 5;
    
  while(Pitch < 0 && d < Limit){
    esc[0].write(thr - Pitch);
    esc[1].write(thr - Pitch);
   
    esc[2].write(c/10+thr);
    esc[3].write(c/10+thr);
     d++;
  }
  c = Pitch*1;
  while(Pitch > 0 && d < Limit){
    esc[2].write(thr-c);
    esc[3].write(thr-c);
    esc[0].write(thr + c / 10);
    esc[1].write(thr+c / 10);
    d++;
  }
  c = Roll*1;
  while(Roll > 0 && d < Limit){
    esc[1].write(thr-c);
    esc[2].write(thr-c);
    esc[0].write(thr+c/10);
    esc[3].write(thr+c/10);
    
    d++;

  }
  c = Roll*1;
  while(Roll < 0 && d < Limit){
    esc[0].write(thr-c);
    esc[3].write(thr-c);
    esc[1].write(thr+c/10);
    esc[2].write(thr+c/10);
    d++;
  }
  }
}
//Read the throttle value
int readThrottle(int i) {
  int throttle = esc[i].read();
  String x = "\"M";
  x += i+1;
  x += "\": ";
  x += throttle;
  appendSerialData(x);
  return throttle;
}

//Change velocity of the 4 escs at the same time
void writeTo4Escs(int throttle) {
  for(int i = 0; i < 4; ++i)
    esc[i].write(throttle);

}

//Init escs
void initEscs() {
  for(int i = 0; i < 4; ++i)
    esc[i].attach(escPin[i], minPulseRate, maxPulseRate);

  
  //Init motors with 0 value
  writeTo4Escs(0);
}

//Start the motors
void startUpMotors() {
  writeTo4Escs(50);
}
 
// Ensure the throttle value is between 0 - 180
int normalizeThrottle(int value) {
  if(value < 0) {
    return 0;
    
  } else if(value > 180) {
    return 180;
  }
  
  return value;
}
 
//Change throttle value
void changeThrottle(int throttle) {
  int currentThrottle = esc[0].read();
  
  int step = 1;
  if(throttle < currentThrottle) {
    step = -1;
  }
  
  // Slowly move to the new throttle value 
  while(currentThrottle != throttle) {
    writeTo4Escs(currentThrottle + step);
    
    currentThrottle = esc[0].read();
    delay(0);
  }
}
void MotorSetup() {
 
  Serial.setTimeout(500);
  
  //Init escs
  initEscs();
}
 
//LOOP
void runMotors() {
  // Wait for some input
  if (Serial.available() > 0) {
    
    // Read the new throttle value
    int throttle = normalizeThrottle(Serial.parseInt());
    thr = throttle;
    // Print it out
    Serial.print("Setting throttle to: ");
    Serial.println(throttle);
    
    // Change throttle to the new value
    changeThrottle(throttle);
  }
  for(int i = 0; i < 4; ++i)
  readThrottle(i);
}
#endif
