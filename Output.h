
#define GPIO_PORTF_DATA_R (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long *)0x4002551C))
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *)0x400FE608))
#define GPIO_PORTA_DATA_R (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_DEN_R (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_DR8R_R (*((volatile unsigned long *)0x40004508))
#define GPIO_PORTF_DR8R_R (*((volatile unsigned long *)0x40025508))

void output_gpio_init(void)
{
    volatile unsigned int temp = 0;
    SYSCTL_RCGCGPIO_R |= 1 << 0 | 1 << 5;
    temp += 1;
    GPIO_PORTA_DEN_R = 1<<4;
    GPIO_PORTF_DEN_R = 0x4;
    GPIO_PORTA_DIR_R = 1<<4;
    GPIO_PORTF_DIR_R = 0x4;
    GPIO_PORTA_DR8R_R = 1<<4;
}
