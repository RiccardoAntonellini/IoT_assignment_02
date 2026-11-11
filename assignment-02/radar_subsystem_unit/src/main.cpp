#include <Arduino.h>
#include "kernel/Scheduler.h"
#include "model/Context.h"
// mancano include dei tasks

Scheduler scheduler; // istanza unica
Context ctx;

void setup() {

  Serial.begin(SERIAL_BAUD);

  scheduler.init(BASE_PERIOD);

  //ogni task creato una volta sola e aggiunto in ordine di esecuzione, tutta la logica sta nei task stessi
  scheduler.addTask(new AlarmLedTask(&ctx));
  // e altri vari
}

void loop() {
  scheduler.schedule();
}