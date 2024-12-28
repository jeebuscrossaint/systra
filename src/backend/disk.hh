//
// Created by amarnath on 12/27/2024.
//

#ifndef SYSTRA_DISK_HH
#define SYSTRA_DISK_HH

#include <cstdint>
#include <string>
#include <vector>
#include <regex>

class DISK {
public:
	DISK();
        ~DISK();

protected:
	uint64_t getDiskUsage();
	uint64_t getDiskFreeUsage();
        std::vector<std::string> getAllDisks();

private:
	std::vector<std::string> diskNames;
};

#endif //SYSTRA_DISK_HH
