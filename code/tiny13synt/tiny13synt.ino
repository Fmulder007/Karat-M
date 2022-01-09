#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "tiny5351.h"


#define REF_AVCC (0<<REFS0) // reference = AVCC
uint32_t frequency = 12345678UL;
uint16_t t;
uint16_t prv_t = 0;


void setup() {
  DDRB &= ~(1 << PB3); // For attiny it is PB3 for adc input
  InitADC();
  sei();
  //si5351_freq(eeprom_read_dword(), 0);
  //eeprom_update_dword(0, frequency);
}

void loop() {
  /*
    t = ReadADC(3) >> 6;
    if (prv_t != t) {
      si5351_freq(frequency + t, 0);
      prv_t = t;
    }*/
  t = map(ReadADC(3), 0, 1023, 0, 10);
  if (prv_t != t) {
    frequency = eeprom_read_dword(uint32_t(t));
    si5351_freq(frequency, 0);
    prv_t = t;
  }
}

uint16_t ReadADC(uint8_t ADCchannel) {
  ADMUX = REF_AVCC | ADCchannel;  // set reference and channel
  delay(100);
  ADMUX |= _BV(ADLAR); // left adjust of ADC result
  ADCSRA |= (1 << ADSC);       // start conversion
  while (ADCSRA & (1 << ADSC)) {} // wait for conversion complete
  return ADC;
}

void InitADC() {
  ADMUX |= (1 << REFS0);
  //set prescaller to 128 and enable ADC
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}
