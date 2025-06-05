#include "debug.h"

void GPIOConfig()
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  // Only if you need PD0 as input
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //input pull up means button originally set as low
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void EXTI0_INT_INIT(void)
{
    EXTI_InitTypeDef EXTI_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource0);  //sets button as interrupt trigger

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //button is initially set as low, so rising triggers interrupt
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI7_0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */



volatile int buttonPressed = 0;  // Shared between ISR and main
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    Delay_Ms(2000); //prevents blocking the board (can reset with 5 seconds spare to upload the code)
    GPIOConfig();
    EXTI0_INT_INIT();
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_RESET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_SET);
    Delay_Ms(100);
    GPIO_WriteBit(GPIOC, GPIO_Pin_3, Bit_RESET);


    while(1)
      {
        Delay_Ms(100);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
        if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) == 0)
        {

                GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
                Delay_Ms(2000);
                GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
                PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE); //this restarts the code from main (reinitialises the code)


        //__WFI(); // <- this doesn't work it is rubbish


        }

    }
}

void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH_Interrupt-fast")));

void EXTI7_0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {

        EXTI_ClearITPendingBit(EXTI_Line0);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
        Delay_Ms(10);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);

    }
}
