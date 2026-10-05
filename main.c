#define RCC_AHBENR   (*(volatile unsigned int *)0x40021014)
#define RCC_APB2ENR  (*(volatile unsigned int *)0x40021018)

#define GPIOE_MODER  (*(volatile unsigned int *)0x48001000)
#define GPIOE_AFRH   (*(volatile unsigned int *)0x48001024)

#define TIM1_CR1     (*(volatile unsigned int *)0x40012C00)
#define TIM1_EGR     (*(volatile unsigned int *)0x40012C14)
#define TIM1_CCMR1   (*(volatile unsigned int *)0x40012C18)
#define TIM1_CCER    (*(volatile unsigned int *)0x40012C20)
#define TIM1_PSC     (*(volatile unsigned int *)0x40012C28)
#define TIM1_ARR     (*(volatile unsigned int *)0x40012C2C)
#define TIM1_CCR1    (*(volatile unsigned int *)0x40012C34)
#define TIM1_BDTR    (*(volatile unsigned int *)0x40012C44)

int i = 0;

void delay(void)
{
    volatile unsigned int j;

    for (j = 0; j < 100000; j++)
    {
    }
}

int main(void)
{
    int direction = 1;

    RCC_AHBENR |= (1U << 21);
    RCC_APB2ENR |= (1U << 11);

    GPIOE_MODER &= ~(3U << 18);
    GPIOE_MODER |= (2U << 18);

    GPIOE_AFRH &= ~(0xFU << 4);
    GPIOE_AFRH |= (2U << 4);

    TIM1_PSC = 7;
    TIM1_ARR = 999;
    TIM1_CCR1 = 0;

    TIM1_CCMR1 &= ~(7U << 4);
    TIM1_CCMR1 |= (6U << 4);
    TIM1_CCMR1 |= (1U << 3);

    TIM1_CCER |= (1U << 0);

    TIM1_BDTR |= (1U << 15);

    TIM1_CR1 |= (1U << 7);

    TIM1_EGR = 1U;

    TIM1_CR1 |= 1U;

    while (1)
    {
        TIM1_CCR1 = i * 10;

        i += direction;

        if (i >= 99)
        {
            i = 99;
            direction = -15;
        }

        if (i <= 0)
        {
            i = 0;
            direction = 15;
        }

        delay();
    }
}
