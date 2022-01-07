How to interface an LCD with Tiva C LaunchPad

Youtube Video: https://www.youtube.com/watch?v=q109cotB7AA

Hardware Components:
 - Tiva C LaunchPad (TM4C123)
 - 16x2 LCD Display
 - 1x1K Potentiometer
 - 5v Power Supply
 - Jumpers

Schematic of the circuit: 

![LCD](https://user-images.githubusercontent.com/42329717/148565233-7be69ca0-19d2-4955-b802-d959c61d3a94.jpg)



Notes that may help you in this project:
 - volatile keyword should be included in your code with variable value can be changed any time such as the counter of for loop
 - 5v Power supply is important for LCD display (without it, your LCD does not work correctly)
 - Adjust the potentiometer if LCD does not display any data.
