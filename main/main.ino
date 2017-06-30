#define redLed 2
#define buzzer 7
#define button 13
int greenLed[]={3,5,9};
int sound[]={A0,A1};
int onLed=0;
int freq=0;
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
  //tone(buzzer,1000);
  
  
  

}

void loop() {
  delay(200);
  if(digitalRead(button)==HIGH)
  right=!right;
  flashLights(right);
 

}
//parameter is direction. Call every loop
void flashLights(boolean dir){
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
