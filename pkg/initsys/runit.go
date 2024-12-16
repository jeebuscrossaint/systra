package initsys

import "os"

func IsRunit() bool {
	// check for runit specific files/directories
	if _, err := os.Stat("/etc/runit"); err == nil {
		return true
	}
	return false
}
