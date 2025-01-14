//
// Created by amarnath on 12/27/2024.
//

#include "disk.hh"

DISK::DISK() {};
DISK::~DISK() {};

// get critical disk data such as names usage free space human readable format percentage used other stuff

std::vector<uint64_t> getDiskData() {
        std::system("lsblk -o KNAME,TYPE,SIZE,MODEL");
};

