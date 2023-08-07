#include "ADC.h"
#include "Output.h"
void SystemInit() {}
void send_output() // wet 2050
{
    if (ADC_value > 2050)
    {
        GPIO_PORTA_DATA_R = 1 << 4;
        GPIO_PORTF_DATA_R = 1 << 2;
    }
    else
    {
        GPIO_PORTA_DATA_R = 0;
        GPIO_PORTF_DATA_R = 0;
    }
}

int main(void)
{

    ADC_Init(); // Initialize the ADC Module
    output_gpio_init();

    while (1)
    {

        get_moisture_level();
        send_output();
    }
}