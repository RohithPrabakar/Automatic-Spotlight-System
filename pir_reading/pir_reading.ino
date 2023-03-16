int led = LED_BUILTIN;
int sensor0 = A0;
int sensor1 = A1;
int sensor2 = A2;
int sensor3 = A3;
int sensor4 = A4;
int sensor5 = A5;

void setup() {
  pinMode(sensor0, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  Serial.begin(9600);
}
void loop() {
  int sensorval0 = analogRead(sensor0);
  int sensorval1 = analogRead(sensor1);
  int sensorval2 = analogRead(sensor2);
  int sensorval3 = analogRead(sensor3);
  int sensorval4 = analogRead(sensor4);
  int sensorval5 = analogRead(sensor5);
  /* for PIR sensor 1 input*/
//   if (sensorval0 > 234) {
//     Serial.print(1);
//     Serial.print(',');
//   }
//   if (sensorval0 < 234) {
//     Serial.print(0);
//     Serial.print(',');
//   }

//  /* for PIR sensor 2 input*/
//   if(sensorval1 > 234) {
//     Serial.print(1);
//     Serial.print(',');
//   }
//   if (sensorval1 < 234){
//     Serial.print(0);
//     Serial.print(',');
//   }

//  /* for PIR sensor 3 input*/
//   if(sensorval2 > 234) {
//     Serial.print(1);
//     Serial.print(',');
//   }
//   if (sensorval2 < 234){
//     Serial.print(0);
//     Serial.print(',');
//   }

//  /* for PIR sensor 4 input*/
//   if(sensorval3 > 234) {
//     Serial.print(1);
//     Serial.print(',');
//   }
//   if (sensorval3 < 234){
//     Serial.print(0);
//     Serial.print(',');
//   }

//  /* for PIR sensor 5 input*/
//   if(sensorval4 > 234) {
//     Serial.print(1);
//     Serial.print(',');
//   }
//   if (sensorval4 < 234){
//     Serial.print(0);
//     Serial.print(',');
//   }

//  /* for PIR sensor 6 input*/
//   if(sensorval5 > 234) {
//     Serial.println(1);
//   }
//   if (sensorval5 < 234){
//     Serial.println(0);
//   }

  Serial.print(sensorval0);
  Serial.print(',');
  Serial.print(sensorval1);
  Serial.print(',');
  Serial.print(sensorval2);
  Serial.print(',');
  Serial.print(sensorval3);
  Serial.print(',');
  Serial.print(sensorval4);
  Serial.print(',');
  Serial.println(sensorval5);
  delay(10);
}
