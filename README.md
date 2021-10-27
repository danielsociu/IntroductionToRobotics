# Introduction to Robotics (2021 - 2022)
This repository represents my progress throughout the 3rd year university course of robotics at the Faculty of Mathematics and Computer Science, University of Bucharest, entailing all the homeworks and side projects. 
Since it's a robotics repo, firstly it will have the source code and details about the implementation.

## Task 1
This task is about making an RGB led that has it's leds controlled by 3 different potentiometers.  
Items used:

* arduino uno
* one breadboard 
* 3 potentiometers
* 1 RGB led 
* 18 connectivity cables  

### [Coding:](lab1/task1/task1.ino)
What I did was take the values from the potentiometers (analog in A0, A1, A2), since they take values from 0-1023 I had to divide the value by 4 so it converts to RGB range.  
Then I sent those values to the RGB led through the digital out (with pwm, ~9, ~10, ~11), and also printed them with Serial.print.

### Arduino
![Arduino image](https://cdn.discordapp.com/attachments/902874706854682637/902875312679968778/unknown.png)

1. First we get 5V and the ground to a column on the breadboard through which I power all my potentiometers.  
2. Then I connect all the potentiometers' output to the analog in A0, A1, A2 representing red, green and blue.
    - here the code that loops makes changes on the output and sends it to led
3. Sending the RGB values to the led with the digital out ports ~9,~10 and ~11, which also power the led.

## Task 1
