# Electrical Interim Report

## RGB LED
- WS2812 LED is a programmable LED, aiming to replace the 3 separate red, orange and green LEDs.
- Controlled by input data stream of 24 bits, 8 bits for red, 8 bits for green, 8 bits for blue.
- Precise timing is required to send the colour signals.
    - This is very difficult to do with limited prohgramming experience and time
    - There is one demo code on GitHub containing the header files with functions that allow the light up, so by changing the pins and ports in this code, we managed to get the RGB LED to light up
    - The library on Github is difficult to implement for a single LED, beccuase it is written for a strip of LEDs so lots of the code can be removed.

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
We started by focusing on the first functionality requirement, which is the LEDs showing the battery status when the button is pressed. This required an understanding of the circuit diagram and to measure the voltage of the battery by initialising a multichannel ADC. We had several "technical difficulties" along the way but managed to solve them as we went along.  
### Multichannel ADC 
In order to read the voltage across the battery, we needed to use the microcontroller to read the value of FB_BAT (battery feedback). The code Noam gave to us utilized a single channel ADC, but this was already being used to control the USB voltage using PWM_USB. To read the battery voltage we required a multichannel ADC, which was more complicated to implement. 

![image](https://github.com/user-attachments/assets/ae9cc546-1e46-4e4b-9c72-b2959458f47c)

![image](https://github.com/user-attachments/assets/4961bb11-972c-4994-9d05-b39819355a00)

#### ADC_MultiChannel_Init
There are 4 sampling channels available from the circuit diagram which we can access with the microcontroller by initialising a multichannel ADC. 
  - FB_USB (PC4/A2) Channel 1
  - FB_SOLAR (PA2/A0) Channel 2
  - FB_BAT (PD4/A7) Channel 3
  - FB_ILED (PD3/A4) Channel 4
 
  
void ADC_MultiChannel_Init(void) //multi channel ADC initialisation
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOA, ENABLE); //sets up clocks for ports A, C, D
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);
    
    //initialise 4 pins for 4 channels of multichannel ADC

    GPIO_InitStructure.GPIO_Pin = FB_USB;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //GPIO mode is AIN = Analogue INput
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = FB_SOLAR;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = FB_BAT;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = FB_ILED;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    ADC_DeInit(ADC1);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 4;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_241Cycles);  //FB_USB = Channel 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 2, ADC_SampleTime_241Cycles);  //FB_SOLAR = Channel 2
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_241Cycles);  //FB_BAT = Channel 3
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_241Cycles);  //FB_ILED = Channel 4


    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

#### DMA (Direct Memory Access) 
This code enables the 4 channel values to be stored in a buffer, as far as I can tell the multichannel ADC does not work without this function. 

void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, uint32_t peripheralAddress, uint32_t memoryAddress, uint16_t bufferSize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = peripheralAddress;
    DMA_InitStructure.DMA_MemoryBaseAddr = memoryAddress;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);
}

#### Printing the Values
Printing the values from a multichannel ADC is more complicated because you cannot directly print a float in C, so have to convert each number to an integer and print it so it looks like an integer. We found that the ADC values fluctuated a lot, so implemented an average across 2000 samples for each readign to try and reduce this fluctuation, which worked successfully. Separate scaling factors were required for each value, so far we have only done FB_BAT but are looking to calibrate the others in the remaining project time. 

float printADCVoltage_Multi()
{
    int x;
    int numsamples = 2000;
    float avgVoltage = 0;

    //calibration voltages
    float USBmultiplier = 1;
    float SOLARmultiplier = 1;
    float BATmultiplier = 10.283;
    float LEDmultiplier = 1;
    for(int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            for(x=0; x<numsamples; x++)//calculate average FB_USB
                    {
                        avgVoltage = avgVoltage + adcVoltage;
                    }
             avgVoltage = avgVoltage/numsamples;
            float calibratedUSB = avgVoltage * USBmultiplier;
            int wholePart = (int)calibratedUSB;
            int decimalPart = (int)((calibratedUSB - wholePart) * 10000);
            printf("FB_USB (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
         }
        if (i == 1)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            for(x=0; x<numsamples; x++)//calculate average FB_USB
                    {
                        avgVoltage = avgVoltage + adcVoltage;
                    }
                    avgVoltage = avgVoltage/numsamples;
            float calibratedSOLAR = avgVoltage*SOLARmultiplier;
            int wholePart = (int)calibratedSOLAR;
            int decimalPart = (int)((calibratedSOLAR - wholePart) * 10000);
            printf("FB_SOLAR (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
        }
        if (i == 2)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            for(x=0; x<numsamples; x++)//calculate average FB_USB
                    {
                        avgVoltage = avgVoltage + adcVoltage;
                    }
                    avgVoltage = avgVoltage/numsamples;
            calibratedBAT = avgVoltage*BATmultiplier;
            int wholePart = (int)calibratedBAT;
            int decimalPart = (int)((calibratedBAT - wholePart) * 10000);
            printf("FB_BAT (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
        }
        if (i == 3)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            for(x=0; x<numsamples; x++)//calculate average FB_USB
                    {
                        avgVoltage = avgVoltage + adcVoltage;
                    }
                    avgVoltage = avgVoltage/numsamples;
            float calibratedLED = avgVoltage*LEDmultiplier;
            int wholePart = (int)calibratedLED;
            int decimalPart = (int)((calibratedLED - wholePart) * 10000);
            printf("FB_ILED (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
        }

    }
    return calibratedBAT;
}


### Board Breakages
We have encountered some issues with the boards

![image](https://github.com/user-attachments/assets/cd3468f7-cbba-4cb9-ae70-af91ca5d3b0d)



#### Inductor Heating
When touching the board, the inductor was very hot and in danger of melting from an overload of current. Firstly we had to fix the original code to the correct ADc pin because it wasn't working: when we read the PWM values on the serial monitor it did not really make sense (the PWM changing did not seem to affect the ADC voltage). This meant that the PWM was actually effective in changing the voltage measured by the single channel ADC. We then decreased the limiting ADC value from 350 to 300 which prevents the voltage from reaching a value that is too high, so the inductor now doesn't get too hot, minimising heat loss. 

Having successfully transferred the RGB LED code to a small board, we upgraded it to a big board and added a battery and it blew the board: there is no voltage regulation in the LED code so it is important when adding the battery to ensure that it is inside the original code to prevent overheating of the components. 

#### Chip Destruction
When we connected the battery to one of the bigger boards, it began smoking because one of the chips was overheating. After some confusion, we noticed that the chip had actually been soldered incorrectly onto the board. This highlighted an issue in the PCB manufacturing, so we may need to look into methods of control checking the boards so this doesn't happen again. This is concerning because we only now have 3 remaining functional big boards. 


<img src="https://github.com/user-attachments/assets/da978993-de49-47fe-be59-8c181bb56fc5" width="300"/>

<img src="https://github.com/user-attachments/assets/412afd88-5d04-401a-b51b-9545bce101cc" width="300"/>



#### Explosive Batteries
We had some confusion when the voltmeter had a reading of 5.2V for our rechargeable 3.7V batteries, which is well above their safety limit. We initially panicked, but after a while of researching what to do if your battery explodes, we tried a different voltmeter and worked out that the original voltmeter was wrong. This taught us a valuable lesson in not always trusting the equipment and thinking outside the box to try and solve the problems.  
