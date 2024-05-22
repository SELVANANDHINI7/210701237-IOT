const int trigPin=12;
const int echoPin=8;

float duration;
float distance;
const int height = 100;
float threshold;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  threshold=height*0.20;
  if(distance<=threshold){
    Serial.print("Full and distance is : ");
    Serial.println(distance);
  }
  delay(2000);
}