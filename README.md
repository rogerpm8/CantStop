# Can't Stop Probability Calculator 🎲

**Author:** Roger  
**Language:** C++  

![C++](https://img.shields.io/badge/Language-C++-blue)

---

## Overview

This project simulates the board game **Cant Stop** using 4 dice. It calculates:  

- Frequencies of sums of dice rolls  
- Probabilities of sum **pairs** and **triples**  
- **Ideal path lengths** for each sum, scaled from a reference sum, faithful to Cant Stop strategy  

The program is modular, separating logic into functions for clean and readable code.

---

## Features

- Generate all possible 4-dice rolls with a customizable number of sides  
- Compute sum counts, relative frequencies, and probabilities  
- Compute pair and triple probabilities  
- Calculate ideal path lengths based on probabilities in sum triples  
- Interactive mode to compute and display ideal paths  

---

## Usage

Compile the project:

```bash
g++ probCantStop.cpp functions.cpp -o probCantStop.exe
```

Run the executable:
```bash
./probCantStop.exe 
```

#### Follow the prompts:
1. Enter the number of sides on the dice
2. See frequencies, pair probabilities, and triple probabilities
3. Optionally compute ideal paths by entering a reference sum length

---

## File Structure
- `probCantStop.cpp` – main program, input/output handling

- `functions.cpp` – all helper functions for sum calculations, pair/triple probabilities, and ideal paths

## Notes 
- Probabilities are computed based on all possible 4-dice rolls
- Ideal paths are scaled from a reference sum, typically sum 2, giving a faithful Cant Stop strategy
- The program assumes 4 dice
