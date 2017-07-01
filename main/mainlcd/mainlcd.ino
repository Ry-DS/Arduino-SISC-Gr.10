#include <LiquidCrystal.h>

#define redLed 2
#define buzzer 3
//#define button 13
int btnRIGHT  =0;
int btnUP     =1;
int btnDOWN   =2;
int btnLEFT   =3;
int btnSELECT =4;
int btnNONE   =5;

int read_buttons(){               // read the buttons
  int adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  

   // For V1.0 comment the other threshold and use the one below:
   /*
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
   */

    return btnNONE;                // when all others fail, return this.
}

int greenLed[]={11,12,13};
int sound[]={A0,A1,A2};
boolean distressMode=false;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
boolean right=true;
boolean prevButton=false;


void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(redLed,OUTPUT);
  pinMode(buzzer,OUTPUT);
  for(int i=0;i<6;i++){
  pinMode(greenLed[i],OUTPUT);}
  pinMode(buzzer,OUTPUT);
  //pinMode(button,INPUT);
  Serial.println("Done setting up Ports");
  tone(buzzer,4000);
  delay(500);
  noTone(buzzer);
  digitalWrite(redLed,HIGH);
  
  
  

}

void loop() {
  delay(7);
  
  if(distressMode){
     
  //flashLights(right);
  siren(); 
  
  }
  else{
    digitalWrite(redLed,HIGH);
    for(int i=0;i<6;i++){
    
    digitalWrite(greenLed[i],LOW);}
    distressMode=checkDistress();


    
    }//TODO make detection mode for distress.
  
 // checkButton();//TODO Change to stop distress after checkDistress works. Also make button press logic better
  if(!distressMode)
  
  noTone(buzzer); 
  else flashRedLed();
  
 

}
boolean checkDistress(){//TODO
  int soundVals[]={analogRead(A0),analogRead(A1),analogRead(A2)}; //0 is left, 1 is middle, 2 is right
  int flame[]={analogRead(A3),analogRead(A4)};//a3 is left a4 is right
 
  if(flame[0]>=100){right=false;return true;}
  if(flame[1]>=100){right=true;return true;}
  if(soundVals[0]>=100&&soundVals[1]>=50&&soundVals[2]>=100){
    if(soundVals[0]>soundVals[2])right=false;
    else right=true;
    Serial.println("Informed decision had to be made!");
    return true;
    }
  if(soundVals[0]>=100&&soundVals[1]>=50){right=false;return true;}
  if(soundVals[2]>=100&&soundVals[1]>=50){right=true;return true;}
    

  return false;
  
 }
long timerbutton=0;
void checkButton(){
 // Serial.println(right);
  //if(millis()-timerbutton>5)timerbutton=millis();
  //else return;
  if(read_buttons()==btnSELECT&&!prevButton){
  distressMode=false;
  tone(buzzer,6000);
  delay(200);
  prevButton=true;
  }
  if(read_buttons()==btnNONE&&prevButton)
  prevButton=false;
 }

int onLed=0;
long timer=0;
//parameter is direction. Call every loop
void flashLights(boolean dir){
  if(millis()-timer>=200){timer=millis();}
  else return;
  
 
  for(int i=0;i<6;i++){
    
  digitalWrite(greenLed[i],LOW);}
  digitalWrite(greenLed[onLed],HIGH);
  
  if(dir)
  onLed++;
  else onLed--;
  
  if(onLed>5)onLed=0;
  if(onLed<0)onLed=5;

  
  }

  
 boolean rise=true;
 const int FREQ_TOP=5000;
 const int FREQ_BOT=2000;
 int freq=2000;
//turn off with noTone(buzzer)
void siren(){

if(freq>FREQ_TOP)rise=false;
else if(freq<FREQ_BOT)rise=true;
if(rise) freq+=10;
else freq-=10;
tone(buzzer,freq);
//Serial.println(freq);


  
}


long redtimer=0;
boolean on=false;
void flashRedLed(){
  if(millis()-redtimer>200){redtimer=millis();}
  else return;
  if(on)
  digitalWrite(redLed,HIGH);
  else digitalWrite(redLed,LOW);
  on=!on;
  
  
  }
