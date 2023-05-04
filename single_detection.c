#include <stdio.h>
#include <math.h>
struct sensor_value {
    int x;
    int y;
};

//sensor position
struct sensor_value sensor_data[6] = {
    {1, 2},
    {3, 4},
    {5, 6},
    {7, 8},
    {9, 10},
    {11, 12}
};

//for left and right movement
double servo1(double light_pos[], double person_pos[]) {
    double adjacent = fabs(person_pos[0] - light_pos[0]);
    double opposite = person_pos[1] - light_pos[1];
    double angle;

    if (opposite == 0) {
        angle = 90;
    } else {
        angle = 90 + atan(opposite / adjacent) * 180 / M_PI;
    }

    return angle;
}

// for up and down movement
double servo2(double light_pos[], double person_pos[], double light_height) {
    double opposite = fabs(person_pos[0] - light_pos[0]);
    double adjacent = light_height;
    double angle = atan(opposite / adjacent) * 180 / M_PI;
    return angle;
}

//light position
double light_height = 3;
double light1_pos[2] = {0, 5};
double light2_pos[2] = {20, 5};

int main()
{
    //led readings
    int ledstate1 = 1;
    int ledstate2 = 1;
    int ledstate3 = 0;
    int ledstate4 = 0;
    int ledstate5 = 0;
    int ledstate6 = 0;
    
    //led readings in array
    int *ledarray[6] = {&ledstate1, &ledstate2, &ledstate3, &ledstate4, &ledstate5, &ledstate6};
    int lenght = sizeof(ledarray)/sizeof(ledarray[0]);
    
    //calculation of xaxis and yaxis of single person
    int totalxaxis = 0;
    int totalyaxis = 0;
    int j = 0;
    
    for(int i=0;i<lenght;i++){
        if(*ledarray[i] == 1){
            totalxaxis += sensor_data[i].x;
            totalyaxis += sensor_data[i].y;
            j++;
        }
    }
    
    int xaxis = totalxaxis / j;
    int yaxis = totalyaxis / j;
    printf("%d, ",xaxis);
    printf("%d, ",yaxis);
    printf("%d ", j);
    
    double person_pos[2] = {xaxis, yaxis};

    printf("Person position\n");
    printf("%f %f\n", person_pos[0], person_pos[1]);
    printf("--------------------------\n");
    printf("servo 2 angles for light 1\n");
    printf("%f\n", servo2(light1_pos, person_pos, light_height));
    printf("servo 1 angles for light 1\n");
    printf("%f\n", servo1(light1_pos, person_pos));
    printf("servo 2 angles for light 2\n");
    printf("%f\n", servo2(light2_pos, person_pos, light_height));
    printf("servo 1 angles for light 1\n");
    printf("%f\n", servo1(light1_pos, person_pos));
    

    return 0;
}
