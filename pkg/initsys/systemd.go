package initsys

import "os"

func IsSystemd() bool {
	// check for systemd specific files/directories
	if _, err := os.Stat("/run/systemd/system"); err == nil {
		return true
	}
	return false
}
