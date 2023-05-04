#include <Servo.h>

Servo servo1;  //light 1 left & right (yellow) (port 5)
Servo servo2;  //light 1 up & down (white) (port 3)
Servo servo3;  //light 2 left & right (yellow) (port 6)
Servo servo4;  //light 2 up & down (white) (port 9)
#define PIR_sensor1 2   // output (white) ground (black) power (red)
#define PIR_sensor2 4   // output (white) ground (black) power (red)
#define PIR_sensor3 7   // output (white) ground (black) power (red)
#define PIR_sensor4 8   // output (yellow) ground (blue) power (green)
#define PIR_sensor5 12  // output (yellow) ground (blue) power (green)
#define PIR_sensor6 13  // output (yellow) ground (blue) power (green)
#define LED1 10  // power (green)  ground (blue)
#define LED2 11  // power (green)  ground (blue)

struct sensor_value {
    double x;
    double y;
};

//sensor position
struct sensor_value sensor_data[6] = {
    {2, 0.37},  // pir 1
    {2, 5.42},  //pir 6
    {5.5, 2},  // pir 2
    {5.5, 4},  // pir 5
    {9, 0.37},  // pir 3
    {9, 5.42}  // pir 4
};

//light position
double light_height = 3;
double light1_pos[2] = {0, 2.8};
double light2_pos[2] = {11, 2.8};


double lr_mov(double light_pos[], double person_pos[]) { //for left & right movment
    double adjacent = fabs(person_pos[0] - light_pos[0]);
    double opposite = person_pos[1] - light_pos[1];
    double angle;
    if (opposite == 0) {
      angle = 90;
    } else if(adjacent == 0){
      angle = 0;
    }else if (opposite < 0){
      angle = 90 - ((atan(fabs(opposite) / adjacent)) * (180 / M_PI));        
    }
    else {
        angle = 90 + ((atan(opposite / adjacent)) * 180 / M_PI);
    }

    return floor(angle);
}

// for up and down movement
double ud_mov(double light_pos[], double person_pos[], double light_height) {
    double opposite = fabs(person_pos[0] - light_pos[0]);
    double adjacent = light_height;
    double angle = 180 - (atan(opposite / adjacent) * 180 / M_PI);
    return floor(angle);
}



void setup() {
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

  //pir kept in an pirarray A and pirArray B
  int *pirarrayA[4] = {&pirstate1, &pirstate6, &pirstate2, &pirstate5};
  int *pirarrayB[4] = {&pirstate2, &pirstate5, &pirstate3, &pirstate4};
  int length = sizeof(pirarrayA)/sizeof(pirarrayA[0]);

  //calculation of totalxaxis and totalyaxis Section A
  double totalxaxisA = 0;
  double totalyaxisA = 0;
  double jA = 0;

  for(int i=0;i<length;i++){
    if(*pirarrayA[i] == 1){
      totalxaxisA += sensor_data[i].x;
      totalyaxisA += sensor_data[i].y;
      jA++;
    }
  }

  //calculation of totalxaxis and totalyaxis Section B
  double totalxaxisB = 0;
  double totalyaxisB = 0;
  double jB = 0;

  for(int i=0;i<length;i++){
    if(*pirarrayB[i] == 1){
      totalxaxisB += sensor_data[2+i].x;
      totalyaxisB += sensor_data[2+i].y;
      jB++;
    }
  }

  //calculation of xaixs and yaxis in Section A
  double xaxisA;    //person x position
  double yaxisA;    //person y position
  if(totalxaxisA == 0 && totalyaxisA == 0){
    xaxisA = 0;
    yaxisA = 0;
  }
  else{
    xaxisA = totalxaxisA / jA;
    yaxisA = totalyaxisA / jA;
  }

  //calculation of xaixs and yaxis in Section B
  double xaxisB;    //person x position
  double yaxisB;    //person y position
  if(totalxaxisB == 0 && totalyaxisB == 0){
    xaxisB = 0;
    yaxisB = 0;
  }
  else{
    xaxisB = totalxaxisB / jB;
    yaxisB = totalyaxisB / jB;
  }
  
  // print all values in pirarrayA and pirarrayB line by line
  Serial.println("--------------------------");
  Serial.print("Values in pirarrayA: ");
  for (int i = 0; i < length; i++) {
    Serial.print(*pirarrayA[i]);
    Serial.print(" ");
  }
  Serial.print("Values in pirarrayB: ");
  for (int i = 0; i < length; i++) {
    Serial.print(*pirarrayB[i]);
    Serial.print(" ");
  }
  // print xaxisA yaxisA xaxisB yaxisB 
  Serial.println();
  Serial.print("Section A: ");
  Serial.print(xaxisA);
  Serial.print(" ");
  Serial.print(yaxisA);
  Serial.print(" ");
  Serial.print(jA);
  Serial.println();
  Serial.print("Section B: ");
  Serial.print(xaxisB);
  Serial.print(" ");
  Serial.print(yaxisB);
  Serial.print(" ");
  Serial.print(jB);
  Serial.println();

  double person_posA[2] = {xaxisA, yaxisA};
  double person_posB[2] = {xaxisB, yaxisB};

  //light status
  if(xaxisA || yaxisA || xaxisB || yaxisB){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);    
  }else{
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }

  Serial.println("Person position in Section A");
  Serial.print(person_posA[0]);
  Serial.print(" ");
  Serial.println(person_posA[1]);
  Serial.println("Person position in Section B");
  Serial.print(person_posB[0]);
  Serial.print(" ");
  Serial.println(person_posB[1]);


  //servo position
  // if((xaxisA == 0 && yaxisA == 0) && (xaxisB == 0 && yaxisB == 0)){             // No one in room
  //   servo1.write(90);
  //   servo2.write(90);
  //   servo3.write(90);
  //   servo4.write(90);

  //   Serial.println("servo 1 angles for light 1 with None");
  //   Serial.println("90");
  //   Serial.println("servo 2 angles for light 1 with None");
  //   Serial.println("90");
  //   Serial.println("servo 3 angles for light 2 with None");
  //   Serial.println("90");  
  //   Serial.println("servo 4 angles for light 2 with None");
  //   Serial.println("90");
  //}else if((xaxisA != 0 || yaxisA != 0) && (xaxisB == 0 && yaxisB == 0) ){
    if((xaxisA != 0 || yaxisA != 0) && (xaxisB == 0 && yaxisB == 0) ){       // 1 person Section A only
    servo1.write(lr_mov(light1_pos, person_posA));
    servo2.write(ud_mov(light1_pos, person_posA, light_height));
    servo3.write(180 - lr_mov(light2_pos, person_posA));
    servo4.write(ud_mov(light2_pos, person_posA, light_height));

    //print Value
    Serial.println("servo 1 angles for light 1 with section A only");
    Serial.println(lr_mov(light1_pos, person_posA));
    Serial.println("servo 2 angles for light 1 with section A only");
    Serial.println(ud_mov(light1_pos, person_posA, light_height));
    Serial.println("servo 3 angles for light 2 with section A only");
    Serial.println(180 - lr_mov(light2_pos, person_posA));  
    Serial.println("servo 4 angles for light 2 with section A only");
    Serial.println(ud_mov(light2_pos, person_posA, light_height));    
  }else if((xaxisB != 0 || yaxisB != 0) && (xaxisA == 0 && yaxisA == 0) ){       // 1 person Section B only
    servo1.write(lr_mov(light1_pos, person_posB));
    servo2.write(ud_mov(light1_pos, person_posB, light_height));
    servo3.write(180 - lr_mov(light2_pos, person_posB));
    servo4.write(ud_mov(light2_pos, person_posB, light_height));


    //print Value
    Serial.println("servo 1 angles for light 1 with section B only");
    Serial.println(lr_mov(light1_pos, person_posB));
    Serial.println("servo 2 angles for light 1 with section B only");
    Serial.println(ud_mov(light1_pos, person_posB, light_height));
    Serial.println("servo 3 angles for light 2 with section B only");
    Serial.println((180 - lr_mov(light2_pos, person_posB)));  
    Serial.println("servo 4 angles for light 2 with section B only");
    Serial.println(ud_mov(light2_pos, person_posB, light_height));
  }
  else if((xaxisB != 0 && yaxisB != 0) && (xaxisB != 0 && yaxisB != 0)){     // 1 person Section A and 1 person Section B
    servo1.write(lr_mov(light1_pos, person_posA));
    servo2.write(ud_mov(light1_pos, person_posA, light_height));
    servo3.write((180 - lr_mov(light2_pos, person_posB)));
    servo4.write(ud_mov(light2_pos, person_posB, light_height));

    //print Value
    Serial.println("servo 1 angles for light 1 with section A and section B");
    Serial.println(lr_mov(light1_pos, person_posA));
    Serial.println("servo 2 angles for light 1 with section A and section B");
    Serial.println(ud_mov(light1_pos, person_posA, light_height));
    Serial.println("servo 3 angles for light 2 with section A and section B");
    Serial.println((180 - lr_mov(light2_pos, person_posB)));  
    Serial.println("servo 4 angles for light 2 with section A and section B");
    Serial.println(ud_mov(light2_pos, person_posB, light_height));
  }
  

  delay(1000);
}
