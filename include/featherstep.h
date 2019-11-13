#pragma once

#define DIR_PIN           6 // Direction
#define EN_PIN            7 // Enable
#define STEP_PIN          8 // Step
#define CS_PIN           14 // Chip select
#define SW_MOSI          12 // Software Master Out Slave In (MOSI)
#define SW_MISO          11 // Software Master In Slave Out (MISO)
#define SW_SCK           13 // Software Slave Clock (SCK)


// Match to your driver
// SilentStepStick series use 0.11
// UltiMachine Einsy and Archim2 boards use 0.2
// Panucatt BSD2660 uses 0.1
// Watterott TMC5160 uses 0.075
#define R_SENSE 0.11f
