#include "binary_counter.h"
#include "drivers/gpio/gpio.h"

/*
 * 6 LEDs, LSB first:
 *   bit0 = D10 (PORTB pin 2)
 *   bit1 = D11 (PORTB pin 3)
 *   bit2 = D12 (PORTB pin 4)
 *   bit3 = D13 (PORTB pin 5)
 *   bit4 = A2  (PORTC pin 2)
 *   bit5 = A3  (PORTC pin 3)
 */

static uint8_t counter_value = 0;

static void display(void) {
    GPIO_Write(GPIO_PORTB, 2, (counter_value >> 0) & 1);
    GPIO_Write(GPIO_PORTB, 3, (counter_value >> 1) & 1);
    GPIO_Write(GPIO_PORTB, 4, (counter_value >> 2) & 1);
    GPIO_Write(GPIO_PORTB, 5, (counter_value >> 3) & 1);
    GPIO_Write(GPIO_PORTC, 2, (counter_value >> 4) & 1);
    GPIO_Write(GPIO_PORTC, 3, (counter_value >> 5) & 1);
}

void BinaryCounter_Init(void) {
    GPIO_Init(GPIO_PORTB, 2, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 3, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 4, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 5, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTC, 2, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTC, 3, GPIO_OUTPUT);

    counter_value = 0;
    display();
}

void BinaryCounter_Increment(void) {
    counter_value = (counter_value + 1) & 0x3F;  /* wrap at 63 */
    display();
}

void BinaryCounter_Reset(void) {
    counter_value = 0;
    display();
}
