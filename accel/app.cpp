/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper motor.
 */

#include <TMCStepper.h>
#include <featherstep.h>

SYSTEM_MODE(MANUAL)

#define R_SENSE 0.11 // Match to your driver
// SilentStepStick series use 0.11
// UltiMachine Einsy and Archim2 boards use 0.2
// Panucatt BSD2660 uses 0.1
// Watterott TMC5160 uses 0.075

TMC5160Stepper driver = TMC5160Stepper(CS_PIN, R_SENSE);

constexpr uint32_t steps_per_mm = 80;

#include <AccelStepper.h>
AccelStepper stepper = AccelStepper(1, STEP_PIN, DIR_PIN);

void setup() {
   SPI.begin();
   pinMode(CS_PIN, OUTPUT);
   digitalWrite(CS_PIN, HIGH);
   driver.begin();             // Initiate pins and registeries
   driver.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
   driver.en_pwm_mode(1);      // Enable extremely quiet stepping
   driver.pwm_autoscale(1);
   driver.microsteps(16);

   stepper.setMaxSpeed(50 * steps_per_mm); // 100mm/s @ 80 steps/mm
   stepper.setAcceleration(1000 * steps_per_mm); // 2000mm/s^2
   stepper.setEnablePin(EN_PIN);
   stepper.setPinsInverted(false, false, true);
   stepper.enableOutputs();
}

void loop() {
   if(stepper.distanceToGo() == 0) {
      stepper.disableOutputs();
      delay(100);
      stepper.move(100 * steps_per_mm); // Move 100mm
      stepper.enableOutputs();
   }
   stepper.run();
}
