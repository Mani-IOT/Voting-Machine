#ifndef VOTING_MACHINE_H
#define VOTING_MACHINE_H

#include <Arduino.h>

/**
 * @file VotingMachine.h
 * @brief Header file for the VotingMachine class.
 * 
 * Defines the interface and constants for a voting machine implementation.
 */

// Define constants for candidates
#define CANDIDATE_1 0 ///< Index for Candidate 1
#define CANDIDATE_2 1 ///< Index for Candidate 2
#define CANDIDATE_3 2 ///< Index for Candidate 3
#define CANDIDATE_4 3 ///< Index for Candidate 4
#define TOTAL_VOTES 4 ///< Index for Total Votes
#define VOTING_STATUS 5 ///< Index for Voting Status

#define HOLDING_REGS_SIZE 6 ///< Size of the holding registers

/**
 * @class VotingMachine
 * @brief Class for implementing a simple voting machine.
 * 
 * The class provides methods to initialize the machine, process votes, and display results.
 */
class VotingMachine {
    friend void loop(); ///< Grant the `loop` function access to private members
    friend class TestVotingMachine;  // Grant access to the test class

public:
    /**
     * @brief Constructor for VotingMachine.
     * 
     * Initializes internal state and prepares the object for use.
     */
    VotingMachine();

    /**
     * @brief Initialize the voting machine.
     * 
     * Sets up GPIO pins and displays instructions for users.
     */
    void begin();

    /**
     * @brief Check for button presses and process votes.
     * 
     * This method handles debouncing and registering votes for candidates.
     */
    void checkVotes();

private:
    unsigned int holdingRegs[HOLDING_REGS_SIZE] = {0}; ///< Array to store vote counts and voting status

    /**
     * @brief Configure a GPIO pin as an input with a pull-up resistor.
     * 
     * @param pin The GPIO pin number to configure.
     */
    void configurePin(int pin);

    /**
     * @brief Display a user guide for operating the voting machine.
     */
    void displayGuide();

    /**
     * @brief Check if a button press is debounced.
     * 
     * @param pin The GPIO pin to check.
     * @param index The index of the button in the state tracking array.
     * @return True if the button was pressed without bounce, false otherwise.
     */
    bool debouncedInput(int pin, int index);

    /**
     * @brief Register a vote for a specific candidate.
     * 
     * @param candidate The candidate index to vote for.
     * @param candidateName The name of the candidate (for display purposes).
     */
    void registerVote(int candidate, const char* candidateName);

    /**
     * @brief Display the results of the voting process.
     */
    void displayResults();
};

#endif
