#define redLed 2
#define buzzer 7
#define button 13
int greenLed[]={3,5,9};
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
  digitalWrite(redLed,HIGH);
  for(int i=0;i<sizeof(greenLed);i++){
  digitalWrite(greenLed[i],HIGH);}
 

}
