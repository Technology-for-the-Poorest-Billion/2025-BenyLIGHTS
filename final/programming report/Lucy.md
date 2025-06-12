# Final Programming Report

## Brief Summary of the Process
We successfully developed the user interface of the board throughout this project, by adding features iteratively within the code. In the initial week of the project, work was relatively slow because there was lots of learning to be done. The CH32V003F4P6 is a relatively difficult board to program compared to something like an Arduino, so the first week was spent trying to interact with the board and familiarise with the MounRiver Studio software that we were using to flash the board.  This project had quite a long learning period at the beginning: I spent a lot of time trying to understand the circuit diagrams and existing code, which was essential before we could make any progress on writing new code. In addition, the connector was quite unreliable, so we would regularly get the 'failed to configure' mcu error when flashing the board, so it is definitely worth investing some time into making a high quality connector. 

During the first week, we focused on trying to get the RGB LED to light up, which (with hindsight) was the most challenging task of the entire project. The LED was programmable so required specific libraries to switch on, which are not widely available for this microprocessor and was much too difficult of a task for complete beginners (aka me). Following our proposal presentations, we received feedback and decided to go back to Noam to redefine our goals for the following 3 weeks. 

In our second meeting with Noam, we could ask much more relevant and specific questions because we were more familiar with the board and the challenges that came with programming it. We redefined the goals for the rest of the project and decided to focus on the user interface and implementing the various features that Noam wanted. Each stage of the code has been documented in our [code](../../code) folder, along with the progress that we made at each stage. The rest of this page details the technicalities behind this implementation. 

## Button Press

When the user presses the button, 2 things happen:
1. The white LEDs increase in brightness
2. The red, green and orange LEDs show the battery voltage for 10 seconds (covered in [Jim's report](Jim.md))

### White LEDs increasing in brightness
The original code we received from Noam used PWM to control the brightness of the LEDs, involving 5 steps of 0, 25%, 50%, 75%, 100%  brightness levels. When just connected to the computer, this code worked fine. However when the battery was inserted, we noticed an issue where on the 4th or 5th button press, all LEDs (including the red, orange and green) would suddenly switch off, as though the microcontroller was resetting. This was a confusing issue, because we had programmed the red, orange and green LEDs to stay on for 10 seconds after each button press. We concluded that a 'brownout' was happening (like a blackout but less extreme) because the battery voltage measured on this higher LED setting significantly decreased. The system was automatically resetting itself every time, which we think could be from sudden surging current or overloading of the battery.

To solve this issue, I tried to reduce the large jump in brightness. I changed the step PWM values to 0, 10%, 25%, 45%, 70% which still provides good variation in brightness levels and solves the browning out issue. 

        const uint8_t brightness_curve[] = {0, 10, 25, 45, 70}; // 5 steps
        PWM_LED_VALUE = brightness_curve[LEDmode];

Each time the button is pressed, the variable **LEDmode** increases by 1 up to a maximum of value of 4 (set by the variable **LEDsteps**). The **PWM_LED_VALUE** which controls the brightness of the LEDs is then set by indexing into an array of increasing brightnesses. 

## Power Conservation Improvements

### Sleep Mode and Standby Mode

Sleep mode should be activated in the following situations:
- Battery voltage drops below 3.2 V
- LED mode is zero for over 2 minutes

The overall goal of sleep mode is to conserve power and prevent the battery discharging lower than the safe level. The project uses 3.7V rechargeable batteries, which should not be discharged below their discharge cut-off voltage of 3V. To prevent batteries dropping below this charge level, the microcontroller (mcu) should go into sleep mode when the battery voltage drops below 3.2V. 

The function **getFB_BAT()** is used to read the battery voltage, and convert the raw ADC value into a voltage using a multiplier. This is then averaged using a **for** loop within the main loop (explained in [Jim's Report](Jim.md)) to return the float **avg_bat**. If **avg_bat** falls below 3.2V, the mcu goes to sleep, using the line **PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);**. This code is lines 527-557 of our [final code](../../code/11_fixed_LED_steps.c). 

In the same section of code I implemented some code that sends the MCU to sleep if the LED mode is 0 for over 2 minutes, signalling the light is not in use. The variable **modetracker** counts up every time the main loop runs whilst the LED mode is zero. If **modetracker** reaches 4000 (this takes around 2 minutes), the mcu goes into sleep mode to conserve battery when it is not being used. This is more of a proof of concept: it should only really be included if there is a second push button added so that the MCU can be woken up using a button interrupt. 

The challenge in implementing this section arose when trying to wake the mcu up from sleep mode. The various options are outlined in the table below, and then explained in more technical detail. 

![image](https://github.com/user-attachments/assets/de4c3d58-6269-4c99-95f0-0a14bf758484)

Initially, we set the existing push button on PD0 as an interrupt to wake the mcu up, which required use of the **__WFI()** function. The interrupt worked perfectly without the **__WFI()** line, but when **__WFI()** was introduced the mcu would only wake up the first two times, and then would remain asleep no matter how many times the button was pressed. This appeared to be because the 2nd button press was not going through the interrupt sequence, so the flag was not being reset, which is an internal issue of the **__WFI()** function itself. We did not know how to solve this issue, so had to do some more research and implement a different function. 

An alternative solution I found was to use a deeper sleep mode called standby mode, called using the function **PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);**. This function worked for unlimited button presses so was an improvement on the dreaded **__WFI()** function, however if using a button to wake up from this mode it restarts the program from main. This would not be an issue if we had multiple buttons, but the PCB we were given only has one programmable button (the RESET button cannot be programmed easily). Setting this button as an interrupt means that every time it is pressed, the interrupt function overwrites it's original functionality, so when we tested this code, the LEDs no longer increased in brightness when the button was pressed. A solution for future iterations of the project would be to add another button to the PCB, but obtaining these new boards was out of the timescale of our project. I documented the code that worked with the button interrupt in the [button wakeup](../../code/8_Button_Wakeup.c) file, so if another button is added the pin number can easily be adjusted and this code can be implemented with very little additional work.

As a proof of concept, I implemented a periodic wakeup system where the mcu wakes itself up from standby mode every 10 seconds with an timed interrupt, and the working code is shown in the [periodic wakeup](../../code/9_Periodic_Wakeup.c) file. The amount of time the mcu is asleep for it set by the **standbyConfig()** function, explained in the Curious Scientist blog on using Low Power Modes with the CH32V003 microcontroller family (see references). This means that the mcu periodically wakes up, checks the battery voltage, and goes back to sleep if it has not risen above 3.2V. This reduces power used by the mcu and can be further improved by increasing the period of time that the mcu is switched off. However, this comes with the tradeoff that there is no user input available to wake the mcu, so once it is asleep the user has to wait until it wakes up if they want to use the light. This is quite impractical so I think the best solution moving forwards is to add another button to the board, so the mcu can remain asleep until woken by the user pressing the button. 

### Cost Reduction

WS2812 LED is a programmable LED, aiming to replace the 3 separate red, orange and green LEDs. It is controlled by input data stream of 24 bits, 8 bits for red, 8 bits for green, 8 bits for blue so precise timing is required to send the colour signals. 

My level of coding experience meant coding the individual on/off timing signals wouild take a LOT longer than four weeks, so I tried to find a library that would allow me to program this LED. The only library I could find that worked with this microcontroller was from Github and can be found in the [RGB LED folder](../../code/RGBLED) in our code folder. This library is usually used for a string of LEDs, so some edits needed to be made to set the number of LEDs and ensure the LED was initialised as the correct pin. The main file and relevant header files are all included into the folder and the LED lit up on the smaller bpard, so it should not be too much work to integrate it onto the bigger board. 

If anyone uses this code in the future, I would recommend testing it on the smaller boards first. I tried to integrate this code onto a bigger board, but when I uploaded the code to the bigger board with a battery, it ended up melting the inductor because there is no protection against the maximum inductor current. I learnt this lesson the hard way, but hopefully including this failure in the report means anyone working on the RGB LED in the future won't make the same mistake!


## Miscalleneous Fixes

### Inductor Overheating

One of the first challenges I faced during the project was trying to prevent the board from overheatig. When the battery was initially connected to the bigger boards, the electronics became too hot to touch almost instantaneously and we concluded that this was not good for the long term use of the board and could be a potential fire hazard. I suspected that the inductor was being overloaded with current, so I changed the overvoltage parameters in Noam's original board to account for this. 

I struggled to find a value online for the maximum value of the inductor so decided to experimentally determine a safe ADC maximum voltage parameter. In Noam's code, the overvoltage and target voltage parameters are defined as raw ADC values, which correspond to voltages. By reducing the target ADC value from 300 to 250, and reducing the max parameter from 350 to 300, the circuit no longer overheated and it was then safe to leave the battery in the board for a prolonged period of time. Following Noam's advice, I measured the output voltage of the USB and was getting an average value of around 4.2V, which is lower than the 5V maximum, so this is a functioning solution. 

### Board Blown

Another issue we had with one of the boards is that it was soldered incorrectly when we received it. These images show where the Q2 chip is supposed to be soldered vs where it is actually soldered, and it is clearly offset. We originally didn't notice this issue, but when a battery was connected the board began smoking so we immediately unplugged it and inspected it to find the issue. For future iterations of the project I would advise thoroughly checking that all components of the board are correctly soldered to minimise risk of this happening again. 

## Next Steps

The current product that we have is useable, but there are several improvements to be made relating to sleep mode. 

- Add another button to the PCB to enable user triggered interrupts
  - Set up second button as interrupt (using [Button Wakeup Code](../../code/8_Button_Wakeup.c))
  - Sleep mode can then be triggered indefinitely without relying on periodic wakeup

- Finalise solar cutoff voltage testing in Ethiopian sun
- Test USB port for phone charging

Additional cost reduction extras can include replacing the three red, orange and green LEDs with the single RGB programmable LED.
- The [code for lighting up the RGB LED](../../code/RGBLED/main.c) can be further modified
        - We modified the code to include the correct pins but ran out of time to change it's colour
        - This code is a good starting point for using the WS2812 library on the CH32V003F4P6
- The header files included in the [RGB LED folder](../../code/RGBLED) must also be included in the User folder in MounRiver Studio for the main file to run       
 









## References

Battery discharge cutoff voltage https://www.amazon.co.uk/PKCELL-900mah-ICR18350-Rechargeable-Battery/dp/B0897RCSYV?ref_=ast_sto_dp
Low power mode blog https://curiousscientist.tech/blog/ch32v003j4m6-low-power-modes


