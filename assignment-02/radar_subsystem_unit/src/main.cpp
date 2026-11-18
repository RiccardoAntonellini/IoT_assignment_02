#include <Arduino.h>
#include <avr/sleep.h>
#include "kernel/Scheduler.h"
#include "model/Context.h"
#include "tasks/ButtonTask.h"
#include "tasks/CommTask.h"
#include "tasks/LedTask.h"
#include "tasks/ScanTask.h"
#include "tasks/SystemTask.h"
#include "tasks/TempTask.h"
#include "tasks/DisplayTask.h"

Scheduler scheduler;
Context ctx;

int idleTimeMs = 0;

// stacca subito l'interrupt altrimenti con il pin low si rilancerebbe di continuo e bloccherebbe tutto
void wakeUpHandler() {
  detachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN));
}

void goToSleep() {
  Serial.flush();// svuota buffer seriale
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);// cpu + timer fermi
  noInterrupts();// evita che il pulsante venga premuto tra prep e sleep
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN), wakeUpHandler, LOW);// pin 2 low allora si sveglia
  interrupts();
  sleep_cpu();// mcu si ferma qui finché non si preme start

  sleep_disable();
  scheduler.resync();// sincronizza nuovamente il timer millis così che il ritmo dei tick rimanga regolare
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  scheduler.init(BASE_PERIOD);

  Led *greenLed = new Led(LED_ON_PIN);
  greenLed->init();
  scheduler.addTask(new SystemTask(&ctx, greenLed));

  Led *redLed = new Led(LED_ALARM_PIN);
  redLed->init();
  scheduler.addTask(new LedTask(&ctx, redLed));

  Button *startButton = new Button(START_BUTTON_PIN);
  Button *stopButton = new Button(STOP_BUTTON_PIN);
  Button *resetButton = new Button(RESET_BUTTON_PIN);
  startButton->init();
  stopButton->init();
  resetButton->init();
  scheduler.addTask(new ButtonTask(&ctx, startButton, stopButton, resetButton));

  Potentiometer *pot = new Potentiometer(POT_PIN);
  RadarServo *servo = new RadarServo(SERVO_PIN);
  Sonar *sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  pot->init();
  servo->init();
  sonar->init();
  scheduler.addTask(new ScanTask(sonar, &ctx, pot, servo));

  TempSensor *tempSensor = new TempSensor(TEMP_PIN);
  tempSensor->init();
  scheduler.addTask(new TempTask(&ctx, tempSensor));

  Display *display = new Display();
  display->init();
  scheduler.addTask(new DisplayTask(&ctx, display));

  scheduler.addTask(new CommTask(&ctx));
}

void loop() {
  scheduler.schedule();

  if (ctx.state == IDLE) {
    idleTimeMs += BASE_PERIOD;
    if (idleTimeMs >= SLEEP_DELAY_MS) {
      goToSleep();
      idleTimeMs = 0;
    }
  } else {
    idleTimeMs = 0;
  }
}