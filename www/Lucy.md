# Final Programming Report

An iterative approach was taken to the programming: by gradually increasing the features in the MCU

## Overall Outcome
We successfully developed the user interface of the board throughout this project, by adding features iteratively within the code. In the initial week of the project, work was relatively slow because there was lots of learning to be done. The CH32V003F4P6 is a relatively difficult board to program compared to something like an Arduino, so the first week was spent trying to interact with the board and familiarise with the MounRiver Studio software that we were using to flash the board. 

During the first week, we focused on trying to get the RGB LED to light up, which (with hindsight) was the most challenging task of the entire project. The LED was programmable so required specific libraries to switch on, which are not widely available for this microprocessor and was much too difficult of a task for complete beginners (aka me). Following our proposal presentations, we received feedback and decided to go back to Noam to redefine our goals for the following 3 weeks. 

In our second meeting with Noam, we could ask much more relevant and specific questions because we were more familiar with the board and the challenges that came with programming it. We redefined the goals for the rest of the project and decided to focus on the user interface and implementing the various features that Noam wanted. Each stage of the code has been documented in our [code](code/README.md) folder, along with the progress that we made at each stage. 

## Button Press

When the user presses the button, 2 things happen:
1. The white LEDs increase in brightness
2. The red, green and orange LEDs show the battery voltage for 10 seconds

### White LEDs increasing in brightness
The original code we received from Noam used PWM to control the brightness of the LEDs, with 5 steps of 0, 25%, 50%, 75%, 100%  brightness levels. When just connected to the computer, this code worked fine. However when the battery was inserted, we noticed an issue where on the 4th or 5th button press, all LEDs (including the red, orange and green) would suddenly switch off, as though the microcontroller was resetting. This was a confusing issue, because we had no programming to switch the red, orange and green LEDs off in this sudden way. We concluded that a 'brownout' was happening (like a blackout but less extreme) because the battery voltage measured on this higher LED setting significantly decreased. The system was automatically resetting itself every time, which we think could be from sudden surging current or overloading of the battery.

To solve this issue, we tried to reduce the large jump in brightness and reduce the maximum brightness. I changed the step PWM values to 0, 10%, 25%, 45%, 70% which still provides good variation in brightness levels and solves the browning out issue. 

        const uint8_t brightness_curve[] = {0, 10, 25, 45, 70}; // 5 steps
        PWM_LED_VALUE = brightness_curve[LEDmode];

Each time the button is pressed, the variable **LEDmode** increases by 1 up to a maximum of value of 4 (set by the variable **LEDsteps**). The **PWM_LED_VALUE** which controls the brightness of the LEDs is then set by indexing into an array of increasing brightnesses. 

### Battery Voltage Display


As well as increasing the brightness of the white LEDs, pressing the button triggers the red, orange and green LEDs to display the battery voltage. In order to implement this, we obtain the battery voltage using the **getFB_BAT()** function, which pulls values from a buffer used to store values that are read using the multichannel ADC. 

The code we received from Noam initialised a single channel ADC, which obtained the USB voltage used for regulating the PWM_USB so we had to implement a 4 channel ADC to gather new FB values. 

There are 4 sampling channels available from the circuit diagram which we can access with the microcontroller by initialising a multichannel ADC. 
  - **FB_USB** (PC4/A2) Channel 1
  - **FB_SOLAR** (PA2/A0) Channel 2
  - **FB_BAT** (PD4/A7) Channel 3
  - **FB_ILED** (PD3/A4) Channel 4

^^ this whole bit should probs go in Jim's. Makes more sense

## Power Conservation Improvements

### Sleep Mode and Standby Mode

The overall goal of sleep mode is to conserve power and prevent the battery discharging lower than the safe level. The project uses 3.7V rechargeable batteries, which should not be discharged below their discharge cut-off voltage of 3V. To prevent batteries dropping below this charge level, the microcontroller (mcu) should go into sleep mode when the battery voltage drops below 3.2V. 

The function **getFB_BAT()** is used to read the battery voltage, and convert the raw ADC value into a voltage using a  multiplier. This is then averaged using a **for** loop within the main loop to return the float **avg_bat**. If **avg_bat** falls below 3.2V, the mcu goes to sleep, using the line **PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);**. 

The challenge in implementing this section arose when trying to wake the mcu up from sleep mode. Initially, we set the push button as an interrupt to wake the mcu up, which required use of the **__WFI()** function. The interrupt worked perfectly without the **__WFI()** line, but when **__WFI()** was introduced the mcu would only wake up the first two times, and then would remain asleep no matter how many times the button was pressed. This appeared to be because the 2nd button press was not going through the interrupt sequence, so the flag was not being reset, which is an internal issue of the **__WFI()** function itself. 

An alternative solution was to use a deeper sleep mode called standby mode, called using the function **PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);**, however if using a button to wake up from this mode it restarts from main. This would not be an issue if we had multiple buttons, but the PCB we were given only has one programmable button (the RESET button cannot be programmed easily). Setting this button as an interrupt means that every time it is pressed, the interrupt function overwrites it's original functionality, so when we tested this code, the LEDs no longer increased in brightness when the button was pressed. A solution for future iterations of the project would be to add another button to the PCB, but obtaining these new boards was out of the timescale of our project. 

As a proof of concept, I implemented a periodic wakeup system where the mcu wakes itself up every 10 seconds with an timed interrupt, set by the **standbyConfig()** function, explained in the Curious Scientist blog on using Low Power Modes with the CH32V003 microcontroller family. This means that the mcu periodically wakes up, checks the battery voltage, and goes back to sleep if it has not risen above 3.2V. This reduces power used by the mcu and can be further improved by increasing the period of time that the mcu is switched off. However, this comes with the tradeoff that there is no user input available to wake the mcu, so once it is asleep the user has to wait until it wakes up if they want to use the light. This is quite impractical so I think the best solution moving forwards is to add another button to the board, so the mcu can remain asleep until woken by the user pressing the button. 

### Inactivity sends MCU to sleep

I implemented some code that sends the MCU to sleep if the LED mode is 0 for over 2 minutes, signalling the light is not in use. The variable **modetracker** counts up every time the main loop runs whilst the LED mode is zero. If **modetracker** reaches 4000 (this takes around 2 minutes), the mcu goes into sleep mode to conserve battery when it is not being used. This is more of a proof of concept: it should only really be included if there is a second push button added so that the MCU can be woken up using a button interrupt. 

### Solar Detection
When the ADC value increases above a certain threshold (0.27) the LEDmode is set to zero, because the user is not expected to require the light when sunlight is detected. 
This feature can be overridden by pressing the button using the **overwrite_solar** variable, which is set to 1 when the button is pressed to increase the LED brightness above zero. The variable **overwrite_solar** is set back to zero when the LED mode returns to zero.  









## References

Battery discharge cutoff voltage https://www.amazon.co.uk/PKCELL-900mah-ICR18350-Rechargeable-Battery/dp/B0897RCSYV?ref_=ast_sto_dp
Low power mode blog https://curiousscientist.tech/blog/ch32v003j4m6-low-power-modes


