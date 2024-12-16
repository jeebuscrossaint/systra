package tui

import (
	"fmt"
	"io/ioutil"
	"os/exec"
	"strings"
    
	tea "github.com/charmbracelet/bubbletea"
	"tuinit/pkg/initsys"
	"tuinit/pkg/util"
    )

func getSystemdVersion() string {
	output, err := exec.Command("systemctl", "--version").Output()
	if err != nil {
	    return "N/A"
	}
	lines := strings.Split(string(output), "\n")
	if len(lines) > 0 {
	    return strings.Fields(lines[0])[1]
	}
	return "N/A"
    }
    
    func getOpenRCVersion() string {
	output, err := exec.Command("openrc", "--version").Output()
	if err != nil {
	    return "N/A"
	}
	return strings.TrimSpace(string(output))
    }
    
    func getRunitVersion() string {
	// Implement runit version retrieval if possible
	return "N/A"
    }
    
    func getDistroInfo() string {
	data, err := ioutil.ReadFile("/etc/os-release")
	if err != nil {
	    return "Unknown"
	}
	for _, line := range strings.Split(string(data), "\n") {
	    if strings.HasPrefix(line, "PRETTY_NAME=") {
		return strings.Trim(line[13:], "\"")
	    }
	}
	return "Unknown"
    }

func InitialModel() model {
    var initSystem, initSystemVersion, distro string

    // Detect init system
    switch {
    case initsys.IsSystemd():
        initSystem = "systemd"
        initSystemVersion = getSystemdVersion()
    case initsys.IsOpenRC():
        initSystem = "OpenRC"
        initSystemVersion = getOpenRCVersion()
    case initsys.IsRunit():
        initSystem = "runit"
        initSystemVersion = getRunitVersion()
    default:
        initSystem = "Unknown"
        initSystemVersion = "N/A"
    }

    // Get distro information
    distro = getDistroInfo()

    // Get program version from util package
    programVersion := util.Version

    return model{
        initSystem:        initSystem,
        initSystemVersion: initSystemVersion,
        distro:            distro,
        programVersion:    programVersion,
    }
}

func (m model) Init() tea.Cmd {
    return nil
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
    switch msg := msg.(type) {
    case tea.KeyMsg:
        if msg.String() == "q" || msg.String() == "ctrl+c" {
            return m, tea.Quit
        }
    }
    return m, nil
}

func (m model) View() string {
	header := fmt.Sprintf(
	    "Init System: %s %s | Distro: %s | tuinit %s\n\n",
	    m.initSystem, m.initSystemVersion, m.distro, m.programVersion,
	)
	return header + "Press 'q' to quit."
    }