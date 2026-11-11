#pragma once

//Pulsanti
#define START_BUTTON_PIN    2
#define STOP_BUTTON_PIN     12
#define RESET_BUTTON_PIN    13

//Led
#define LED_ON_PIN  9
#define LED_ALARM_PIN  8

#define SERVO_PIN 4
#define MIN_ANGLE 0
#define MAX_ANGLE 180

#define SONAR_ECHO_PIN  3
#define SONAR_TRIG_PIN  11

#define POT_PIN A0

#define TEMP_PIN A1

//Parametri abritrari
#define N_SECTORS 8
#define D1 0.10
#define D2 0.25
#define SCAN_PERIOD_S1 200
#define SCAN_PERIOD_S2 100

//Display
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define SERIAL_BAUD 9600

//per scheduler
#define BASE_PERIOD 50