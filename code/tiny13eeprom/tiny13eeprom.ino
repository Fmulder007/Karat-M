#include <avr/eeprom.h>

uint32_t freq[] = {
  2410000,
  3410000,
  2415000,
  3415000,
  2420000,
  3420000,
  2425000,
  3425000,
  2430000,
  3430000
};
void setup() {
  eeprom_update_block((void*)&freq, 0, sizeof(freq));
}

void loop() {
}
