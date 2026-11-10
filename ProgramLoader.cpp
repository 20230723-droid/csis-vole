#include "ProgramLoader.h"
#include <cctype>
#include <fstream>

bool ProgramLoader::load(const std::string& filename, MainMemory& memory,
                         int startAddress, std::string& errorMessage) {
    // 1. Validate the start address (must be even and inside memory)
    if (startAddress < 0 || startAddress >= MainMemory::SIZE || (startAddress % 2 != 0)) {
        errorMessage = "Error: start address must be an even number between 00 and FE.";
        return false;
    }

    // 2. Open the program file
    std::ifstream file(filename);
    if (!file.is_open()) {
        errorMessage = "Error: could not open file '" + filename + "'.";
        return false;
    }

    std::string line;
    int lineNumber = 0;
    int address = startAddress;

    // 3. Read the file line by line
    while (std::getline(file, line)) {
        ++lineNumber;

        // Filter: remove comment (everything after ';') + spaces/tabs
        std::string instr = cleanLine(line);

        // Ignore empty lines and pure comment lines
        if (instr.empty()) continue;

        // Validate: exactly 4 hex digits, otherwise REJECT the program
        if (!isValidInstruction(instr)) {
            errorMessage = "Error: invalid instruction '" + instr +
                           "' at line " + std::to_string(lineNumber) +
                           ". Each instruction must be exactly 4 hex digits.";
            file.close();
            return false;
        }

        // Check the program still fits in memory
        if (address + 1 >= MainMemory::SIZE) {
            errorMessage = "Error: program does not fit in memory.";
            file.close();
            return false;
        }

        // Load the 4 hex digits (2 bytes) into memory, big-endian
        unsigned int value = std::stoul(instr, nullptr, 16);
        memory.write(address,     (value >> 8) & 0xFF);   // high byte
        memory.write(address + 1,  value & 0xFF);         // low byte
        address += 2;
    }

    file.close();
    return true;
}

std::string ProgramLoader::cleanLine(const std::string& line) {
    std::string result;
    for (char c : line) {
        if (c == ';') break;   // comment starts here: ignore the rest of the line
        if (c == ' ' || c == '\t' || c == '\r') continue;
        result += (char)std::toupper((unsigned char)c);   // normalize to uppercase
    }
    return result;
}

bool ProgramLoader::isHexDigit(char c) {
    return std::isxdigit((unsigned char)c) != 0;
}

bool ProgramLoader::isValidInstruction(const std::string& s) {
    if (s.length() != 4) return false;
    for (char c : s) {
        if (!isHexDigit(c)) return false;
    }
    return true;
}
