#include <Arduino.h>

// Define constants for candidates 
#define CANDIDATE_1 0
#define CANDIDATE_2 1
#define CANDIDATE_3 2
#define CANDIDATE_4 3
#define TOTAL_VOTES 4
#define VOTING_STATUS 5

#define HOLDING_REGS_SIZE 6
unsigned int holdingRegs[HOLDING_REGS_SIZE] = {0};

// GPIO pins for voting inputs
const int pinDI1 = 33; // Candidate 1 
const int pinDI2 = 25; // Candidate 2 
const int pinDI3 = 26; // Candidate 3
const int pinDI4 = 27; // Candidate 4 
const int pinDI8 = 14; // End voting

class VotingMachine {
public:
    void begin() {
        configurePin(pinDI1);
        configurePin(pinDI2);
        configurePin(pinDI3);
        configurePin(pinDI4);
        configurePin(pinDI8);

        Serial.println("Voting Machine Initialized");
        displayGuide();
    }

    void checkVotes() {
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

private:
    void configurePin(int pin) {
        pinMode(pin, INPUT_PULLUP);
    }

    void displayGuide() {
        Serial.println("\n--- Voting Machine Interface ---");
        Serial.println("Press the corresponding button to vote:");
        Serial.println("DI1 -> Vote for Candidate 1");
        Serial.println("DI2 -> Vote for Candidate 2");
        Serial.println("DI3 -> Vote for Candidate 3");
        Serial.println("DI4 -> Vote for Candidate 4");
        Serial.println("DI8 -> End Voting and Show Results");
        Serial.println("---------------------------------");
    }

    bool debouncedInput(int pin, int index) {
        static bool buttonPressed[5] = {false};
        bool reading = digitalRead(pin);

        // If button is pressed (LOW for active-low configuration)
        if (reading == LOW) {
            // If this button hasn't been pressed before
            if (!buttonPressed[index]) {
                buttonPressed[index] = true;
                return true;
            }
        } else {
            // Reset button state when released
            buttonPressed[index] = false;
        }

        return false;
    }

    void registerVote(int candidate, const char* candidateName) {
        holdingRegs[candidate]++;
        holdingRegs[TOTAL_VOTES]++;
        Serial.print("Vote registered for ");
        Serial.println(candidateName);
        delay(200); // Feedback delay
    }

    void displayResults() {
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
};

VotingMachine votingMachine;

void setup() {
    Serial.begin(115200); // Serial for debugging
    votingMachine.begin(); // Initialize Voting Machine
}

void loop() {
    votingMachine.checkVotes();
}