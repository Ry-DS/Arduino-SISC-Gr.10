#define redLed 2
#define buzzer 7
#define button 13

int greenLed[]={3,5,9};
int sound[]={A0,A1,A2};
boolean distressMode=false;


boolean right=false;


void setup() {
  Serial.begin(9600);
  pinMode(redLed,OUTPUT);
  pinMode(buzzer,OUTPUT);
  for(int i=0;i<sizeof(greenLed);i++){
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
    for(int i=0;i<3;i++){
    
    digitalWrite(greenLed[i],LOW);}
    distressMode=checkDistress();


    
    }//TODO make detection mode for distress.
  
  checkButton();//TODO Change to stop distress after checkDistress works. Also make button press logic better
  if(!distressMode)
  noTone(buzzer); 
  else flashRedLed();
 

}
boolean checkDistress(){//TODO
  int soundVals[]={analogRead(sound[0]),analogRead(sound[1]),analogRead(sound[2])}; 
  int flame=analogRead(A3);
 Serial.print(soundVals[0]);
 Serial.print(" ");
 Serial.print(soundVals[1]);
 Serial.print(" ");
 Serial.println(soundVals[2]);
  return false;
  
 }
long timerbutton=0;
void checkButton(){
  if(millis()-timerbutton>200)timerbutton=millis();
  else return;
  if(digitalRead(button)==HIGH)
  distressMode=!distressMode;
 }

int onLed=0;
long timer=0;
//parameter is direction. Call every loop
void flashLights(boolean dir){
  if(millis()-timer>=200){timer=millis();}
  else return;
  
 
  for(int i=0;i<3;i++){
    
  digitalWrite(greenLed[i],LOW);}
  digitalWrite(greenLed[onLed],HIGH);
  
  if(dir)
  onLed++;
  else onLed--;
  
  if(onLed>2)onLed=0;
  if(onLed<0)onLed=2;

  
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
