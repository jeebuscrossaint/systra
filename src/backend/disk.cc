//
// Created by amarnath on 12/27/2024.
//

#include "disk.hh"

DISK::DISK() {};
DISK::~DISK() {};

std::vector<std::string> DISK::getAllDisks() {
        std::vector<std::string> disks;
        std::ifstream disksFile("/proc/partitions");

        if (disksFile.is_open()) {
                std::string line;
                while (std::getline(disksFile, line)) {
                        // Extract disk names using regex
                        std::smatch match;
                        if (std::regex_search(line, match, std::regex("\\b(sd[a-z]|hd[a-z]|nvme[0-9]n[0-9])\\b"))) {
                                disks.push_back(match[1]);
                        }
                }
                disksFile.close();
        } else {
                std::cerr << "Error opening /proc/partitions" << std::endl;
        }

        return disks;
}