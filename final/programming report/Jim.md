# Final contributions report   [code](code)


## Hardware work
I soldered the battery tabs on to make all the provided PCBs compatible with batteries and soldered a solar panel enabling recharging tests. As well as this, the link used to upload the code to the microprocessor was tempremental so needed improving, this involved sourcing a stackable header to replace the crimp connectors and solder with heat shrink to form a more robust and reliable connector to the board.

## Programming contributions 
Me and Lucy worked together on lots of the programming, further detail can be found on the [code](code) page.
### Battery status 
#### Multi-channel ADC
Upon the user pressing the button on the board, as well as increasing the brightness of the white LEDs, the coloured LEDs are required to display the battery voltage. In order to implement this, we obtain the battery voltage using the **getFB_BAT()** function, which pulls values from a buffer used to store values that are read using the multichannel ADC. 

The code we received from Noam initialised a single channel ADC, which obtained the USB voltage used for regulating the PWM_USB so we had to implement a 4 channel ADC to gather new FB values. 

There are 4 sampling channels available from the circuit diagram which we can access with the microcontroller by initialising a multichannel ADC. 
  - **FB_USB** (PC4/A2) Channel 1
  - **FB_SOLAR** (PA2/A0) Channel 2
  - **FB_BAT** (PD4/A7) Channel 3
  - **FB_ILED** (PD3/A4) Channel 4
  - 
#### Calibration
Now able to recieve a 10 bit value from these feedback channels the battery value needs to be calibrated to account for the relative resistors in the potential divider and return an accurate voltage reading. This was done by sequentially draining the battery and using voltmeter as well as the serial moniter to plot ADC values and voltage measurements. From this a linear relationship was observed and enabled a simple coeficient to convert the ADC value to the battery voltage. 

#### Using the LEDs 
Armed with the calibrated battery voltage we could write the code for the LEDs to display the battery status for 10 seconds upon button press. There was many ways to implement this however we decided to choose a counter than incremented each time through the main while loop. Upon a button press this counter was reset to zero and outside of the button press code an if statement incorporated the LED status by turning them on if the **batcount** was less than a specified value **statusledtime**. This meant that after a button was pressed the code looped through this if statement so long as the batcount remained less than statusledtime. Inside the if statement, comparitors were used to selectively light up the different LEDs depending on voltage thresholds specified in the code. The thresholds, and statusledtime will need adjusting to produce the desired status duration and appropriate colour associated with charge level of the battery.

### Averaging to incorporate sleepmode 
In order to prevent the battery charge dropping to damaging levels, a low power sleep mode was to be incorporated that engaged when the calibrated battery voltage dropped below 3.2V. This was implemented using interupts and is discussed further on [Lucy's](Lucy) page. 
