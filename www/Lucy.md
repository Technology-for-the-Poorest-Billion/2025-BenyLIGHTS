# Programming the CH32V003F4P6 Microcontroller

## Button Press

## Power Conservation Improvements

### Sleep Mode and Standby Mode

The overall goal of sleep mode is to conserve power and prevent the battery discharging lower than the safe level. The project uses 3.7V rechargeable batteries, which should not be discharged below their discharge cut-off voltage of 3V. To prevent batteries dropping below this charge level, the microcontroller (mcu) should go into sleep mode when the battery voltage drops below 3.2V. 

The function **getFB_BAT()** is used to read the battery voltage, and convert the raw ADC value into a voltage using a  multiplier. This is then averaged using a **for** loop within the main loop to return the float **avg_bat**. If **avg_bat** falls below 3.2V, the mcu goes to sleep, using the line **PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);**. 

The challenge in implementing this section arose when trying to wake the mcu up from sleep mode. Initially, we set the push button as an interrupt to wake the mcu up, which required use of the **__WFI()** function. The interrupt worked perfectly without the **__WFI()** line, but when **__WFI()** was introduced the mcu would only wake up the first two times, and then would remain asleep no matter how many times the button was pressed. This appeared to be because the 2nd button press was not going through the interrupt sequence, so the flag was not being reset, which is an internal issue of the **__WFI()** function itself. 

An alternative solution was to use a deeper sleep mode called standby mode, called using the function **PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);**, however if using a button to wake up from this mode it restarts from main. This would not be an issue if we had multiple buttons, but the PCB we were given only has one programmable button (the RESET button cannot be programmed easily). Setting this button as an interrupt means that every time it is pressed, the interrupt function overwrites it's original functionality, so when we tested this code, the LEDs no longer increased in brightness when the button was pressed. A solution for future iterations of the project would be to add another button to the PCB, but obtaining these new boards was out of the timescale of our project. 

As a proof of concept, I implemented a periodic wakeup system where the mcu wakes itself up every 10 seconds with an timed interrupt, set by the **standbyConfig()** function, explained in the Curious Scientist blog on using Low Power Modes with the CH32V003 microcontroller family. This means that the mcu periodically wakes up, checks the battery voltage, and goes back to sleep if it has not risen above 3.2V. This reduces power used by the mcu and can be further improved by increasing the period of time that the mcu is switched off. However, this comes with the tradeoff that there is no user input available to wake the mcu, so once it is asleep the user has to wait until it wakes up if they want to use the light. This is quite impractical so I think the best solution moving forwards is to add another button to the board, so the mcu can remain asleep until woken by the user pressing the button. 

### Sun Detection


    











https://curiousscientist.tech/blog/ch32v003j4m6-low-power-modes




## References

Battery discharge cutoff voltage https://www.amazon.co.uk/PKCELL-900mah-ICR18350-Rechargeable-Battery/dp/B0897RCSYV?ref_=ast_sto_dp


