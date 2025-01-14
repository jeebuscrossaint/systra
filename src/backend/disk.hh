//
// Created by amarnath on 12/27/2024.
//

#ifndef SYSTRA_DISK_HH
#define SYSTRA_DISK_HH

#include <cstdint>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <sys/statvfs.h>

namespace fs = std::filesystem;

class DISK {
public:
	DISK();
        ~DISK();

protected:
	std::vector<uint64_t> getDiskData();
        std::vector<std::string> getAllDisks();

private:
	std::vector<std::string> diskNames;
};

#endif //SYSTRA_DISK_HH
