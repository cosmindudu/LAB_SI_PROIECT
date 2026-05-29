# Sistem Integrat de Control cu ATmega328P

Proiect realizat pe microcontrollerul ATmega328P (16 MHz), scris de la zero in C pur, fara librarii de Arduino. Aplicatia ruleaza pe o structura de super-loop si gestioneaza in timp real trei functionalitati independente.

---

## Ce face proiectul

1. **Reglare intensitate LED (PWM):** Sistemul citeste valoarea analogica de la potentiometrul POT1 (A0) prin ADC si o scaleaza pe 8 biti (0-255). Valoarea este trimisa direct in registrul de match de la Timer1 pentru a modifica luminozitatea unui LED pe pinul D9 (Fast PWM la 1 kHz).
2. **Semnalizare dinamica auto (Sweep):** Citeste potentiometrul POT2 (A1) pentru a calcula deviatia fata de centru (512). Daca potentiometrul e miscat stanga/dreapta, un grup de 5 LED-uri (D2-D6) se aprinde secvential in directia respectiva. Viteza efectului este dinamica (intre 30 si 200 ms) in functie de cat de mult invarti potentiometrul, existand si o zona moarta la mijloc pentru oprire.
3. **Numarator binar pe 6 biti:** Foloseste doua butoane (D7 pentru incrementare si D8 pentru reset) conectate cu pull-up intern (active-LOW). Pentru a scapa de zgomotul de contact, am implementat un debouncing software de 50 ms folosind functia non-blocking Millis(). Rezultatul (0-63) este afisat in binar pe 6 LED-uri (D10-D13, A2, A3).

---

## Configurare Pini

* **A0 (ADC0):** Potentiometru 1 (Intensitate LED)
* **A1 (ADC1):** Potentiometru 2 (Directie/Viteza Semnalizare)
* **D9 (OC1A):** LED PWM (Iesire Timer1)
* **D2–D6:** LED-uri Semnalizare Dinamica (PORTD)
* **D10–D13 & A2–A3:** LED-uri Numarator Binar (Afisare 0-63)
* **D7:** Buton Incrementare / **D8:** Buton Reset

---

## Structura Proiectului


├── bsp/            # Configurari hardware si mapare pini (nano.h)
├── drivers/        # Drivere periferice (adc, pwm, button, sweep, binary_counter, timer0, gpio)
├── src/            # Codul principal al aplicatiei (main.c)
├── test/           # Teste unitare pentru rulare pe PC cu regiștri mock-uiti
└── Makefile        # Script de compilare si incarcare pe placa

---

## Compilare si Rulare

```bash
# Compilare proiect pentru Arduino Nano
make

# Incarcare cod pe placa prin USB
make flash

# Stergere fisiere temporare de build
make clean

# Rulare teste unitare pe PC
make test

Contribuitori: Dudu Cosmnin-Mihaita --- Iordache Cosmin Stefan.
