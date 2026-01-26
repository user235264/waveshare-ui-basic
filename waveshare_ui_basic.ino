#include <Arduino.h>
#include "LVGL_Driver.h"

// Touch controller depends on I2C and possibly TCA9554PWR
#include "Touch_CST816.h"
#include "I2C_Driver.h"
#include "TCA9554PWR.h"

// Display driver (already transitively included by LVGL_Driver.h, but explicit is okay)
#include "Display_ST77916.h"

// If your project uses battery, RTC, or SD (optional):
// #include "BAT_Driver.h"
// #include "RTC_PCF85063.h"
// #include "SD_Card.h"

// Include UI header (ensure all SquareLine Studio .c files are added to sketch)
extern "C" {
  #include "ui.h"
}

void setup() {
  Serial.begin(115200);

  // -- Initialize I2C bus --
  I2C_Init();

  // -- Initialize TCA9554 power switch chip --
  // (call only if used in your schematics)
  TCA9554PWR_Init(0x00); // Or as required

  // -- Initialize LCD display and backlight --
  LCD_Init();
  Backlight_Init();
  Set_Backlight(80);

  // -- Initialize Touch Controller (CST816) --
  Touch_Init();

  // -- Optional: battery, RTC, SD, etc. --
  // BAT_Init();
  // PCF85063_Init();
  // SD_Init();

  // -- Initialize LVGL Display buffer, register display+touch with LVGL --
  Lvgl_Init();

  // -- SquareLine Studio UI --
  ui_init();
}

void loop() {
  Lvgl_Loop();
  delay(5);
}