## Voting Machine Code ReadMe

### Overview
This project implements a voting machine using an **EXT IO Card** connected to a microcontroller ( ESP32). It uses Modbus communication for managing and recording votes and displays a user-friendly guide via the serial monitor.

### Features
- Supports four candidates with real-time vote tallying.
- Displays voting instructions on the serial monitor.
- Ends voting and displays results when a specific input is triggered.
- Stores voting data in Modbus holding registers for external system communication.

### Components Used
- **Microcontroller**: ESP32.
- **Multiplexer**: For managing multiple digital inputs (CD74HC4067).
- **EXTIO_Lib**: Custom library for handling multiplexer-based input/output operations.
- **SimpleModbusSlave**: Library for Modbus communication.

### Register Mapping
| Register      | Purpose                 | Index |
|---------------|-------------------------|-------|
| `CANDIDATE_1` | Votes for Candidate 1   | 0     |
| `CANDIDATE_2` | Votes for Candidate 2   | 1     |
| `CANDIDATE_3` | Votes for Candidate 3   | 2     |
| `CANDIDATE_4` | Votes for Candidate 4   | 3     |
| `TOTAL_VOTES` | Total votes registered  | 4     |
| `VOTING_STATUS` | Voting complete status | 5     |


### Serial Monitor Guide
- The program displays voting instructions at the start.
- Example output:
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
