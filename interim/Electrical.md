# Electrical Interim Report

## RGB LED
- WS2812 LED is a programmable LED, aiming to replace the 3 separate red, orange and green LEDs.
- Controlled by input data stream of 24 bits, 8 bits for red, 8 bits for green, 8 bits for blue.
- Precise timing is required to send the colour signals. 

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
We started by focusing on the first functionality requirement, which is the LEDs showing the battery status when the button is pressed. This required an understanding of the circuit diagram and to measure the voltage of the battery by initialising a multichannel ADC. We had several *technical difficulties* 
### Multichannel ADC 
- There are 4 sampling channels available from the circuit diagram which we can access with the microcontroller
  - FB_USB (PC4/A2) Channel 1
  - FB_SOLAR (PA2/A0) Channel 2
  - FB_BAT (PD4/A7) Channel 3
  - FB_ILED (PD3/A4) Channel 4
- Floats cannot be directly printed in C, so there is a neat trick to display them as 2 integers.

- Also fixed Noam's code because his single ADC was connected to the wrong pin. 

### Melting Components :( 
We have encountered several issues along the way with this circuit, some by accident! 
#### Inductor Heating
When touching the board, the inductor was very hot and in danger of melting from an overload of current. After research, we found that there are two ways to prevent this from happening: decreasing the voltage (by decreasing the PWM) 
#### Chip Destruction
#### Explosive Batteries???
