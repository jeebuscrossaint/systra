//
// Created by amarnath on 12/25/24.
//

#ifndef SYSTRA_CPU_HH
#define SYSTRA_CPU_HH

#include <vector>
#include <string>
#include <cstdint>
#include <regex>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

struct cache {
        int level;
        size_t size;
};

struct load {
        double load1;
        double load5;
        double load15;
};

struct power {
        int power;
        int voltage;
        int current;
};

class CPU {
public:
        CPU();
        ~CPU();
protected:
        std::string getModel() const; // simply get the model fo the cpu and like other name vendor related stuff
        std::vector<int> getUtilization() const; // Utilization of per core, in percentage and in order of core number along with overall utilization as last element
        float getFreq() const; // get the frequency of the cpu
        int getTemp() const; // temperature of the cpu
        std::vector<cache> getCache() const; // get the cache and cache usage and cache percentage of the cpu
        power getPower() const; // get the power consumption of the cpu
        load getLoad() const; // get the load of the cpu in 1, 5 and 15 minutes
        uint64_t interruptRate() const; // get the interrupt rate of the cpu
        bool isVirtual() const; // check if the cpu is virtual or not
        uint64_t instructionsPerSec() const; // get the instructions per second of the cpu

private:
        std::string model;
        std::vector<int> utilization;
        float freq;
        int temp;
        std::vector<cache> caches;
        power powerConsumption;
        load load;
        uint64_t interrupt;
        bool virtualCpu;
        uint64_t instructions;
};


#endif //SYSTRA_CPU_HH
