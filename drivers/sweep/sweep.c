#include "sweep.h"
#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"

#define SWEEP_COUNT    5
#define DEAD_ZONE      50
#define DELAY_MIN_MS   30
#define DELAY_MAX_MS   200

/* LED pins: D2=PD2, D3=PD3, D4=PD4, D5=PD5, D6=PD6 — all PORTD, index 0 = LSB (D2) */
static uint8_t sweep_pins[SWEEP_COUNT] = {2, 3, 4, 5, 6};

static int8_t  sweep_pos     = 0;
static uint8_t sweep_idle    = 1;
static uint32_t sweep_last_ms = 0;

void Sweep_Init(void) {
    uint8_t i;
    for (i = 0; i < SWEEP_COUNT; i++) {
        GPIO_Init(GPIO_PORTD, sweep_pins[i], GPIO_OUTPUT);
        GPIO_Write(GPIO_PORTD, sweep_pins[i], GPIO_LOW);
    }
}

void Sweep_Update(int16_t deflection) {
    int16_t  abs_d = deflection < 0 ? -deflection : deflection;
    uint32_t delay;
    uint32_t now;

    if (abs_d <= DEAD_ZONE) {
        if (!sweep_idle) {
            uint8_t i;
            for (i = 0; i < SWEEP_COUNT; i++) {
                GPIO_Write(GPIO_PORTD, sweep_pins[i], GPIO_LOW);
            }
            sweep_idle = 1;
        }
        return;
    }

    /* just left dead zone: light up current position immediately */
    if (sweep_idle) {
        GPIO_Write(GPIO_PORTD, sweep_pins[sweep_pos], GPIO_HIGH);
        sweep_idle    = 0;
        sweep_last_ms = Millis();
        return;
    }

    /* speed: more deflection = shorter delay */
    delay = DELAY_MAX_MS - ((uint32_t)(abs_d - DEAD_ZONE) * (DELAY_MAX_MS - DELAY_MIN_MS)) / (512 - DEAD_ZONE);

    now = Millis();
    if (now - sweep_last_ms < delay) {
        return;
    }
    sweep_last_ms = now;

    /* turn off current LED */
    GPIO_Write(GPIO_PORTD, sweep_pins[sweep_pos], GPIO_LOW);

    /* advance position */
    if (deflection > 0) {
        /* LSB -> MSB */
        sweep_pos++;
        if (sweep_pos >= SWEEP_COUNT) sweep_pos = 0;
    } else {
        /* MSB -> LSB */
        sweep_pos--;
        if (sweep_pos < 0) sweep_pos = SWEEP_COUNT - 1;
    }

    /* turn on new LED */
    GPIO_Write(GPIO_PORTD, sweep_pins[sweep_pos], GPIO_HIGH);
}
