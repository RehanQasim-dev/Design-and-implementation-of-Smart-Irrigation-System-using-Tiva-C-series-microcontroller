
#define SYSCTL_RCGCADC_R (*((volatile unsigned long *)0x400FE638))
#define SYSCTL_RCGC_GPIO_R (*((volatile unsigned long *)0x400FE608))
// port B
#define GPIO_PORTE_DATA_R (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_AMSEL_R (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_DEN_R (*((volatile unsigned long *)0x4002451C))

#define ADC0_ACTSS_R (*((volatile unsigned long *)0x40038000))
#define ADC0_RIS_R (*((volatile unsigned long *)0x40038004))
#define ADC0_IM_R (*((volatile unsigned long *)0x40038008))
#define ADC0_ISC_R (*((volatile unsigned long *)0x4003800C))
#define ADC0_EMUX_R (*((volatile unsigned long *)0x40038014))
#define ADC0_USTAT_R (*((volatile unsigned long *)0x40038018))
#define ADC0_TSSEL_R (*((volatile unsigned long *)0x4003801C))
#define ADC0_SSPRI_R (*((volatile unsigned long *)0x40038020))
#define ADC0_SPC_R (*((volatile unsigned long *)0x40038024))
#define ADC0_PSSI_R (*((volatile unsigned long *)0x40038028))
#define ADC0_SAC_R (*((volatile unsigned long *)0x40038030))
#define ADC0_CTL_R (*((volatile unsigned long *)0x40038038))
#define ADC0_SSMUX3_R (*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3_R (*((volatile unsigned long *)0x400380A4))
#define ADC0_SSFIFO3_R (*((volatile unsigned long *)0x400380A8))
#define ADC0_PC_R (*((volatile unsigned long *)0x40038FC4))

unsigned int ADC_value = 0;

// Function prototypes and variables
void ADC_Init(void);
void Delay(volatile unsigned int delay);

// Intialization routine for setting up the required ports
void ADC_Init(void)
{
    volatile unsigned long delay;

    SYSCTL_RCGC_GPIO_R |= 1 << 4;
    // Enable the clock for ADC0
    SYSCTL_RCGCADC_R |= 0x01;

    // Delay for clock signal to settle down
    delay = SYSCTL_RCGCADC_R;
    GPIO_PORTE_AFSEL_R = 1 << 3;

    // 4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
    // GPIO Digital Enable (GPIODEN) register (see page 682).
    GPIO_PORTE_DEN_R &= ~(1 << 3);

    // 5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
    // the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
    GPIO_PORTE_AMSEL_R = 1 << 3;

    // Configure portA and portB for Seven segments
    // ADC0 configuration

    // Clear the sample rate
    ADC0_PC_R &= 0x00; // ADC Peripheral COntrol register
    // Set sample rate equal to 125 ksps
    ADC0_PC_R |= 0x01;
    // Set the priority of sample sequencers.
    // Sample sequence 0 has highest and SS3 has lowest priority
    ADC0_SSPRI_R |= 0x3210;
    // Disable sample sequence 3 before configuration
    ADC0_ACTSS_R &= ~(0x08);
    // Enable TS0,IE0 and END0 bits
    ADC0_SSCTL3_R |= 0x6;
    // Enable 16x hardware over sampling
    ADC0_SAC_R |= 0x4;
    ADC0_SSMUX3_R = 0x0;
    // Disable Interrupt by writing 0 to corresponding bit
    ADC0_IM_R &= ~(0x08);
    // Activate sample sequencer
    ADC0_ACTSS_R |= 0x08;
}

// ADC0 interrupt service routine for sequencer 3
void get_moisture_level(void)
{
    // software trigger
    ADC0_PSSI_R |= 0x08; // sample is aken once

    // POLL for the status of corresponding RIS BIT

    while ((ADC0_RIS_R & 0x08) == 0)
        ;
    // After conversion
    ADC_value = (ADC0_SSFIFO3_R & 0xFFF); // 12 bit value
    // clear RIS to start again
    ADC0_ISC_R &= ~(0x08); // although this bit is not set if u dont enable interrupt in
                           // masked interrupt status but writting to this bit clears RIS bit
}

/* This function generates the delay. */
void Delay(volatile unsigned int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
    }
}
