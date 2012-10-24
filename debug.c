#include "stm32f10x.h"

#define MODE_ON 	0	/* Offset to add to pin for ON */
#define MODE_OFF	16	/* Offset to add to pin for OFF */

void debug_init(void) {
	// Turn on clock for IO Port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
        // Turn on clock for IO Port E
        RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
        
        // Alternate function IO clock enable
        RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
        
        // Turn on clock for USART1
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
                      
        // Put PA9 in output mode 
        // 10|11 ( Alternate function output Push-pull | Output mode, max speed 50 MHz )
        GPIOA->CRH &= ~GPIO_CRH_MODE9;
        GPIOA->CRH |=  GPIO_CRH_MODE9_0;
        GPIOA->CRH |=  GPIO_CRH_MODE9_1;
        GPIOA->CRH &= ~GPIO_CRH_CNF9;
        GPIOA->CRH |= GPIO_CRH_CNF9_1;
        
        // Put PA10 in input mode 
        // 01|00 ( Floating input (reset state) | Input mode (reset state) )
        GPIOA->CRH &= ~GPIO_CRH_MODE10;
   	GPIOA->CRH &= ~GPIO_CRH_CNF10;
   	GPIOA->CRH |= GPIO_CRH_CNF10_0;
        
    	// Put PE{4,5,6,7} in output mode
    	// 00|01 ( General purpose output push-pull | Output mode, max speed 10 MHz )
    	// GPIOE->CRL reset value = 0x44444444
    	GPIOE->CRL &= ~GPIO_CRL_MODE3;
    	GPIOE->CRL |=  GPIO_CRL_MODE3_0;
        GPIOE->CRL &= ~GPIO_CRL_CNF3;
        
        GPIOE->CRL &= ~GPIO_CRL_MODE4;
    	GPIOE->CRL |=  GPIO_CRL_MODE4_0;
        GPIOE->CRL &= ~GPIO_CRL_CNF4;
        
        GPIOE->CRL &= ~GPIO_CRL_MODE5;
    	GPIOE->CRL |=  GPIO_CRL_MODE5_0;
        GPIOE->CRL &= ~GPIO_CRL_CNF5;
        
        GPIOE->CRL &= ~GPIO_CRL_MODE6;
    	GPIOE->CRL |=  GPIO_CRL_MODE6_0;
        GPIOE->CRL &= ~GPIO_CRL_CNF6;
      
        // Configure BRR by deviding the bus clock with the baud rate
        USART1->BRR = 8000000/57600;
	USART1->CR1 |= ( USART_CR1_UE | USART_CR1_RE | USART_CR1_TE);
}

/**
 * Delay for "cnt" NOPs.
 *
 * @param[in]	cnt	number of NOPs to delay
 */
void delay(int cnt) {
    	while (cnt-- > 0) {
        	asm("nop");
    	}
}

/**
 * Turn a single LED on PORTC on/off.
 *
 * @param[in]	led pin (0-15)  to turn on/off
 * @param[in] mode of led (LED_ON | LED_OFF)
 */
void set_led(int led, int mode) {
    	GPIOE->BSRR = 1<<(led + mode);
}

/**
 * Set a led on.
 *
 * @param[in]	led pin (0-15)  to flash
 */
void led_on(int led) {
    	set_led(led, MODE_ON);
}

/**
 * Set a led off.
 *
 * @param[in]	led pin (0-15)  to flash
 */
void led_off(int led) {
    	set_led(led, MODE_OFF);
}

/**
 * Flash a led oo-off.
 *
 * @param[in]	led pin (0-15)  to flash
 */
void flash_led(int led) {
    	set_led(led, MODE_ON);
    	delay(300000);
    	set_led(led, MODE_OFF);
}

/**
 * Receive a single byte from USART1. This call blocks
 * until the USART signals that a byte was received.
 *
 * @return 	the byte received
 */
int usart_rec(void) {
    /* Wait until the data is ready to be received. */
    while ((USART1->SR & USART_SR_RXNE) == 0);

    // read RX data, combine with DR mask (we only accept a max of 9 Bits)
    return USART1->DR & 0x1FF;
}

/**
 * Send a single byte to USART1. This call blocks
 * until the USART has send the byte.
 *
 * @param[in]		data byte to send
 */
void usart_snd(int data) {
    	USART1->DR = data;

    	// wait for TX
    	while ((USART1->SR & USART_SR_TXE) == 0);
}

/**
 * Send string to USART1
 *
 * @param[in]		str to send
 */
void usart_snd_str(char *str) {
    	int   i = 0;

    	while(str[i] != 0) {
        	usart_snd(str[i++]);
    	}
}

