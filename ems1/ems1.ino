#include <TimerOne.h>
#include <SPI.h>
#define SONAR_IN_PIN A0
#define BJT_OUT_PIN 3
#define SONAR_READ analogRead(A0)
#define TIMER_INTERRUPT 10
#define CS_PIN 10
#define M1_LEVEL_0 0 //we need to fill in here after calibration
#define M1_LEVEL_1 0
#define M1_LEVEL_2 0
#define M1_LEVEL_3 0
#define M1_LEVEL_4 0
#define M1_LEVEL_5 0
#define M1_LEVEL_6 0
#define M1_LEVEL_7 0
#define M1_LEVEL_8 0
#define M1_LEVEL_9 0
#define M1_LEVEL_10 0

uint8_t pulse_width =200; //u sec
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

void MCP41010Write(byte value)
{
   digitalWrite(CS_PIN,LOW); // select the chip
   SPI.transfer(B00010001); // command byte
   SPI.transfer(value); // data byte 
   digitalWrite(CS_PIN,HIGH); // de-select the chip
}

void setup() {
  pinMode(BJT_OUT_PIN,OUTPUT);
  Serial.begin(9600);
  Timer1.initialize(TIMER_INTERRUPT);
  Timer1.attachInterrupt(process); 
  SPI.begin();
}

void loop() {
  
  Serial.println(SONAR_READ);
  //MCP41010Write(255);
  delay(100);

}
