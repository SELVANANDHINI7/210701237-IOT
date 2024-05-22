int pirpin = 12;
int buzzerpin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(pirpin,INPUT);
  pinMode(buzzerpin,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int motion = digitalRead(pirpin);
  if(motion==HIGH){
    digitalWrite(buzzerpin,HIGH);
    delay(2000);
    digitalWrite(buzzerpin, LOW);
  }
}
