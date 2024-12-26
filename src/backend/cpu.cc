//
// Created by amarnath on 12/25/24.
//

#include "cpu.hh"

CPU::CPU() {
}; // Constructor IDK what to do in this right now

CPU::~CPU() {
}; // Destructor IDK what to do in this right now

std::string CPU::getModel() const {
        std::ifstream cpuinfo("/proc/cpuinfo");
        if (!cpuinfo.is_open()) {
                std::cerr << "Error: Could not open /proc/cpuinfo" << std::endl;
                return "Unknown CPU";
        }

        std::string line;
        while (std::getline(cpuinfo, line)) {
                if (line.find("model name") == 0) {
                        // Extract using regex
                        std::smatch match;
                        std::regex modelNameRegex("model name\\s*:\\s*(.*)");
                        if (std::regex_search(line, match, modelNameRegex)) {
                                return match[1].str();
                        }
                        break;
                }
        }

        cpuinfo.close();
        return "Unknown CPU";
}


std::vector<int> CPU::getUtilization() const {
        std::ifstream statFile("/proc/stat");
        if (!statFile.is_open()) {
                std::cerr << "Error: Could not open /proc/stat" << std::endl;
                return {};
        }

        std::vector<int> utilization;
        std::string line;
        std::vector<std::vector<uint64_t>> cpuStats;

        while (std::getline(statFile, line)) {
                if (line.find("cpu") == 0) {
                        std::istringstream ss(line);
                        std::string cpu;
                        uint64_t user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
                        ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
                        cpuStats.push_back({user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice});
                }
        }

        statFile.close();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        statFile.open("/proc/stat");
        if (!statFile.is_open()) {
                std::cerr << "Error: Could not open /proc/stat" << std::endl;
                return {};
        }

        std::vector<std::vector<uint64_t>> cpuStatsNew;
        while (std::getline(statFile, line)) {
                if (line.find("cpu") == 0) {
                        std::istringstream ss(line);
                        std::string cpu;
                        uint64_t user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
                        ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
                        cpuStatsNew.push_back({user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice});
                }
        }

        statFile.close();

        for (size_t i = 0; i < cpuStats.size(); ++i) {
                uint64_t prevIdle = cpuStats[i][3] + cpuStats[i][4];
                uint64_t idle = cpuStatsNew[i][3] + cpuStatsNew[i][4];

                uint64_t prevNonIdle = cpuStats[i][0] + cpuStats[i][1] + cpuStats[i][2] + cpuStats[i][5] + cpuStats[i][6] + cpuStats[i][7];
                uint64_t nonIdle = cpuStatsNew[i][0] + cpuStatsNew[i][1] + cpuStatsNew[i][2] + cpuStatsNew[i][5] + cpuStatsNew[i][6] + cpuStatsNew[i][7];

                uint64_t prevTotal = prevIdle + prevNonIdle;
                uint64_t total = idle + nonIdle;

                uint64_t totald = total - prevTotal;
                uint64_t idled = idle - prevIdle;

                double cpuPercentage = (totald - idled) * 100.0 / totald;
                utlization.push_back(static_cast<int>(cpuPercentage));
        }

        return utilization;
}

float CPU::getFreq() const {
        std::ifstream freqFile("/proc/cpuinfo");
        if (!freqFile.is_open()) {
                std::cerr << "Error: Could not open /proc/cpuinfo" << std::endl;
                return 0.0;
        }

        std::string line;
        while (std::getline(freqFile, line)) {
                if (line.find("cpu MHz") == 0) {
                        // extract cpu info using regex
                        std::smatch match;
                        std::regex freqRegex("cpu MHz\\s*:\\s*(\\d+\\.\\d+)");
                        if (std::regex_search(line, match, freqRegex)) {
                                return match[1].str(); + " MHz";
                        }
                        break;
                }
        }

        freqFile.close();
        return "Unknown Frequency";
}

int CPU::getTemp() const {
        std::ifstream tempFile("/sys/class/thermal/thermal_zone*/temp");
        if (!tempFile.is_open()) {
                std::cerr << "Error: Could not open /sys/class/thermal/thermal_zone*/temp" << std::endl;
                return -1;
        }

        std::string line;
        while (std::getline(tempFile, line)) {
                std::istringstream ss(line);
                int temp;
                ss >> temp;
                return temp / 1000;
        }

        tempFile.close();
        return -1;
}

std::vector<cache> CPU::getCache() const {
        std::vector<cache> caches;
        std::ifstream cacheFile("/proc/cpuinfo");

        if (!cacheFile.is_open()) {
                std::cerr << "Error: Could not open /proc/cpuinfo" << std::endl;
                return caches;
        }

        std::string line;
        std::regex levelRegex("cache: L\\d");
        std::regex sizeRegex("size\\s*:\\s*(\\d+)\\s*KB");

        int currentLevel = -1;
        size_t currentSize = 0;

        while (std::getline(file, line)) {
                if (std::regex_match(line, levelRegex)) {
                        // New cache level found
                        if (currentLevel != -1) {
                                // Store previous cache info
                                caches.push_back({currentLevel, currentSize});
                        }
                        currentLevel = std::stoi(line.substr(line.find('L') + 1, 1));
                        currentSize = 0;
                } else if (std::regex_match(line, sizeRegex)) {
                        std::smatch match;
                        if (std::regex_search(line, match, sizeRegex)) {
                                currentSize = std::stoul(match[1]);
                        }
                }
        }

        // Store the last cache info
        if (currentLevel != -1) {
                caches.push_back({currentLevel, currentSize});
        }

        file.close();

        return caches;
}

power CPU::getPower() const {
        power result = {0, 0, 0};
        std::ifstream powerFile("/sys/class/power_supply/BAT0/power_now");
        std::ifstream voltageFile("/sys/class/power_supply/BAT0/voltage_now");
        std::ifstream currentFile("/sys/class/power_supply/BAT0/current_now");

        if (powerFile) powerFile >> result.power;
        if (voltageFile) voltageFile >> result.voltage;
        if (currentFile) currentFile >> result.current;

        powerFile.close();
        voltageFile.close();
        currentFile.close();

        return result;
}

load CPU::getLoad() const {
        load result = {0.0, 0.0, 0.0};
        std::ifstream loadFile("/proc/loadavg");

        if (loadFile) {
                loadFile >> result.load1 >> result.load5 >> result.load15;
        }

        loadFile.close();

        return result;
}

uint64_t CPU::interruptRate() const {
        std::ifstream statFile("/proc/stat");
        std::string line;

        while (std::getline(stat, line)) {
                if (line.substr(0, 4) == "intr") {
                        uint64_t totalInterrupts = 0;
                        stat >> totalInterrupts; // First number after intr is the total number of interrupts
                        statFile.close();
                        return totalInterrupts;
                }
        }

        return 0;
}

bool isVirtual() const {
        std::ifstream cpuinfo("/proc/cpuinfo");
        std::string line;

        while (std::getline(cpuinfo, line)) {
                // Check common hypervisor signatures
                if (line.find("hypervisor") != std::string::npos ||
                    line.find("VMwareVMware") != std::string::npos ||
                    line.find("KVM") != std::string::npos ||
                    line.find("QEMU") != std::string::npos ||
                    line.find("VirtualBox") != std::string::npos ||
                    line.find("Xen") != std::string::npos) {
                        return true;
                }
        }

        return false;
}

uint64_t CPU::instructionsPerSec() const {

}