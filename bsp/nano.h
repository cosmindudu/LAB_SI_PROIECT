#ifndef NANO_H
#define NANO_H

#include "drivers/gpio/gpio.h"

// Arduino Nano Pin Mappings
// Professional driver implementation: definitions for silk screen labels

// Digital Pins
#define D0  GPIO_PORTD, 0  // RX
#define D1  GPIO_PORTD, 1  // TX
#define D2  GPIO_PORTD, 2
#define D3  GPIO_PORTD, 3
#define D4  GPIO_PORTD, 4
#define D5  GPIO_PORTD, 5
#define D6  GPIO_PORTD, 6
#define D7  GPIO_PORTD, 7

#define D8  GPIO_PORTB, 0
#define D9  GPIO_PORTB, 1
#define D10 GPIO_PORTB, 2
#define D11 GPIO_PORTB, 3
#define D12 GPIO_PORTB, 4
#define D13 GPIO_PORTB, 5  // Onboard LED

// Analog Pins (usable as Digital GPIO)
#define A0  GPIO_PORTC, 0
#define A1  GPIO_PORTC, 1
#define A2  GPIO_PORTC, 2
#define A3  GPIO_PORTC, 3
#define A4  GPIO_PORTC, 4
#define A5  GPIO_PORTC, 5

// Note: A6 and A7 on Nano are Analog Input ONLY. 
// They are not supported by the digital GPIO driver.

// Aliases
#define LED_BUILTIN D13
#define RX          D0
#define TX          D1

// --- Project-specific pin assignments ---

// POT1 → PWM LED intensity (ADC channel numbers, not GPIO descriptors)
#define POT1_ADC_CH   0  /* A0 */
#define POT2_ADC_CH   1  /* A1 */

// PWM LED (D9 / PB1 / OC1A)
#define PWM_LED       D9

// Sweep LEDs: D2–D6 (PD2–PD6), index 0 = leftmost
#define SWEEP_LED_0   D2
#define SWEEP_LED_1   D3
#define SWEEP_LED_2   D4
#define SWEEP_LED_3   D5
#define SWEEP_LED_4   D6

// Binary counter LEDs: D10–D13 (bits 0–3), A2–A3 (bits 4–5), LSB first
#define BIN_LED_0     D10
#define BIN_LED_1     D11
#define BIN_LED_2     D12
#define BIN_LED_3     D13
#define BIN_LED_4     A2
#define BIN_LED_5     A3

// Buttons (D7, D8 — pulled up internally, active LOW)
#define BTN_INCREMENT D7
#define BTN_RESET     D8

#endif // NANO_H
