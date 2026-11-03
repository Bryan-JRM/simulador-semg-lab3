#include "semg.h"

unsigned int i = 0;
unsigned long tiempoAnterior = 0;

const unsigned long periodo = 488;

void setup() {
}

void loop() {

  unsigned long ahora = micros();

  if (ahora - tiempoAnterior >= periodo) {

    tiempoAnterior += periodo;

    dacWrite(25, SEMG[i]);

    i++;

    if (i >= N_SEMG) {
      i = 0;
    }
  }
}
