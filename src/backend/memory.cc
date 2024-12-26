//
// Created by amarnath on 12/26/24.
//

#include "memory.hh"

MEM::MEM() {
        memoryStats = {0, 0, 0, 0, 0};
}

MEM::~MEM() {
        delete memoryStats;
}

memoryStats MEM::getStats() const {

}
