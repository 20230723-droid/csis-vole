#include "MainMemory.h"
#include <iomanip>
#include <sstream>

MainMemory::MainMemory() { clear(); }

void MainMemory::clear() {
    for (int i = 0; i < SIZE; ++i) cells[i] = 0;
}

bool MainMemory::write(int address, unsigned char value) {
    if (address < 0 || address >= SIZE) return false;
    cells[address] = value;
    return true;
}

unsigned char MainMemory::read(int address) const {
    if (address < 0 || address >= SIZE) return 0;
    return cells[address];
}

std::string MainMemory::readHex(int address) const {
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
        << (int)cells[address];
    return oss.str();
}
