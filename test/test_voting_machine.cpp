/**
 * @file test.cpp
 * @brief Unit tests for the VotingMachine class using the Unity testing framework.
 * 
 * This file includes tests to verify the functionality of the VotingMachine class, 
 * including vote registration, multiple votes, and voting status. The tests use a 
 * wrapper class to access private members for testing purposes.
 * 
 * @author [Your Name]
 * @date [Date]
 */

#include <unity.h>
#include "VotingMachine.h"
#include <Arduino.h>

/// GPIO pins for voting inputs
const int pinDI1 = 33; ///< Pin for Candidate 1
const int pinDI2 = 25; ///< Pin for Candidate 2
const int pinDI3 = 26; ///< Pin for Candidate 3
const int pinDI4 = 27; ///< Pin for Candidate 4
const int pinDI8 = 14; ///< Pin for End Voting

/**
 * @class TestVotingMachine
 * @brief A test wrapper class derived from VotingMachine to access private members for testing.
 */
class TestVotingMachine : public VotingMachine {
public:
    /**
     * @brief Accessor for private holdingRegs member.
     * @return Pointer to the holding registers array.
     */
    unsigned int* getHoldingRegs() {
        return holdingRegs;
    }

    /**
     * @brief Mock method to register a vote for testing purposes.
     * 
     * @param candidate The candidate index to register a vote for.
     * @param candidateName The name of the candidate.
     */
    void mockRegisterVote(int candidate, const char* candidateName) {
        holdingRegs[candidate]++;
        holdingRegs[TOTAL_VOTES]++;
    }
};

// Global test object
TestVotingMachine votingMachine;

/**
 * @brief Set up function for Unity tests.
 * 
 * Reinitializes the voting machine object before each test.
 */
void setUp(void) {
    votingMachine = TestVotingMachine();
}

/**
 * @brief Tear down function for Unity tests.
 * 
 * Cleans up after each test, if necessary.
 */
void tearDown(void) {
    // No specific teardown actions required
}

/**
 * @brief Test to verify initialization of the VotingMachine.
 */
void test_VotingMachine_Initialization(void) {
    votingMachine.begin();
    unsigned int* regs = votingMachine.getHoldingRegs();
    TEST_ASSERT_EQUAL_UINT(0, regs[CANDIDATE_1]);
    TEST_ASSERT_EQUAL_UINT(0, regs[CANDIDATE_2]);
    TEST_ASSERT_EQUAL_UINT(0, regs[CANDIDATE_3]);
    TEST_ASSERT_EQUAL_UINT(0, regs[CANDIDATE_4]);
    TEST_ASSERT_EQUAL_UINT(0, regs[TOTAL_VOTES]);
}

/**
 * @brief Test to verify vote registration for a single candidate.
 */
void test_VotingMachine_VoteRegistration(void) {
    votingMachine.mockRegisterVote(CANDIDATE_1, "Candidate 1");
    unsigned int* regs = votingMachine.getHoldingRegs();
    TEST_ASSERT_EQUAL_UINT(1, regs[CANDIDATE_1]);
    TEST_ASSERT_EQUAL_UINT(1, regs[TOTAL_VOTES]);
}

/**
 * @brief Test to verify multiple votes for the same candidate.
 */
void test_VotingMachine_MultipleVotes(void) {
    for (int i = 0; i < 3; i++) {
        votingMachine.mockRegisterVote(CANDIDATE_3, "Candidate 3");
    }
    unsigned int* regs = votingMachine.getHoldingRegs();
    TEST_ASSERT_EQUAL_UINT(3, regs[CANDIDATE_3]);
    TEST_ASSERT_EQUAL_UINT(3, regs[TOTAL_VOTES]);
}

/**
 * @brief Test to verify votes for multiple candidates.
 */
void test_VotingMachine_MultiCandidateVoting(void) {
    votingMachine.mockRegisterVote(CANDIDATE_1, "Candidate 1");
    votingMachine.mockRegisterVote(CANDIDATE_2, "Candidate 2");
    votingMachine.mockRegisterVote(CANDIDATE_3, "Candidate 3");
    unsigned int* regs = votingMachine.getHoldingRegs();
    TEST_ASSERT_EQUAL_UINT(1, regs[CANDIDATE_1]);
    TEST_ASSERT_EQUAL_UINT(1, regs[CANDIDATE_2]);
    TEST_ASSERT_EQUAL_UINT(1, regs[CANDIDATE_3]);
    TEST_ASSERT_EQUAL_UINT(3, regs[TOTAL_VOTES]);
}

/**
 * @brief Test to verify the end of voting status.
 */
void test_VotingMachine_EndVoting(void) {
    votingMachine.mockRegisterVote(CANDIDATE_1, "Candidate 1");
    votingMachine.mockRegisterVote(CANDIDATE_2, "Candidate 2");
    unsigned int* regs = votingMachine.getHoldingRegs();
    regs[VOTING_STATUS] = 1;
    TEST_ASSERT_EQUAL_UINT(1, regs[VOTING_STATUS]);
}

/**
 * @brief Arduino setup function to run Unity tests.
 * 
 * Configures GPIO pins and executes the test suite.
 */
void setup() {
    pinMode(pinDI1, INPUT);
    pinMode(pinDI2, INPUT);
    pinMode(pinDI3, INPUT);
    pinMode(pinDI4, INPUT);
    pinMode(pinDI8, INPUT);
    UNITY_BEGIN();
    RUN_TEST(test_VotingMachine_Initialization);
    RUN_TEST(test_VotingMachine_VoteRegistration);
    RUN_TEST(test_VotingMachine_MultipleVotes);
    RUN_TEST(test_VotingMachine_MultiCandidateVoting);
    RUN_TEST(test_VotingMachine_EndVoting);
    UNITY_END();
}

/**
 * @brief Arduino loop function.
 * 
 * This is intentionally left empty as Unity tests are executed in setup().
 */
void loop() {
    // Unity tests run in setup()
}
