
# Memory Management Simulation

## Overview

This program simulates memory management in a system using main memory and swap memory. It handles loading, running, and managing processes with memory page allocation and Least Recently Used (LRU) page replacement and First in First Out(FIFO) policy. The system supports commands to load executable files, run them, and simulate basic arithmetic and memory access operations.

The program works with the following memory structures:
- **Main Memory**: Divided into pages.
- **Swap Memory**: Used to store pages that cannot fit into main memory.
- **Page Table**: Each process maintains a page table mapping virtual memory pages to physical memory pages.
- **LRU**: Least Recently Used page replacement strategy is used to manage pages in main memory.
        (OR)
- **FIFO**: First in First Out replacement strategy is used to manage pages in main memory.      

### Features

- **Load Executable Files**: Loads a program into memory and assigns it a process ID (PID).
- **Run Executables**: Runs commands (`add`, `sub`, `print`, and `load`) from the loaded executable files.
- **Kill Processes**: Frees up memory by terminating a process.
- **List Processes**: Lists active processes with their assigned PIDs.
- **Page Table Management**: Allows viewing the page table of a specific process or all processes.
- **Memory Operations**: Handles memory access with page faults and swaps pages between main memory and swap memory if needed.

## Files

- **lru.cpp**: This is the C++ file that handles the memory management with Least recently used policy.
- **fifo.cpp**: This is the C++ file that handles the memory management with first in first out policy.
- **infile**: input file containing system calls.
- **executable files**:executable files denoting processes.
- **Output Files**: Various operations write results to specified output files.

## Setup

### Prerequisites

- **C++ compiler**: The program is written in C++ and needs a C++ compiler such as `g++` to run.
- **Standard C++ Libraries**: The program uses several standard libraries like iostream, vector, and queue.

## Compilation and Execution

1. **Compile the program**:
    ```bash
      make all
    ```
    
2. **Run the executable**:
    ```bash
    example: ./[lru | fifo] -M 32 -V 32 -P 512 -i infile -o outfile
    ```

3. **Available Commands**:

    - `load <executable_file>`: Load an executable file.
    - `run <PID>`: Run the loaded executable for the process with the given PID.
    - `kill <PID>`: Kill the process with the given PID, freeing up memory.
    - `list`: List all active processes.
    - `pte <PID>`: View the page table of a specific process.
    - `pteall`: View page tables of all active processes.
    - `print memloc length`: Display what is present in specific memory location.

