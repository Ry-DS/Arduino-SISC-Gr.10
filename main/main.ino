#define redLed 2
#define buzzer 7
#define button 13

int greenLed[]={3,5,9};
int sound[]={A0,A1};
boolean distressMode=true;


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
  
  
  

}

void loop() {
  delay(7);
  if(digitalRead(button)==HIGH)
  right=!right;
  if(distressMode){
  flashLights(right);
  //siren(); off cause ANNOYING
  }
  else{}//TODO make detection mode for distress. 
  
 

}

int onLed=0;
long timer=0;
//parameter is direction. Call every loop
void flashLights(boolean dir){
  if(millis()-timer>=200){timer=millis();}
  else return;
  int size=sizeof(greenLed);
  digitalWrite(redLed,HIGH);
  for(int i=0;i<size;i++){
    
  digitalWrite(greenLed[i],LOW);}
  digitalWrite(greenLed[onLed],HIGH);
  
  if(dir)
  onLed++;
  else onLed--;
  size--;
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
