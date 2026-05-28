#include "button.h"
#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"

#define DEBOUNCE_MS 50

/* BTN_INC = D7 (PORTD pin 7), BTN_RST = D8 (PORTB pin 0) */
static uint8_t  last_state[2]  = {1, 1};
static uint32_t last_change[2] = {0, 0};

void Buttons_Init(void) {
    /* D7 - increment button */
    GPIO_Init(GPIO_PORTD, 7, GPIO_INPUT);
    GPIO_Write(GPIO_PORTD, 7, GPIO_HIGH);   /* enable pull-up */

    /* D8 - reset button */
    GPIO_Init(GPIO_PORTB, 0, GPIO_INPUT);
    GPIO_Write(GPIO_PORTB, 0, GPIO_HIGH);   /* enable pull-up */
}

uint8_t Button_WasPressed(uint8_t btn_id) {
    uint8_t current;

    if (btn_id == BTN_INC) {
        current = GPIO_Read(GPIO_PORTD, 7);
    } else {
        current = GPIO_Read(GPIO_PORTB, 0);
    }

    uint32_t now = Millis();

    if (current != last_state[btn_id] && (now - last_change[btn_id]) >= DEBOUNCE_MS) {
        last_state[btn_id]  = current;
        last_change[btn_id] = now;

        if (current == 0) {
            return 1;   /* falling edge = pressed (pull-up logic) */
        }
    }

    return 0;
}
