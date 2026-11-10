#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include <string>

// Simulates the Vole machine main memory: 256 cells, each cell is 8 bits.
class MainMemory {
public:
    static const int SIZE = 256;

    MainMemory();

    void clear();                                  // reset all cells to 0x00
    bool write(int address, unsigned char value);  // false if address out of range
    unsigned char read(int address) const;         // 0 if out of range
    std::string readHex(int address) const;        // e.g. "3F"

private:
    unsigned char cells[SIZE];
};

#endif
