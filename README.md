# Introduction to Robotics (2021 - 2022)
This repository represents my progress throughout the 3rd year university course of robotics at the Faculty of Mathematics and Computer Science, University of Bucharest, entailing all the homeworks and side projects. 
Since it's a robotics repo, firstly it will have the source code and details about the implementation.

## Task 1
<details>
<summary>First task details</summary> <br>
This task is about making an RGB led that has it's leds controlled by 3 different potentiometers.  
Items used:

* arduino uno
* one breadboard 
* 3 potentiometers
* 3 resistors (220)
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
3. Sending the RGB values to the led with the digital out ports ~9,~10 and ~11, which also power the led. Since each out is 5V we need resistors for the extra voltage.  

[Demonstration video](https://www.youtube.com/watch?v=gF32hki-3Qw)
</details>

## Task 2
<details>
<summary>Second task details </summary> <br>
This implements traffic lights for cars and pedestrians. The semaphore for cars has 3 leds and the one for pedestrians has 2 leds.  
The whole system has 4 states:  

1. Green for cars, red for pedestrians (permament until button is pressed)
2. Yellow for cars, red for pedestrians (starts 10 seconds after state 1 and lasts 3 seconds)
3. Red for cars and green for pedestrians with a constant beeping sound (Duration 10s)
4. Red for cars and a blinking green for pedestrians with a faster constant beeping sound (duration 5 seconds)  

The default state will be state one, and the trigger to go in state 2 will be a button. Pressing the button in any other state than the first will not change anything.  
Items used:  

* arduino uno
* one breadboard
* 5 leds
* 1 button
* 1 active buzzer
* 3 resistors
* wires

### [Coding:](lab2/task2/task2.ino)
For initialization it has the variables declarations and the setup.  
In the loop it firstly checks if the button was pressed with a debouncer and if the state of the program was 1 else it does nothing (it uses a variable programState to keep in mind in which state arduino is).  
After that we have the four states implementation, lighting the proper leds at each one of them, and for state 3 and 4 we add the buzzer sound. 
Each one of them makes use of the millis() for the timing implementation.  
We also have 3 functions, one for writing to the leds, one for making a led blink at a specific interval and one that makes a buzzer beep at a regular interval.

### Arduino
![Arduino_image](https://cdn.discordapp.com/attachments/902874706854682637/905536721377165472/unknown.png)  

1. Button that has a connection type PULLUP. Initializes state 2 of the program
2. Pedestrian semaphore
3. Car semaphore
4. The active buzzer for the pedestrian semaphore.

[Demonstration video](https://youtube.com/watch?v=JWWpOgTnioQ&feature=share)

</details>
