#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"
#include "drivers/adc/adc.h"
#include "drivers/pwm/pwm.h"
#include "drivers/button/button.h"
#include "drivers/sweep/sweep.h"
#include "drivers/binary_counter/binary_counter.h"

int main(void) {
    /* System tick (1ms) + global interrupts */
    Timer0_Init();

    /* ADC for potentiometers */
    ADC_Init();

    /* PWM LED on D9 (PORTB pin 1) */
    GPIO_Init(GPIO_PORTB, 1, GPIO_OUTPUT);
    PWM_Init(GPIO_PORTB, 1, 1000);

    /* Sweep LEDs: D2-D6 initialized inside Sweep_Init */
    Sweep_Init();

    /* Binary counter LEDs: D10-D13, A2, A3 initialized inside BinaryCounter_Init */
    BinaryCounter_Init();

    /* Buttons: D7, D8 initialized inside Buttons_Init */
    Buttons_Init();

    while (1) {
        /* POT1 on A0 (channel 0) -> PWM brightness */
        uint16_t pot1 = ADC_Read(0);
        PWM_SetDutyCycle(GPIO_PORTB, 1, (uint8_t)(pot1 >> 2));

        /* POT2 on A1 (channel 1) -> sweep direction and speed */
        int16_t deflection = (int16_t)ADC_Read(1) - 512;
        Sweep_Update(deflection);

        /* Buttons -> binary counter */
        if (Button_WasPressed(BTN_INC)) {
            BinaryCounter_Increment();
        }
        if (Button_WasPressed(BTN_RST)) {
            BinaryCounter_Reset();
        }
    }
}
