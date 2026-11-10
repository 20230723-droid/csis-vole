// Application file - RENAME to: A2-YourSection-YourID-YourID.cpp
#include <iostream>
#include "MainMemory.h"
#include "ProgramLoader.h"

int main() {
    MainMemory memory;
    ProgramLoader loader;
    std::string errorMessage;

    std::string filename;
    int startAddress = 0;

    std::cout << "Enter program file name: ";
    std::cin >> filename;
    std::cout << "Enter start address (hex, even number e.g. 00): ";
    std::cin >> std::hex >> startAddress;

    if (loader.load(filename, memory, startAddress, errorMessage)) {
        std::cout << "Program loaded successfully into memory.\n";
        std::cout << "First instruction at " << startAddress
                  << ": " << memory.readHex(startAddress)
                  << memory.readHex(startAddress + 1) << "\n";
    } else {
        std::cout << errorMessage << "\n";
    }
    return 0;
}
