//
// Created by amarnath on 12/26/24.
//

#ifndef SYSTRA_MEMORY_HH
#define SYSTRA_MEMORY_HH

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

struct memoryStats {
        uint64_t total;
        uint64_t used;
        uint64_t free;
        uint64_t buffers;
        uint64_t cached;
};

class MEM {
public:
        MEM();
        ~MEM();
protected:
        memoryStats getStats() const; // this function should be able to do everything we need to get the memory stats
private:
        float usage;
        float swapUsage;
        float cache;
        float buffer;
};

#endif //SYSTRA_MEMORY_HH
