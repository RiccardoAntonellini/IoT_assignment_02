#pragma once

// Pulsanti
#define START_BUTTON_PIN    2
#define STOP_BUTTON_PIN     12
#define RESET_BUTTON_PIN    13

#define BUTTON_DEBOUNCE_MS 20

// Led
#define LED_ON_PIN  9
#define LED_ALARM_PIN  8

// Servo
#define SERVO_PIN 4
#define MIN_ANGLE 0
#define MAX_ANGLE 180

// Sonar
#define SONAR_ECHO_PIN  3
#define SONAR_TRIG_PIN  11

#define SONAR_MAX_DISTANCE 0.40 // portata massima in metri

// Potentiometer
#define POT_PIN A0

// Temperature sensor
#define TEMP_PIN A1

#define TENSIONE_RIFERIMENTO_TS 5.0
#define LIVELLI_CONVERTITORE_TS 1024.0
#define TENSIONE_USCITA_0C_TS 0.5
#define TENSIONE_PER_GRADOC_TS 0.01
#define CAMPIONI_PER_MEDIA_RUMORE_TS 8

// Parametri abritrari
#define N_SECTORS 8
#define D1 0.10
#define D2 0.25
#define SCAN_PERIOD_S1 200
#define SCAN_PERIOD_S2 100

// Display
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define SERIAL_BAUD 9600

// Scheduler
#define BASE_PERIOD 50

#define BLINK_TIME 250