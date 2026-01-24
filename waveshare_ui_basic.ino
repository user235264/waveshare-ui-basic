#include <Arduino.h>
#include "LVGL_Driver.h"

// Add the SquareLine screens (everything in /screen folder)
extern "C" {
  #include "screen/ui.h"
}

// Optional: Setup other C/CPP linkage as needed for helpers/events

void setup() {
  Serial.begin(115200);
  LCD_Init();
  Backlight_Init();
  Set_Backlight(80);
  Lvgl_Init();

  // Now initialize all the screens/UI widgets from the SquareLine export.
  ui_init();
}

void loop() {
  Lvgl_Loop();
  delay(5);
}
