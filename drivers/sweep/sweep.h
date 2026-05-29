#ifndef SWEEP_H
#define SWEEP_H

#include <stdint.h>

void Sweep_Init(void);
void Sweep_Update(int16_t deflection);  /* deflection = ADC_Read(POT2) - 512 */

#endif /* SWEEP_H */
