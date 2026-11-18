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

Scheduler scheduler; // istanza unica
Context ctx;

int idleTimeMs = 0;   // da quanto tempo il sistema è in IDLE

// ISR di risveglio: si stacca subito, altrimenti con il pin LOW si rilancerebbe di continuo
void wakeUpHandler() {
  detachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN));
}

void goToSleep() {
  Serial.flush();                                  // svuota il buffer seriale (altrimenti STATE:IDLE resta tagliato)

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);             // modalità di sonno più profonda
  noInterrupts();                                  // niente interrupt tra attach e sleep, per non perdere il risveglio
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN), wakeUpHandler, LOW);  // in power-down vale solo il livello LOW
  interrupts();
  sleep_cpu();                                     // l'MCU si ferma qui finché START non va a LOW

  // ---- risveglio: si riparte da qui ----
  sleep_disable();
  scheduler.resync();                              // millis() era fermo: riallineo lo scheduler
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
  startButton->init();                    // pinMode INPUT_PULLUP + stato iniziale reale
  stopButton->init();
  resetButton->init();
  scheduler.addTask(new ButtonTask(&ctx, startButton, stopButton, resetButton));

  Potentiometer *pot = new Potentiometer(POT_PIN);
  RadarServo *servo = new RadarServo(SERVO_PIN);
  Sonar *sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
  pot->init();
  servo->init();                          // prepara lo stato, non attacca ancora il servo
  sonar->init();                          // pinMode di TRIG ed ECHO
  scheduler.addTask(new ScanTask(sonar, &ctx, pot, servo));

  TempSensor *tempSensor = new TempSensor(TEMP_PIN);
  tempSensor->init();
  scheduler.addTask(new TempTask(&ctx, tempSensor));

  Display *display = new Display();
  display->init();                        // avvia I2C e accende la retroilluminazione
  scheduler.addTask(new DisplayTask(&ctx, display));

  scheduler.addTask(new CommTask(&ctx));
}

void loop() {
  scheduler.schedule();                            // un tick: tutti i task fanno un passo

  if (ctx.state == IDLE) {
    idleTimeMs += BASE_PERIOD;                     // conto il tempo passato in IDLE
    if (idleTimeMs >= SLEEP_DELAY_MS) {
      goToSleep();
      idleTimeMs = 0;                              // al risveglio riparto da zero
    }
  } else {
    idleTimeMs = 0;                                // fuori da IDLE non si dorme
  }
}