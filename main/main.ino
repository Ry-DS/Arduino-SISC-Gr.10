#define redLed 2
#define buzzer 7
#define button 13

int greenLed[]={3,5,9,11};
int sound[]={A0,A1,A2};
boolean distressMode=false;


boolean right=true;
boolean prevButton=false;


void setup() {
  Serial.begin(9600);
  pinMode(redLed,OUTPUT);
  pinMode(buzzer,OUTPUT);
  for(int i=0;i<4;i++){
  pinMode(greenLed[i],OUTPUT);}
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);
  Serial.println("Done setting up Ports");
  tone(buzzer,4000);
  delay(500);
  noTone(buzzer);
  digitalWrite(redLed,HIGH);
  
  
  

}

void loop() {
  delay(7);
  
  if(distressMode){
     
  flashLights(right);
  siren(); 
  
  }
  else{
    digitalWrite(redLed,HIGH);
    for(int i=0;i<4;i++){
    
    digitalWrite(greenLed[i],LOW);}
    distressMode=checkDistress();


    
    }//TODO make detection mode for distress.
  
  checkButton();//TODO Change to stop distress after checkDistress works. Also make button press logic better
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
  if(digitalRead(button)==HIGH&&!prevButton){
  distressMode=false;
  tone(buzzer,6000);
  delay(200);
  prevButton=true;
  }
  if(digitalRead(button)==LOW&&prevButton)
  prevButton=false;
 }

int onLed=0;
long timer=0;
//parameter is direction. Call every loop
void flashLights(boolean dir){
  if(millis()-timer>=200){timer=millis();}
  else return;
  
 
  for(int i=0;i<4;i++){
    
  digitalWrite(greenLed[i],LOW);}
  digitalWrite(greenLed[onLed],HIGH);
  
  if(dir)
  onLed++;
  else onLed--;
  
  if(onLed>3)onLed=0;
  if(onLed<0)onLed=3;

  
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
