#include <Servo.h>

Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;

int light_height = 10;
int light1_pos[2] = {0, 5};
int light2_pos[2] = {20, 5};
int person_pos[2] = {3, 4};

void setup() {
  servo_1.attach(3);
  servo_2.attach(5);
}

void loop() {
  int servo1_angle_light1 = servo1(light1_pos, person_pos);
  int servo2_angle_light1 = servo2(light1_pos, person_pos, light_height);
  int servo1_angle_light2 = servo1(light2_pos, person_pos);
  int servo2_angle_light2 = servo2(light2_pos, person_pos, light_height);
  
  // move servo 1 of light 1 to the calculated angle
  servo_1.write(90);
  Serial.println(servo1_angle_light1);
  
  // move servo 2 of light 1 to the calculated angle
  servo_2.write(90);
  
  // move servo 1 of light 2 to the calculated angle
  servo_3.write(servo1_angle_light2);
  
  // move servo 2 of light 2 to the calculated angle
  servo_4.write(servo2_angle_light2);
  
  delay(1000); // wait for 1 second
}

// for right and left movement
int servo1(int light_pos[], int person_pos[]) {
  int adjacent = abs(person_pos[0] - light_pos[0]);
  int opposite = person_pos[1] - light_pos[1];
  int angle;
  if (opposite == 0) {
    angle = 90;
  } else {
    angle = 90 + (180.0 / 3.141592) * atan(opposite / (float)adjacent);
  }
  return angle;
}

// for up and down movement
int servo2(int light_pos[], int person_pos[], int light_height) {
  int opposite = abs(person_pos[0] - light_pos[0]);
  int adjacent = light_height;
  int angle = (180.0 / 3.141592) * atan(opposite / (float)adjacent);
  return angle;
}
