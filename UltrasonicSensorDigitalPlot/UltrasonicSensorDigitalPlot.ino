const int trigPin = 9;
const int echoPin = 10;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration;
  float distance;

  // TRIGパルス送信
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // 距離計算(cm)
  distance = duration * 0.0343 / 2.0;

  Serial.println(distance);

  delay(50);
}
