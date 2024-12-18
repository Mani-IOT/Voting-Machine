/**
 * @file VotingMachine.cpp
 * @brief Implementation of the VotingMachine class for a basic voting system using Arduino.
 * 
 * This class provides an interface to initialize the voting system, monitor GPIO inputs for 
 * voting actions, and display results.
 * 
 * @author K Mani Balan
 * @date 16/12/2024
 */

#include "VotingMachine.h"
#ifdef ARDUINO
#include <Arduino.h>
#endif

// GPIO pins for voting inputs
const int pinDI1 = 33; ///< GPIO pin for Candidate 1 voting
const int pinDI2 = 25; ///< GPIO pin for Candidate 2 voting
const int pinDI3 = 26; ///< GPIO pin for Candidate 3 voting
const int pinDI4 = 27; ///< GPIO pin for Candidate 4 voting
const int pinDI8 = 14; ///< GPIO pin for ending voting

/**
 * @class VotingMachine
 * @brief Class for managing voting functionality.
 */

/**
 * @brief Constructor for VotingMachine.
 */
VotingMachine::VotingMachine() {
    // Constructor implementation (optional)
}

/**
 * @brief Initializes the voting machine.
 * 
 * Configures GPIO pins and displays the voting guide.
 */
void VotingMachine::begin() {
    configurePin(pinDI1);
    configurePin(pinDI2);
    configurePin(pinDI3);
    configurePin(pinDI4);
    configurePin(pinDI8);

    Serial.println("Voting Machine Initialized");
    displayGuide();
}

/**
 * @brief Monitors GPIO inputs and registers votes based on user input.
 * 
 * Also checks for the end voting signal and displays the results.
 */
void VotingMachine::checkVotes() {
    if (debouncedInput(pinDI1, 0)) { // DI1 -> Candidate 1
        registerVote(CANDIDATE_1, "Candidate 1");
    }

    if (debouncedInput(pinDI2, 1)) { // DI2 -> Candidate 2
        registerVote(CANDIDATE_2, "Candidate 2");
    }

    if (debouncedInput(pinDI3, 2)) { // DI3 -> Candidate 3
        registerVote(CANDIDATE_3, "Candidate 3");
    }

    if (debouncedInput(pinDI4, 3)) { // DI4 -> Candidate 4
        registerVote(CANDIDATE_4, "Candidate 4");
    }

    if (debouncedInput(pinDI8, 4)) { // DI8 -> End Voting
        displayResults();
        holdingRegs[VOTING_STATUS] = 1; // Voting complete status
        delay(5000); // Pause before resetting
    }
}

/**
 * @brief Configures the given GPIO pin as an input with pull-up resistor.
 * 
 * @param pin The GPIO pin to configure.
 */
void VotingMachine::configurePin(int pin) {
    pinMode(pin, INPUT_PULLUP);
}

/**
 * @brief Displays instructions for using the voting machine.
 */
void VotingMachine::displayGuide() {
    Serial.println("\n--- Voting Machine Interface ---");
    Serial.println("Press the corresponding button to vote:");
    Serial.println("DI1 -> Vote for Candidate 1");
    Serial.println("DI2 -> Vote for Candidate 2");
    Serial.println("DI3 -> Vote for Candidate 3");
    Serial.println("DI4 -> Vote for Candidate 4");
    Serial.println("DI8 -> End Voting and Show Results");
    Serial.println("---------------------------------");
}

/**
 * @brief Debounces GPIO input to ensure accurate button press detection.
 * 
 * @param pin The GPIO pin to read input from.
 * @param index The index of the button in the button state array.
 * @return true if the button press is valid and debounced, false otherwise.
 */
bool VotingMachine::debouncedInput(int pin, int index) {
    static bool buttonPressed[5] = {false};
    bool reading = digitalRead(pin);

    if (reading == LOW) {
        if (!buttonPressed[index]) {
            buttonPressed[index] = true;
            return true;
        }
    } else {
        buttonPressed[index] = false;
    }

    return false;
}

/**
 * @brief Registers a vote for a candidate.
 * 
 * @param candidate The candidate index to register a vote for.
 * @param candidateName The name of the candidate.
 */
void VotingMachine::registerVote(int candidate, const char* candidateName) {
    holdingRegs[candidate]++;
    holdingRegs[TOTAL_VOTES]++;
    Serial.print("Vote registered for ");
    Serial.println(candidateName);
    delay(200); // Feedback delay
}

/**
 * @brief Displays the voting results.
 */
void VotingMachine::displayResults() {
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
}
