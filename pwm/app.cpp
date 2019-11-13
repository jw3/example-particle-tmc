/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper
 * motor in alternating directions.
 *
 * https://github.com/teemuatlut/TMCStepper/blob/master/examples/Simple/Simple.ino
 *
 */

#include <Particle.h>
#include <TMCStepper.h>
#include <featherstep.h>

SYSTEM_MODE(MANUAL)

TMC5160Stepper driver(CS_PIN, R_SENSE);

void setup() {
   RGB.control(true);
   RGB.color(255,128,0);

   pinMode(EN_PIN, OUTPUT);
   pinMode(STEP_PIN, OUTPUT);
   pinMode(DIR_PIN, OUTPUT);
   digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

   // Enable one according to your setup
   SPI.begin();                    // SPI drivers
   driver.begin();                 // SPI: Init CS pins and possible SW SPI pins

   driver.toff(5);                 // Enables driver in software
   driver.rms_current(200);        // Set motor RMS current
   driver.microsteps(0);          // Set microsteps to 1/16th

//driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
//   driver.pwm_autoscale(true);     // Needed for stealthChop
}

bool shaft = false;

void loop() {
   tone(STEP_PIN, 20000, 5000);
   delay(1000);
   noTone(STEP_PIN);
   shaft = !shaft;
   driver.shaft(shaft);
}
