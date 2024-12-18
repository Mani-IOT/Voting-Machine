/**
 * @file main.cpp
 * @brief Main program file for the Arduino-based Voting Machine.
 * 
 * This program initializes the VotingMachine class and continuously monitors votes in the loop.
 * It uses the custom VotingMachine library to handle voting functionality and display results.
 * 
 * @author K Mani Balan
 * @date 16/12/2024
 */

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "VotingMachine.h" ///< Include the custom VotingMachine library

VotingMachine votingMachine; ///< Create an object of VotingMachine

/**
 * @brief Arduino setup function.
 * 
 * Initializes the Serial interface for debugging and calls the VotingMachine's initialization routine.
 */
void setup() {
    Serial.begin(115200); ///< Begin Serial communication at 115200 baud rate
    votingMachine.begin(); ///< Initialize the Voting Machine
}

/**
 * @brief Arduino main loop function.
 * 
 * Continuously monitors GPIO inputs to check for votes or end voting signal.
 */
void loop() {
    votingMachine.checkVotes(); ///< Monitor votes and manage the voting process
}
