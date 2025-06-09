# Code

This section contains the multiple iterations of code that we completed throughout the project.

## 0 Initial Code
Code we received from Noam. Can be found in the initial documentation section. 

## 1 Multichannel ADC
This code initialises a multichannel ADC so we can print values from the 4 channels **FB_USB**, **FB_BAT**, **FB_SOLAR** and **FB_LED**. This requires the following four functions:
- **calculateVoltage**(uint16_t ADCbits) to convert the raw digital ADC value to a float between 0 and 1 that can then be scaled
- **ADC_MultiChannel_Init(void)** function to initialise the multi channel ADC and set up the 4 channels and pins
- **DMA_Tx_Init**(DMA_Channel_TypeDef *DMA_CHx, uint32_t peripheralAddress, uint32_t memoryAddress, uint16_t bufferSize) to initialise direct memory access
-  **printMultiChannelADC()** function which includes the scaling and printing of the 4 values from each channel

## 2 Battery Status
In main loop, code has been added to set the red, orange and green LEDs based on the battery voltage (yet uncalibrated)

## 3 Calibration
We used a voltmeter to measure the voltage across the battery for multiple readings, plotted a linear graph to work out the scaling factor and set BATmultiplier to the correct value, so FB_BAT now prints the correct battery voltage.

## 4 Returning Multiple Channels
In the Calibration code, we relied on returning calibratedBAT from the **printMultiChannelADC()** function, which was a temporary solution, because in C only one value can be returned per function. If we continued to use **printMultiChannelADC()** we would only be able to return one value, but we need four values. This new code now introduced 4 separate functions: **printFB_BAT**, **printFB_USB**, **printFB_SOLAR**, **printFB_LED** which each return the single corresponding value. This means we can now hopefully utilise the solar panel voltage in the next iteration. 

## 5 Averaging
There is quite a lot of fluctuation between each of the FB values, so we implemented an averaging code that takes a number of samples and finds the average across them to try and minimise fluctuations. 

## 6 Sleep Mode Test
This code shows successful sleep mode implementation. The __WFI() command was behaving unexpectedly and does not work with this microcontroller so replaced it with **PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);** which reinitialises the code from the start of main, which solves the problems we were facing originally. Next step is to hopefully implement sleep mode with the longer code. 

## 7 Reordered and commented
This code is reorded in an order that makes logical sense and we also commented everything so we understand all elements of the code going forward. 

## 8 Button WakeUp
This was the first time we tried to use the button to wake up the mcu from sleep mode on the bigger board. Problem with this code is that this standby mode reinitialises main every time, which does not work with the button press because all previous information about button LED levels is lost, so the button loses functionality and becomes purely an interrupt trigger. If we had multiple buttons, could easily set one as the interrupt wake up and the other as the LED brightness increaser.... but there is only one available push button. This makes it impossible to wake up the mcu with the button whilst maintaining functionality of the device, so need to investigate another way of waking up the device. 

## 9 Periodic WakeUp
In this version of the code, the button is no longer an interrupt so it is now functional in increasing the brightness of the LEDs and showing the battery voltage. This code measures the battery voltage, and if it is less than 3.2V it sends the microcontroller into standby mode. There is then a periodic wakeup cycle of 10 seconds, where the mcu wakes up, runs through the while loop to check if the battery voltage has increased, and if not it goes back to sleep. If the battery voltage has increased, it escapes the while loop and continues operating normally which is good. 
The issue with this code is that when the button is pressed to increase the brightness of the LEDs, the measured battery voltage coming from FB_BAT decreases (to around 2.9V for the maximum LED setting). This means the microcontroller then goes to sleep whilst the LEDs are stuck on their brightest setting, which is bad. I have added code to switch off the LEDs and PWM_USB when entering sleep mode, but still needs some work. 

## 10 Averaging
Neatened up the functions for averaging each of the 4 channels USB, BAT, SOLAR and LED. Condensed the print functions into more simple **getFB** and a more general **printFB** function which is used to print the floats as integers. 

## 11 Extra Power Conservation
Added solar detector code which switches LEDs off when solar ADC value goes below a certain value (0.27 was measured as threshold voltage but is quite temperamental). 
Also added code that send mcu to sleep if LEDmode is 0 for over 2 minutes. This is currently commented because it is a bit pointless without having a second interrupt button). 


