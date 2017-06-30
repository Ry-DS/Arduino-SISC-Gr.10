#define redLed 2
#define buzzer 7
#define button 13
int greenLed[]={3,5,9};
int onLed=0;
boolean right=false;
void setup() {
  Serial.begin(9600);
  pinMode(redLed,OUTPUT);
  for(int i=0;i<sizeof(greenLed);i++){
  pinMode(greenLed[i],OUTPUT);}
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT);
  Serial.println("Done setting up Ports");
  
  
  

}

void loop() {
  delay(200);
  digitalWrite(redLed,HIGH);
  for(int i=0;i<sizeof(greenLed);i++){
    
  digitalWrite(greenLed[i],LOW);}
  digitalWrite(greenLed[onLed],HIGH);
  if(digitalRead(button)==HIGH)
  right=!right;
  if(right)
  onLed++;
  else onLed--;
  if(onLed>2)onLed=0;
  if(onLed<0)onLed=2;
 

}
