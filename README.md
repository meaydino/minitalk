*This project has been created as part of the 42 curriculum by meaydino.*

# Minitalk

Minitalk is a small client-server communication application developed using exclusively UNIX signals (`SIGUSR1` and `SIGUSR2`).

## Description

The objective of this project is to implement a robust and fast inter-process communication (IPC) protocol using UNIX signals. 
- The **Server** starts, prints its Process ID (PID), and waits for incoming signals. It reconstructs characters from incoming bits and prints them to the standard output.
- The **Client** takes the Server's PID and a string as arguments, then sends the string character-by-character, bit-by-bit to the server.

### Features
- **Reliable Signal Transmission**: In the bonus version, a bidirectional signaling protocol is established where the server sends an acknowledgment signal back to the client for every bit received. This prevents signal loss (Linux does not queue signals when a signal of the same type is already pending).
- **Unicode / UTF-8 Support**: Supports multi-byte UTF-8 encoded characters, including non-ASCII letters, emojis, and symbols.
- **Zero Memory Leaks**: Both client and server manage memory without any dynamic heap allocations, avoiding any memory leak vulnerabilities.
- **Single Global Variable Limit**: The client uses only one global variable (as allowed and justified for handling asynchronous signals). The server runs completely without global variables by maintaining its state with function-scope `static` variables.

## Instructions

### Compilation
Build the project using the provided `Makefile`:

- Build the mandatory version:
  ```bash
  make
  ```
- Build the bonus version (acknowledgment protocol):
  ```bash
  make bonus
  ```
- Clean object files:
  ```bash
  make clean
  ```
- Clean all compiled files (including binaries and libft):
  ```bash
  make fclean
  ```
- Recompile from scratch:
  ```bash
  make re
  ```

### Execution

1. Start the server in one terminal:
   ```bash
   ./server
   ```
   It will print its PID, for example: `Server PID: 12345`

2. Send a message from the client in another terminal:
   ```bash
   ./client <server_pid> "<string_to_send>"
   ```
   Example:
   ```bash
   ./client 12345 "🚀 Hello Minitalk! 🌟"
   ```

## Resources

### References
- [GNU C Library - Signal Handling](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)
- [sigaction(2) Linux Manual Page](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [kill(2) Linux Manual Page](https://man7.org/linux/man-pages/man2/kill.2.html)
- [UTF-8 encoding standard](https://en.wikipedia.org/wiki/UTF-8)

### AI Usage Description
This project was co-authored and implemented with the assistance of an agentic AI coding assistant (Antigravity by Google DeepMind).
- **Tasks performed by AI**:
  - Drafting the initial technical implementation plan.
  - Generating C source code for the mandatory and bonus parts of `client` and `server`.
  - Creating a robust top-level `Makefile` that handles dependency compilation and prevents unnecessary relinking.
  - Designing an automated test script (`test.sh`) to validate message integrity, UTF-8 compatibility, and acknowledgment logic.
  - Investigating potential signal race conditions and memory leak verification using `valgrind`.
