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
In main loop, code has been added to set the red, orange and green LEDs based on the battery coltage (yet uncalibrated)

## 3 Calibration
We used a voltmeter to measure the voltage across the battery for multiple readings, plotted a linear graph to work out the scaling factor and set BATmultiplier to the correct value, so FB_BAT now prints the correct battery voltage.

## 4 Returning Multiple Channels
In the Calibration code, we relied on returning calibratedBAT from the **printMultiChannelADC()** function, which was a temporary solution, because in C only one value can be returned per function. If we continued to use **printMultiChannelADC()** we would only be able to return one value, but we need four values. This new code now introduced 4 separate functions: **printFB_BAT**, **printFB_USB**, **printFB_SOLAR**, **printFB_LED** which each return the single corresponding value. This means we can now hopefully utilise the solar panel voltage in the next iteration. The averaging was removed, because it was ineffective. 
