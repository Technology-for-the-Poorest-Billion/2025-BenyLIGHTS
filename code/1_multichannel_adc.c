/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : NOAM
 * Version            : V1.0.0
 * Date               : 21.4.25
 * Description        : Main program body.


/*
 *@Note
 * 6_six_PWM output routine:
 * TIM1_CH1(PC4) TIM1_CH1N(PC3)
 * TIM1_CH2(PC7) TIM1_CH2N(PD2)
 * TIM1_CH2(PC5) TIM1_CH3N(PC6)
 * Only advanced timer (channel 1,2,3) have this function.
*/

#include "debug.h"
uint16_t ADCBuffer[4];          //define ADC buffer to hold channel readings
#define RED GPIO_Pin_3          //port C
#define YLW GPIO_Pin_6          //port C
#define GRN GPIO_Pin_7          //port C
#define PWM_OUT GPIO_Pin_0      //port C OUT means output from the microcontroller in this context
#define PWM_OUT_TIM TIM1        //RCCAPB1 if change timer
#define PWM_LED_TIM TIM2        //RCCAPB2 if change timer
#define PWM_LED GPIO_Pin_1      //port C
#define ADC_OUT GPIO_Pin_4      //port ADC
#define Key GPIO_Pin_0          //port D
#define FB_USB GPIO_Pin_4       //port C
#define FB_SOLAR GPIO_Pin_2     //port A
#define FB_BAT GPIO_Pin_4      //port D
#define FB_ILED GPIO_Pin_3     //port D
#define FIVE_V_EN GPIO_Pin_1   //port A

/* PWM Output Mode Definition */
#define PWM_MODE1   0
#define PWM_MODE2   1

/* PWM Output Mode Selection */
//#define PWM_MODE PWM_MODE1
#define PWM_MODE PWM_MODE2



void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );
    GPIO_InitStructure.GPIO_Pin = Key;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init( GPIOD, &GPIO_InitStructure);
}

void InitTimer1( u16 arr, u16 psc, u16 ccp ) //PWM OUT with TIM1
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE );
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = PWM_OUT;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( PWM_OUT_TIM, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init( PWM_OUT_TIM, &TIM_OCInitStructure );


    TIM_CtrlPWMOutputs(PWM_OUT_TIM, ENABLE );
    TIM_OC3PreloadConfig( PWM_OUT_TIM, TIM_OCPreload_Enable );
    TIM_ARRPreloadConfig( PWM_OUT_TIM, ENABLE );

    TIM_Cmd( PWM_OUT_TIM, ENABLE );
}

void InitTimer2(u16 arr, u16 psc, u16 ccp)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = PWM_LED;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( PWM_LED_TIM, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OC1Init( PWM_LED_TIM, &TIM_OCInitStructure );

    TIM_CtrlPWMOutputs(PWM_LED_TIM, ENABLE );
    TIM_OC1PreloadConfig( PWM_LED_TIM, TIM_OCPreload_Disable );
    TIM_ARRPreloadConfig( PWM_LED_TIM, ENABLE );

    TIM_CCPreloadControl(PWM_LED_TIM, ENABLE);//CCPC
    TIM_SelectCOM(PWM_LED_TIM, ENABLE);//CCUS

    TIM_Cmd( PWM_LED_TIM, ENABLE );
}

void initialADC()
{
    ADC_InitTypeDef ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = ADC_OUT;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; //single channel
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //continues sample
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //no ext trigger
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1; //# of channels
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 1, ADC_SampleTime_241Cycles);
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
float calculateVoltage(uint16_t ADCbits)
{
    float vref = 4.2f;
    float adcVoltage = (vref * 5 * ADCbits)/1024.0f;
    return adcVoltage;
}

void ADC_MultiChannel_Init(void)//new code for multiple channels
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = FB_USB;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
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

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_241Cycles);//FB_USB
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 2, ADC_SampleTime_241Cycles);//FB_SOLAR
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_241Cycles);//FB_BAT
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_241Cycles);//FB_ILED


    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

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

/*void printADCVoltage_Multi()
{
    for(int i = 0; i < 4; i++)
    {
        float adcVoltage = calculateVoltage(ADCBuffer[i]);
        int wholePart = (int)adcVoltage;
        int decimalPart = (int)((adcVoltage - wholePart) * 10000);
        printf("Channel - %d : %d.%04d ",i+1 , wholePart, decimalPart);
    }
    printf("\n");
}*/

void printADCVoltage_Multi()
{
    for(int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            int wholePart = (int)adcVoltage;
            int decimalPart = (int)((adcVoltage - wholePart) * 10000);
            printf("FB_USB (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
         }
        if (i == 1)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            int wholePart = (int)adcVoltage;
            int decimalPart = (int)((adcVoltage - wholePart) * 10000);
            printf("FB_SOLAR (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
        }
        if (i == 2)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            int wholePart = (int)adcVoltage;
            int decimalPart = (int)((adcVoltage - wholePart) * 10000);
            printf("FB_BAT (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
        }
        if (i == 3)
        {
            float adcVoltage = calculateVoltage(ADCBuffer[i]);
            int wholePart = (int)adcVoltage;
            int decimalPart = (int)((adcVoltage - wholePart) * 10000);
            printf("FB_ILED (Channel - %d) : %d.%04d ",i+1 , wholePart, decimalPart);
        }
    }
}

void initialGPIO(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    // Configure the GPIO pins for output

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz; //can be also GPIO_Speed_50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE); // Enable GPIOC and GPIOA clock

    GPIO_InitStructure.GPIO_Pin = PWM_LED ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = RED ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = YLW ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GRN ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = FIVE_V_EN ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*********************************************************************
 * @fn      KEY_PRESS
 *
 * @brief   Key processing function.
 *
 * @return  every time the function is called in case KEY is pressed KeyTimePress++, otherwise 0
            when reaching KeyTimePress=KeyMinPress (should be at least 50ms) clamp
 */

int KEY_PRESS(int KeyTimePress, int KeyMinPressCalc)
{
    if (KeyTimePress < KeyMinPressCalc)
    {
        if (GPIO_ReadInputDataBit(GPIOD,Key) == 0)
        {
            KeyTimePress = 0;
            return KeyTimePress;
        }
        if (GPIO_ReadInputDataBit(GPIOD,Key) == 1)
        {
            if (KeyTimePress < KeyMinPressCalc+1)
            {
                KeyTimePress++;
                return KeyTimePress;
            }
            else return KeyTimePress;
        }
    }
    return 0;
}

int KEY_UNPRESS(void)
{
    if (GPIO_ReadInputDataBit(GPIOD,Key) == 1) return 1;
    else return 0;
}


/*********************************************************************



/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */



int main(void)
{

    // need to set SYSCLK_FREQ_48MHZ_HSI to 48M in system_ch32v00x.c
    SystemCoreClockUpdate(); // Initialize system clocks and peripherals at 48MHz
    Delay_Init();
    initialGPIO();


#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );


    InitTimer1( 240, 0, 0 ); //Tsw is 240 is 10us, 0 is the prescale (48MHz), 20 is 20/240 which is 8.3%
    InitTimer2( 240, 0, 0 );

    initialADC();
    ADC_MultiChannel_Init();
    DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)ADCBuffer, 4);//if changing number of channels, need to change 4 to different number
    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    int SystemDelay = 10; //10ms every cycle


    //OUT voltage regulation
    int targetADC = 250; //had to change the target voltage for the ADC because the inductor was over heating
    int HystADC = 5;
    int HystADC_big = 10;
    int ADC_OV = 300;

    //OUT
    float PWM_Value;
    int PWMwhole;
    int PWMdec;
    int PWM_USB_VALUE = 0; //the PWM value

    //ADC
    int j = 0;
    int samples = 2000;
    float adcVoltageValue;
    long int ADCintValue;
    int ADCintValuePrint;
    int ADCwhole;
    int ADCdec;

    //signal LED
    int i = 0;
    int change_LED = 60;

    //KEY
    int KeyMinPress = 50; //in ms
    int KeyMinPressCalc = KeyMinPress/SystemDelay;
    int KeyTimePress = 0;
    int KeyPressed = 0;

    //LED
    int LED_steps = 5;
    int PWM_LED_VALUE = 0; //the PWM value
    int LEDmode = 0;


    while(1)
    {
        i++;
        //Every cycle delay time
        Delay_Ms(SystemDelay);
        GPIO_WriteBit(GPIOA, FIVE_V_EN, Bit_SET); //ensuring the MT3540 chip is enabled at all times
        ///////////////////////////////////KEY///////////////////////////////////////
        //when KeyTimePress > KeyMinPressCalc it is considered a key pressed
        if(!KeyPressed)
        {
            KeyTimePress = KEY_PRESS(KeyTimePress,KeyMinPressCalc);
            if(KeyTimePress == KeyMinPressCalc )
            {
                KeyPressed = 1;
                if(LEDmode<LED_steps)
                {
                    LEDmode++;
                }
                else LEDmode = 0;
            }
        }
        else KeyPressed=KEY_UNPRESS(); //waiting for Key to be unpressed

        PWM_LED_VALUE = LEDmode*100/LED_steps; //steps out of 100%
        ///////////////////////////////////KEY///////////////////////////////////////


        ADCintValue = 0;
        for(j=0; j<samples; j++)
        {
            ADCintValue = ADCintValue + ADC_GetConversionValue(ADC1);
        }
        ADCintValue = ADCintValue/samples; //finding the average value of the ADC over 2000 samples
        ADCintValuePrint = ADCintValue;
        //ADCintValue = ADC_GetConversionValue(ADC1);
        // ADC of 221 is 4.532V (4.2*5/1024 = 0.02) --> 221*0.02=4.42
        // ADC of 344 is 7.054V (4.2*5/1024 = 0.02) --> 334*0.02=6.68
        adcVoltageValue = 4.2f * (5.0f  * ADCintValue)/1024.0f; //why multiplied by 4.2 and 5?

        //allows the ADC value to be printed as a float
        ADCwhole = (int) adcVoltageValue;
        ADCdec = (int) ((adcVoltageValue - ADCwhole)*1000);

        PWM_Value = (100.0f*PWM_USB_VALUE)/240.0f;
        PWMwhole = (int) PWM_Value;
        PWMdec = (int) ((PWM_Value-PWMwhole)*1000);
        //printf("ADC value is %d.%0.3d and PWM is %d \n",ADCwhole,ADCdec,i);
        printADCVoltage_Multi();

        //print data eg ADC raw data is 221 (4.42V), PWM is
        printf("ADC raw data is %d (%d.%0.3dV), PWM is %d (%d.%0.3d) and Mode is %d/%d (%d/%d), LEDs are %d \n",ADCintValuePrint, ADCwhole, ADCdec , PWM_USB_VALUE, PWMwhole,PWMdec,LEDmode,LED_steps,KeyTimePress,KeyMinPressCalc,i);


        /*if(ADCintValue > 5*50 && !reachRED)
        {
            reachRED = 1;
            printf("RED \n");
            //GPIO_WriteBit(GPIOC, RED, Bit_SET);
            GPIO_WriteBit(GPIOC, YLW, Bit_RESET);
            //GPIO_WriteBit(GPIOC, GRN, Bit_RESET);
        }

        if(ADCintValue > 6*50 && !reachYLW)
        {
            reachYLW = 1;
            printf("YLW \n");
            //GPIO_WriteBit(GPIOC, RED, Bit_SET);
            GPIO_WriteBit(GPIOC, YLW, Bit_SET);
            //GPIO_WriteBit(GPIOC, GRN, Bit_RESET);
        }

        if (ADCintValue > 7*50 && !reachGRN)
        {
            reachGRN = 1;
            printf("GRN \n");
           // GPIO_WriteBit(GPIOC, RED, Bit_SET);
            GPIO_WriteBit(GPIOC, YLW, Bit_SET);
            //GPIO_WriteBit(GPIOC, GRN, Bit_SET);
        }


        if (ADCintValue < 5*50)
        {
            reachGRN = 0;
            reachYLW = 0;
            reachRED = 0;
            printf("low \n");
            //GPIO_WriteBit(GPIOC, RED, Bit_RESET);
            GPIO_WriteBit(GPIOC, YLW, Bit_RESET);
            //GPIO_WriteBit(GPIOC, GRN, Bit_RESET);
        }*/

        if(i == change_LED)
        {
            i=0;
            if(GPIO_ReadOutputDataBit(GPIOC, GRN) == Bit_SET)
            {
                if(GPIO_ReadOutputDataBit(GPIOC, YLW) == Bit_SET)
                {
                    if(GPIO_ReadOutputDataBit(GPIOC, RED) == Bit_SET)
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_RESET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_RESET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_RESET);
                    }
                    else
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_SET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_RESET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_RESET);
                    }
                }
                else
                {
                    if(GPIO_ReadOutputDataBit(GPIOC, RED) == Bit_SET)
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_SET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_SET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_RESET);
                    }
                    else
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_RESET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_SET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_RESET);
                    }
                }
            }
            else
            {
                if(GPIO_ReadOutputDataBit(GPIOC, YLW) == Bit_SET)
                {
                    if(GPIO_ReadOutputDataBit(GPIOC, RED) == Bit_SET)
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_SET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_SET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_SET);
                    }
                    else
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_RESET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_SET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_SET);
                    }
                }
                else
                {
                    if(GPIO_ReadOutputDataBit(GPIOC, RED) == Bit_SET)
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_SET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_RESET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_SET);
                    }
                    else
                    {
                        GPIO_WriteBit(GPIOC, RED, Bit_RESET);
                        GPIO_WriteBit(GPIOC, YLW, Bit_RESET);
                        GPIO_WriteBit(GPIOC, GRN, Bit_SET);
                    }
                }
            }

        }


        if (ADCintValue>ADC_OV)
        {
            printf("emergency DOWN     ");
            PWM_USB_VALUE = 0;
        }

        if(PWM_USB_VALUE == 110)
        {
            printf("PWM too high       ");
            PWM_USB_VALUE=0;
        }

        if(ADCintValue<targetADC-HystADC)
        {
            printf("UP        ");
            PWM_USB_VALUE++;
        }

        if(ADCintValue>targetADC+HystADC)
        {
            if(PWM_USB_VALUE>0)
            {
                printf("DOWN     ");
                PWM_USB_VALUE--;
            }
        }

        if (ADCintValue>targetADC+HystADC_big)
        {
            if(PWM_USB_VALUE>10)
            {
                printf("big DOWN     ");
                PWM_USB_VALUE = PWM_USB_VALUE-10;
            }
            else
            {
                PWM_USB_VALUE = 0;
            }

        }

        InitTimer2( 100, 0, PWM_LED_VALUE );
        InitTimer1( 240, 0, PWM_USB_VALUE );
        TIM_GenerateEvent(PWM_OUT_TIM, TIM_EventSource_COM);
        TIM_GenerateEvent(PWM_LED_TIM, TIM_EventSource_COM);
    }
}
