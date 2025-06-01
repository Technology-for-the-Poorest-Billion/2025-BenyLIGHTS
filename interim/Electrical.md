# Electrical Interim Report

## Redefined Expectations
- Following feedback from our proposal presentation, we met again with Noam to discuss the expectations.
- He explained that the RGB LED is an extension exercise, and that we should focus on the basic functionality of the board first.
- Functionality Requirements
    - When user presses the button, 3 LEDs show battery status for 10 seconds and LED brightness should increase in 4 steps
    - When sun detected, LED should be set back to 0%
    - When battery is below 3.2V, enter sleep mode. When battery is over 3.4V, exit sleep mode and wait for user.
    - When user presses RESET, enter sleep mode
- We also worked out that the big boards don't light up without the battery being connected.

## Technical Progress
We have been documenting each code draft in the **code** folder of our GitHub, where the README file clearly explains what progress has been made in each iteration of the code. 

We started by focusing on the first functionality requirement, which is the LEDs showing the battery status when the button is pressed. This required an understanding of the circuit diagram and to measure the voltage of the battery by initialising a multichannel ADC. We had several "technical difficulties" along the way but managed to solve them as we went along. 

### RGB LED
#### Objectives
- WS2812 LED is a programmable LED, aiming to replace the 3 separate red, orange and green LEDs.
- Controlled by input data stream of 24 bits, 8 bits for red, 8 bits for green, 8 bits for blue.
- Precise timing is required to send the colour signals.

<img src="https://github.com/user-attachments/assets/a8ebc379-6f4d-4d00-b0be-e49ac661be34" width="300"/>
<img src="https://github.com/user-attachments/assets/6104afc8-59b7-438d-89d4-88e13fb0c015" width="300"/>
<img src="https://github.com/user-attachments/assets/868338b5-9130-45ca-8fca-06aec21aafae" width="300"/>

*Images sourced from https://lastminuteengineers.com/ws2812b-arduino-tutorial/*

#### Difficulties Faced
 - The precise timing is very difficult to achieve with limited programming experience and time. 
 - The library on Github is difficult to implement for a single LED, becuase it is written for a strip of LEDs so lots of the code can be removed.
 - Integrating the LED code with the bigger board must be done before testing, otherwise the bigger board will blow when a battery is inserted.
   
#### Outcome
 - There is one demo code on GitHub containing the header files with functions that allow the light up, so by changing the pins and ports in this code, we managed to get the RGB LED to light up. This can be found in the **RGB LED** folder in our **code** folder.
 - This can be revisited at the end of the project if time permits.

### Multichannel ADC 
In order to read the voltage across the battery, we needed to use the microcontroller to read the value of FB_BAT (battery feedback). The code Noam gave to us utilized a single channel ADC, but this was already being used to control the USB voltage using PWM_USB. To read the battery voltage we required a multichannel ADC, which was more complicated to implement. 

<img src="https://github.com/user-attachments/assets/ae9cc546-1e46-4e4b-9c72-b2959458f47c" width="300"/>
<img src="https://github.com/user-attachments/assets/4961bb11-972c-4994-9d05-b39819355a00" width="700"/>


#### ADC_MultiChannel_Init
There are 4 sampling channels available from the circuit diagram which we can access with the microcontroller by initialising a multichannel ADC. 
  - FB_USB (PC4/A2) Channel 1
  - FB_SOLAR (PA2/A0) Channel 2
  - FB_BAT (PD4/A7) Channel 3
  - FB_ILED (PD3/A4) Channel 4

#### Printing the Values
Printing the values from a multichannel ADC is more complicated because you cannot directly print a float in C, so have to convert each number to an integer and print it so it looks like an integer. We found that the ADC values fluctuated a lot, so implemented an average across 2000 samples for each readign to try and reduce this fluctuation, which worked successfully. Separate scaling factors were required for each value, so far we have only done FB_BAT but are looking to calibrate the others in the remaining project time. 

### Board Breakages
This part of the circuit shows a boost converter, where the duty cycle is controlled by the PWM_USB input signal. The inductor is sensitive to current and will overheat if the maximum current is exceeded, so it is important to limit this current. 

<img src="https://github.com/user-attachments/assets/cd3468f7-cbba-4cb9-ae70-af91ca5d3b0d" width="500"/>

#### Inductor Heating
When touching the board, the inductor was very hot and in danger of melting from an overload of current. Firstly we had to fix the original code to the correct ADc pin because it wasn't working: when we read the PWM values on the serial monitor it did not really make sense (the PWM changing did not seem to affect the ADC voltage). This meant that the PWM was actually effective in changing the voltage measured by the single channel ADC. We then decreased the limiting ADC value from 350 to 300 which prevents the voltage from reaching a value that is too high, so the inductor now doesn't get too hot, minimising heat loss. 

Having successfully transferred the RGB LED code to a small board, we upgraded it to a big board and added a battery and it blew the board: there is no voltage regulation in the LED code so it is important when adding the battery to ensure that it is inside the original code to prevent overheating of the components. 

#### Chip Destruction
When we connected the battery to one of the bigger boards, it began smoking because one of the chips was overheating. After some confusion, we noticed that the chip had actually been soldered incorrectly onto the board. This highlighted an issue in the PCB manufacturing, so we may need to look into methods of control checking the boards so this doesn't happen again. This is concerning because we only now have 3 remaining functional big boards. 


<img src="https://github.com/user-attachments/assets/da978993-de49-47fe-be59-8c181bb56fc5" width="300"/>

<img src="https://github.com/user-attachments/assets/412afd88-5d04-401a-b51b-9545bce101cc" width="300"/>



#### Explosive Batteries
We had some confusion when the voltmeter had a reading of 5.2V for our rechargeable 3.7V batteries, which is well above their safety limit. We initially panicked, but after a while of researching what to do if your battery explodes, we tried a different voltmeter and worked out that the original voltmeter was wrong. This taught us a valuable lesson in not always trusting the equipment and thinking outside the box to try and solve the problems.  
