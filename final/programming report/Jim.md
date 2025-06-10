[code](code)





As well as increasing the brightness of the white LEDs, pressing the button triggers the red, orange and green LEDs to display the battery voltage. In order to implement this, we obtain the battery voltage using the **getFB_BAT()** function, which pulls values from a buffer used to store values that are read using the multichannel ADC. 

The code we received from Noam initialised a single channel ADC, which obtained the USB voltage used for regulating the PWM_USB so we had to implement a 4 channel ADC to gather new FB values. 

There are 4 sampling channels available from the circuit diagram which we can access with the microcontroller by initialising a multichannel ADC. 
  - **FB_USB** (PC4/A2) Channel 1
  - **FB_SOLAR** (PA2/A0) Channel 2
  - **FB_BAT** (PD4/A7) Channel 3
  - **FB_ILED** (PD3/A4) Channel 4
