#include <Arduino.h>
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

void setup() {
  Serial.begin(SERIAL_BAUD);
  scheduler.init(BASE_PERIOD);

  Led *greenLed = new Led(LED_ON_PIN);
  greenLed->init();                       // pinMode OUTPUT + LED spento
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
  scheduler.schedule();
}