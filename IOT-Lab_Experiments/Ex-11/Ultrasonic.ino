int echo = 8, trig = 12;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delay(2000);
  digitalWrite(trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(trig, LOW);
  float time;
  time = pulseIn(echo,HIGH);
  float distance = (time * 0.017);
  Serial.print("Distance :");
  Serial.println(distance);
  delay(1000);
}
