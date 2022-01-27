#include <avr/eeprom.h>
#include "tiny5351.h"

uint32_t SI_XTAL_FREQ = 27018750UL; // Measured crystal frequency of XTAL2 for CL = 10pF
//uint32_t frequency = 0;
//uint8_t ch = 0;
uint8_t prv_ch = 254;


void setup() {
  DDRB &= ~(1 << PB3);      // For attiny it is PB3 for adc input
  ADMUX |= (0 << REFS0) | (1 << MUX1) | (1 << MUX0); // set reference and channel
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN); //set prescaller to 128 and enable ADC
  sei();
}

void loop() {
uint8_t  ch = ReadADC() >> 6;
  if (prv_ch != ch) {
    si5351_freq(eeprom_read_dword((uint32_t*)(ch << 2)) , 0);
    prv_ch = ch;
  }
}

uint16_t ReadADC() {
  ADCSRA |= (1 << ADSC);       // start conversion
  while (ADCSRA & (1 << ADSC)) {} // wait for conversion complete
  return ADC;
}
