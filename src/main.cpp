#include <Arduino.h>
#include <SimpleModbusSlave.h>
#include "EXTIO_Lib.h"

#define FW_Ver "V1.1.0"

// Modbus parameters
#define Baudrate 38400
#define Format SERIAL_8E1
#define SlaveID 4
#define TxEnablePin 2

#define HOLDING_REGS_SIZE 6
unsigned int holdingRegs[HOLDING_REGS_SIZE] = {0};

const int common_Z = A3; //global variables

// EXTIO_Lib instance for input/output control
InOut input_mux(7, 8, 9, 10, common_Z); // Set the S0, S1, S2 and S3 pins


// Modbus register mappings for voting
#define CANDIDATE_1 0
#define CANDIDATE_2 1
#define CANDIDATE_3 2
#define CANDIDATE_4 3
#define TOTAL_VOTES 4
#define VOTING_STATUS 5


void setup() {
  // Initialize Modbus
  modbus_configure(&Serial, Baudrate, Format, SlaveID, TxEnablePin, HOLDING_REGS_SIZE, holdingRegs);
  modbus_update_comms(Baudrate, Format, SlaveID);

  pinMode(common_Z, INPUT);

  // Serial for debugging
  Serial.begin(115200);
  Serial.println("EXT IO Card Voting Machine Initialized");
}

void loop() {
  // Update Modbus communication
  modbus_update();

  // Check voting inputs and update Modbus registers
  if (ioModule.DI_Read(0)) { // DI1 -> Candidate 1
    holdingRegs[CANDIDATE_1]++;
    holdingRegs[TOTAL_VOTES]++;
    Serial.println("Vote registered for Candidate 1");
    delay(200); // Debounce delay
  }

  if (ioModule.DI_Read(1)) { // DI2 -> Candidate 2
    holdingRegs[CANDIDATE_2]++;
    holdingRegs[TOTAL_VOTES]++;
    Serial.println("Vote registered for Candidate 2");
    delay(200);
  }

  if (ioModule.DI_Read(2)) { // DI3 -> Candidate 3
    holdingRegs[CANDIDATE_3]++;
    holdingRegs[TOTAL_VOTES]++;
    Serial.println("Vote registered for Candidate 3");
    delay(200);
  }

  if (ioModule.DI_Read(3)) { // DI4 -> Candidate 4
    holdingRegs[CANDIDATE_4]++;
    holdingRegs[TOTAL_VOTES]++;
    Serial.println("Vote registered for Candidate 4");
    delay(200);
  }

  // End voting status triggered by a specific DI (e.g., DI8)
  if (ioModule.DI_Read(7)) { // DI8 -> End Voting
    Serial.println("\n--- Voting Results ---");
    Serial.print("Candidate 1 Votes: ");
    Serial.println(holdingRegs[CANDIDATE_1]);
    Serial.print("Candidate 2 Votes: ");
    Serial.println(holdingRegs[CANDIDATE_2]);
    Serial.print("Candidate 3 Votes: ");
    Serial.println(holdingRegs[CANDIDATE_3]);
    Serial.print("Candidate 4 Votes: ");
    Serial.println(holdingRegs[CANDIDATE_4]);
    Serial.print("Total Votes: ");
    Serial.println(holdingRegs[TOTAL_VOTES]);

    holdingRegs[VOTING_STATUS] = 1; // Voting complete status
    delay(5000); // Pause before resetting
  }
}
