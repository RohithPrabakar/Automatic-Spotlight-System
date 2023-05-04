import math

#for right and left movement
def servo1(light_pos, person_pos):      
    adjacent = abs(person_pos[0] - light_pos[0])
    opposite = person_pos[1] - light_pos[1]
    if(opposite == 0):
        angle = 90
    else:
        angle = 90 + math.degrees(math.atan(opposite/adjacent))
   
    return angle


#for up and down movement
def servo2(light_pos, person_pos, light_height):
    opposite = light_height
    adjacent = abs(person_pos[0] - light_pos[0])
    angle = 180 - (math.degrees(math.atan(opposite/adjacent)))
    return angle
   
light_height = 3
light1_pos = [0,5]
light2_pos = [20,5]
person_pos = [1,1]

print("Person position")
print(person_pos[0],person_pos[1])
print("--------------------------")
print("servo 2 angles for light 1")
print(servo2(light1_pos,person_pos,light_height))
print("servo 1 angles for light 1")
print(servo1(light1_pos,person_pos))
print("servo 2 angles for light 2")
print(servo2(light2_pos,person_pos,light_height))
print("servo 1 angles for light 2")
print(servo1(light1_pos,person_pos))

