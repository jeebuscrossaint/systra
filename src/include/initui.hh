#ifndef INITUI_HH
#define INITUI_HH

#include <string>

namespace InitUI {
    const std::string VERSION = "0.1.0";

    enum class InitSystem {
        SYSTEMD,
        OPENRC,
        RUNIT,
        UNKNOWN
    };

    struct SystemInfo {
        std::string uname;
        InitSystem init_system;
        std::string init_version;
    };

    SystemInfo get_system_info();
}

#endif // INITUI_HH