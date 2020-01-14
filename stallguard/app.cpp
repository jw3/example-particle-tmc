/**
 * Author Teemu Mäntykallio
 *
 * Plot TMC2130 or TMC2660 motor load using the stallGuard value.
 * You can finetune the reading by changing the STALL_VALUE.
 * This will let you control at which load the value will read 0
 * and the stall flag will be triggered. This will also set pin DIAG1 high.
 * A higher STALL_VALUE will make the reading less sensitive and
 * a lower STALL_VALUE will make it more sensitive.
 *
 * You can control the rotation speed with
 * 0 Stop
 * 1 Resume
 * + Speed up
 * - Slow down
 */
#include <Particle.h>
#include <TMCStepper.h>
#include <featherstep.h>

#define DIAG0_PIN 99

#define MAX_SPEED        40 // In timer value
#define MIN_SPEED      1000

#define STALL_VALUE      15 // [-64..63]

TMC5160Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

using namespace TMC2130_n;

void stallguardStop() {
   digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
}

void setup() {
   SPI.begin();

   pinMode(EN_PIN, OUTPUT);
   pinMode(STEP_PIN, OUTPUT);
   pinMode(CS_PIN, OUTPUT);
   pinMode(DIR_PIN, OUTPUT);
   pinMode(MISO, INPUT_PULLUP);
   digitalWrite(EN_PIN, LOW);

   driver.begin();
   driver.toff(4);
   driver.blank_time(24);
   driver.rms_current(400); // mA
   driver.microsteps(16);
   driver.TCOOLTHRS(0xFFFFF); // 20bit max
   driver.THIGH(0);
   driver.semin(5);
   driver.semax(2);
   driver.sedn(0b01);
   driver.sgt(STALL_VALUE);

   attachInterrupt(DIAG0_PIN, stallguardStop, FALLING);
}

void loop() {
   static uint32_t last_time=0;
   uint32_t ms = millis();

   if((ms-last_time) > 100) { //run every 0.1s
      last_time = ms;

      DRV_STATUS_t drv_status{0};
      drv_status.sr = driver.DRV_STATUS();

      Serial.print("0 ");
      Serial.print(drv_status.sg_result, DEC);
      Serial.print(" ");
      Serial.println(driver.cs2rms(drv_status.cs_actual), DEC);
   }
}
