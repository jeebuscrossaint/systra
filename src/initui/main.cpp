#include "initui.hh"
#include <ncurses.h>
#include <cstdlib>
#include <memory>

using namespace InitUI;

void cleanup_ncurses() {
    endwin();
}

std::string get_uname_output() {
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("uname -a", "r"), pclose);
    if (!pipe) return "Error getting system information";
    
    char buffer[128];
    std::string result;
    
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    
    return result;
}

InitSystem detect_init_system() {
    if (system("which systemctl >/dev/null 2>&1") == 0) return InitSystem::SYSTEMD;
    if (system("which rc-status >/dev/null 2>&1") == 0) return InitSystem::OPENRC;
    if (system("which sv >/dev/null 2>&1") == 0) return InitSystem::RUNIT;
    return InitSystem::UNKNOWN;
}

std::string get_init_version() {
    switch (detect_init_system()) {
        case InitSystem::SYSTEMD:
            return "systemd (version info TBD)";
        case InitSystem::OPENRC:
            return "OpenRC (version info TBD)";
        case InitSystem::RUNIT:
            return "runit (version info TBD)";
        default:
            return "Unknown init system";
    }
}

namespace InitUI {
    SystemInfo get_system_info() {
        SystemInfo info;
        info.uname = get_uname_output();
        info.init_system = detect_init_system();
        info.init_version = get_init_version();
        return info;
    }
}

int main() {
    // Initialize ncurses
    initscr();
    std::atexit(cleanup_ncurses);
    
    // Enable color if available
    start_color();
    use_default_colors();
    
    // Get terminal dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Get system information
    InitUI::SystemInfo info = InitUI::get_system_info();
    
    // Rest of the code remains the same
    mvprintw(1, 2, "InitUI Version: %s", VERSION.c_str());
    mvprintw(3, 2, "System Information:");
    mvprintw(4, 4, "%s", info.uname.c_str());
    mvprintw(6, 2, "Init System: %s", info.init_version.c_str());
    
    mvprintw(max_y-2, 2, "Press any key to exit");
    refresh();
    getch();
    
    return 0;
}