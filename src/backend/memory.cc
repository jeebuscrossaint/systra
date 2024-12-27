//
// Created by amarnath on 12/26/24.
//

#include "memory.hh"

MEM::MEM() {
}

MEM::~MEM() {
}

memoryStats MEM::getStats() const {
        memoryStats stats = {0, 0, 0, 0, 0};
        std::ifstream meminfo("/proc/meminfo");
        std::string line;

        while (std::getline(meminfo, line)) {
                std::istringstream iss(line);
                std::string key;
                uint64_t value;
                std::string unit;

                iss >> key >> value >> unit;

                if (key == "MemTotal:") {
                        stats.total = value;
                } else if (key == "MemFree:") {
                        stats.free = value;
                } else if (key == "Buffers:") {
                        stats.buffers = value;
                } else if (key == "Cached:") {
                        stats.cached = value;
                }
        }

        stats.used = stats.total - stats.free - stats.buffers - stats.cached;
        return stats;
}