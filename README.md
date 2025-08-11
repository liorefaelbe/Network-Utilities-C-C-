# Network Utilities (C & C++)

A cross-language (C and C++) network utilities library implementing TCP, UDP, and broadcast communication for both client and server applications. Designed for embedded systems and cross-compilation for ARM.

## Features
- TCP Client & Server implementations in C
- UDP Client & Server implementations in C
- UDP Broadcast sender & receiver
- C++ server interface (`server.hpp`)
- Shared libraries (`libnetwork_c.so`, `libnetwork_cpp.so`) for reusability
- ARM cross-compilation support

## Directory Structure
- **inc/** – Public header files
- **src/** – Implementation files
- **test/** – Example usage and test programs
- **Makefile** – Build instructions

## Build Instructions
```bash
# Compile the shared libraries and test programs
make

# Run TCP server
./tcp_s

# Run TCP client
./tcp_c
