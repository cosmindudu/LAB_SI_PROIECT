#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#define BTN_INC 0
#define BTN_RST 1

void    Buttons_Init(void);
uint8_t Button_WasPressed(uint8_t btn_id);

#endif /* BUTTON_H */
