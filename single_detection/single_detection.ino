#include <Servo.h>

Servo servo1;  //light 1 left & right (yellow)
Servo servo2;  //light 1 up & down (white)
Servo servo3;  //light 2 left & right (yellow)
Servo servo4;  //light 2 up & down (white)
#define PIR_sensor1 2   // output (white) ground (black) power (red)
#define PIR_sensor2 4   // output (white) ground (black) power (red)
#define PIR_sensor3 7   // output (white) ground (black) power (red)
#define PIR_sensor4 8   // output (yellow) ground (blue) power (green)
#define PIR_sensor5 12  // output (yellow) ground (blue) power (green)
#define PIR_sensor6 13  // output (yellow) ground (blue) power (green)
#define LED1 10  // power (green)  ground (blue)
#define LED2 11  // power (green)  ground (blue)

struct sensor_value {
    int x;
    int y;
};

//sensor position
struct sensor_value sensor_data[6] = {
    {2, 2},
    {5.5, 2},
    {9, 2},
    {9, 4},
    {5.5, 4},
    {2, 4}
};


double lr_mov(double light_pos[], double person_pos[]) { //for left & right movment
    double adjacent = fabs(person_pos[0] - light_pos[0]);
    double opposite = person_pos[1] - light_pos[1];
    double angle;

    if (opposite == 0) {
        angle = 90;
    } else {
        angle = 90 + atan(opposite / adjacent) * 180 / PI;
    }

    return angle;
}

// for up and down movement
double ud_mov(double light_pos[], double person_pos[], double light_height) {
    double opposite = fabs(person_pos[0] - light_pos[0]);
    double adjacent = light_height;
    double angle = 180 - (atan(opposite / adjacent) * 180 / M_PI);
    return angle;
}

//light position
double light_height = 3;
double light1_pos[2] = {0, 2.8};
double light2_pos[2] = {10., 2.8};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(5);
  servo2.attach(3);
  servo3.attach(6);
  servo4.attach(9);
  pinMode(PIR_sensor1, INPUT);
  pinMode(PIR_sensor2, INPUT);
  pinMode(PIR_sensor3, INPUT);
  pinMode(PIR_sensor4, INPUT);
  pinMode(PIR_sensor5, INPUT);
  pinMode(PIR_sensor6, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void loop() {
  //pir readings taken in
  int pirstate1 = digitalRead(PIR_sensor1);
  int pirstate2 = digitalRead(PIR_sensor2);
  int pirstate3 = digitalRead(PIR_sensor3);
  int pirstate4 = digitalRead(PIR_sensor4);
  int pirstate5 = digitalRead(PIR_sensor5);
  int pirstate6 = digitalRead(PIR_sensor6);

  //pir kept in an array
  int *pirarray[6] = {&pirstate1, &pirstate2, &pirstate3, &pirstate4, &pirstate5, &pirstate6};
  int length = sizeof(pirarray)/sizeof(pirarray[0]);

  //calculation of xaxis and yaxis of single person
  int totalxaxis = 0;
  int totalyaxis = 0;
  int j = 0;

  for(int i=0;i<length;i++){
    if(*pirarray[i] == 1){
      totalxaxis += sensor_data[i].x;
      totalyaxis += sensor_data[i].y;
      j++;
    }
  }

  // print all values in ledarray in one line
  Serial.println("--------------------------");
  Serial.print("Values in pirarray: ");
  for (int i = 0; i < length; i++) {
    Serial.print(*pirarray[i]);
    Serial.print(" ");
  }
  Serial.println();

  
  int xaxis;    //person x position
  int yaxis;    //person y position
  if(totalxaxis == 0 && totalyaxis == 0){
    xaxis = 0;
    yaxis = 0;
  }
  else{
    xaxis = totalxaxis / j;
    yaxis = totalyaxis / j;
  }

  Serial.print(xaxis);
  Serial.print(" ");
  Serial.print(yaxis);
  Serial.print(" ");
  Serial.println(j);

  double person_pos[2] = {xaxis, yaxis};
  if(xaxis || yaxis){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);    
  }else{
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }

  //servo position
//  if(xaxis == 0 && yaxis == 0){
    // servo1.write(90);
    // servo2.write(90);
    // servo3.write(90);
    // servo4.write(90);
//  }else{
    servo1.write(lr_mov(light1_pos, person_pos));
    servo2.write(ud_mov(light1_pos, person_pos, light_height));
    servo3.write(lr_mov(light1_pos, person_pos));
    servo4.write(ud_mov(light2_pos, person_pos, light_height));
 // }


  Serial.println("Person position");
  Serial.print(person_pos[0]);
  Serial.print(" ");
  Serial.println(person_pos[1]);
  Serial.println("servo 1 angles for light 1");
  Serial.println(lr_mov(light1_pos, person_pos));
  Serial.println("servo 2 angles for light 1");
  Serial.println(ud_mov(light1_pos, person_pos, light_height));
  Serial.println("servo 3 angles for light 2");
  Serial.println(lr_mov(light1_pos, person_pos));  
  Serial.println("servo 4 angles for light 2");
  Serial.println(ud_mov(light2_pos, person_pos, light_height));
  

  
  

  delay(1000);
}
