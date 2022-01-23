How to control LED by potentiometer (variable resistor)

Youtube video link: https://www.youtube.com/watch?v=INh9_MQy3Pg

Hardware Components: 
 
  - Tiva C launchpad
  - 10K Ohms potentiometer
  - Jumpers

Schematic of the circuit:
![adc](https://user-images.githubusercontent.com/42329717/150673121-dd9297e5-2873-494b-814a-f2abe2d62dc0.jpg)

In this project, i read the analog voltage from Analog Input 0 (AIN0) -> (PE3) with SS3 (sample sequenzer 3).

This ADC code of TM4C123GH6PM microcontroller reads analog input from AN0 pin and
based on digital value turns on or turns off the onboard green LED of TM4C123G Tiva C launchpad.
If measured digital value is less than 2048 LED will remain off. If ADC digital value is greater than or equal to 2048, LED turns on.

