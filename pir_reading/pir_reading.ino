int led = LED_BUILTIN;
#define PIR_sensor1 2   // output (white) ground (black) power (red)
#define PIR_sensor2 4   // output (white) ground (black) power (red)
#define PIR_sensor3 7   // output (white) ground (black) power (red)
#define PIR_sensor4 8   // output (yellow) ground (blue) power (green)
#define PIR_sensor5 12  // output (yellow) ground (blue) power (green)
#define PIR_sensor6 13

void setup() {
  pinMode(PIR_sensor1, INPUT);
  pinMode(PIR_sensor2, INPUT);
  pinMode(PIR_sensor3, INPUT);
  pinMode(PIR_sensor4, INPUT);
  pinMode(PIR_sensor5, INPUT);
  pinMode(PIR_sensor6, INPUT);
  Serial.begin(9600);
}
void loop() {
  int pirstate1 = digitalRead(PIR_sensor1);
  int pirstate2 = digitalRead(PIR_sensor2);
  int pirstate3 = digitalRead(PIR_sensor3);
  int pirstate4 = digitalRead(PIR_sensor4);
  int pirstate5 = digitalRead(PIR_sensor5);
  int pirstate6 = digitalRead(PIR_sensor6);

  int *pirarray[6] = {&pirstate1, &pirstate2, &pirstate3, &pirstate4, &pirstate5, &pirstate6};
  int length = sizeof(pirarray)/sizeof(pirarray[0]);
  Serial.print("Values in pirarray: ");
  for (int i = 0; i < length; i++) {
    Serial.print(*pirarray[i]);
    Serial.print(" ");
  }
  Serial.println();
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

 delay(1000);
}
