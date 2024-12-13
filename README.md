# Voting Machine Code Readme

### Overview
This project implements a **Voting Machine** using an **ESP32** microcontroller. It allows users to vote for one of four candidates via digital inputs, and the results are displayed on the serial monitor.

### Features
- Supports voting for four candidates.
- Displays voting instructions on the serial monitor.
- Ends voting and shows results when a specific button is pressed.
- Keeps track of the total votes for each candidate.

### Components Used
- **Microcontroller**: ESP32
- **GPIO Pins**: Used for voting input buttons:
  - DI1 -> Vote for Candidate 1
  - DI2 -> Vote for Candidate 2
  - DI3 -> Vote for Candidate 3
  - DI4 -> Vote for Candidate 4
  - DI8 -> Ends Voting and Displays Results

### Register Mapping
| Register      | Purpose                    | Index |
|---------------|----------------------------|-------|
| `CANDIDATE_1` | Votes for Candidate 1      | 0     |
| `CANDIDATE_2` | Votes for Candidate 2      | 1     |
| `CANDIDATE_3` | Votes for Candidate 3      | 2     |
| `CANDIDATE_4` | Votes for Candidate 4      | 3     |
| `TOTAL_VOTES` | Total votes cast           | 4     |
| `VOTING_STATUS` | Voting completion status | 5     |

### Serial Monitor Instructions
- The serial monitor displays the following instructions:
  ```
  --- Voting Machine Interface ---
  Press the corresponding button to vote:
  DI1 -> Vote for Candidate 1
  DI2 -> Vote for Candidate 2
  DI3 -> Vote for Candidate 3
  DI4 -> Vote for Candidate 4
  DI8 -> End Voting and Show Results
  ---------------------------------
  ```

### Example Output:
```
--- Voting Machine Interface ---
Press the corresponding button to vote:
DI1 -> Vote for Candidate 1
DI2 -> Vote for Candidate 2
DI3 -> Vote for Candidate 3
DI4 -> Vote for Candidate 4
DI8 -> End Voting and Show Results
---------------------------------
Vote registered for Candidate 1
Vote registered for Candidate 2
Vote registered for Candidate 3
Vote registered for Candidate 4

--- Voting Results ---
Candidate 1 Votes: 3
Candidate 2 Votes: 2
Candidate 3 Votes: 2
Candidate 4 Votes: 3
Total Votes: 10
```

