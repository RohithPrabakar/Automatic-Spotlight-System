int led = LED_BUILTIN;
int sensor0 = A0;
int sensor1 = A1;
void setup() {
  pinMode(sensor0, INPUT);
  pinMode(sensor1, INPUT);
  Serial.begin(9600);
}
void loop() {
  int sensorval0 = analogRead(sensor0);
  int sensorval1 = analogRead(sensor1);
  /* for PIR sensor 1 input*/
  if (sensorval0 > 234) {
    Serial.print(1);
    Serial.print(',');
  }
  if (sensorval0 < 234) {
    Serial.print(0);
    Serial.print(',');
  }
if (sensorval1 > 234) {
    Serial.println(1);
  }
if (sensorval1 < 234){
    Serial.println(0);
  }
  delay(10);
}
