#include <TimerOne.h>
#define SONAR_IN_PIN A0
#define BJT_OUT_PIN 3
#define SONAR_READ analogRead(A0)
#define TIMER_INTERRUPT 10
uint8_t pulse_width = 200; //u sec
long freq_inv = 1282051 ; // in us

long high_state = pulse_width;
long low_state = freq_inv - high_state;
uint8_t countStep = 14;
long count_out_ems = 0;
uint8_t pulse_forward_state_high = 0;
uint8_t pulse_forward_state_low = 1;
void process(){
 count_out_ems+=countStep;
 if (count_out_ems > freq_inv) count_out_ems = 0;
 if ((count_out_ems >=0) && (count_out_ems<=high_state)){
  //output high state here
  digitalWrite(BJT_OUT_PIN,HIGH);
 }
 else
 if ((count_out_ems >high_state) && (count_out_ems<=freq_inv)){
  //output low state
  digitalWrite(BJT_OUT_PIN,LOW);
 }
}

void setup() {
  pinMode(BJT_OUT_PIN,OUTPUT);
  Serial.begin(9600);
  Timer1.initialize(TIMER_INTERRUPT);
  Timer1.attachInterrupt(process); 
}

void loop() {
  
  Serial.println(SONAR_READ);
  delay(100);

}
