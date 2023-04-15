#include <Servo.h>

Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;

#define LED1 10  // power (green)  ground (blue)
#define LED2 11

int light_height = 10;
int seran=0;
int light1_pos[2] = { 0, 5 };
int light2_pos[2] = { 20, 5 };
int person_pos[2] = { 3, 4 };

void setup() {
  servo_1.attach(5);
  servo_2.attach(3);
  servo_3.attach(6);
  servo_4.attach(9);
}

void loop() {

  int menuChoice = Serial.parseInt();
  servo_1.write(menuChoice);
  servo_2.write(menuChoice);
  servo_3.write(menuChoice);
  servo_4.write(menuChoice);
  Serial.println(menuChoice);

  delay(1000);
}