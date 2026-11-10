#ifndef PROGRAMLOADER_H
#define PROGRAMLOADER_H

#include <string>
#include "MainMemory.h"

// Reads a Vole machine program file, filters out comments and blank
// lines, validates every instruction, and loads the program into memory.
// Any invalid instruction causes the WHOLE program to be rejected.
class ProgramLoader {
public:
    // Loads the program into memory starting at startAddress
    // (must be an even number: 00, 02, 04, ... FE).
    // Returns true on success. On failure returns false and fills errorMessage.
    bool load(const std::string& filename, MainMemory& memory,
              int startAddress, std::string& errorMessage);

private:
    static std::string cleanLine(const std::string& line); // remove comment + whitespace
    static bool isHexDigit(char c);
    static bool isValidInstruction(const std::string& s);  // exactly 4 hex digits
};

#endif
