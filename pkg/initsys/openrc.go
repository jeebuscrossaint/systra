package initsys

import "os"

func IsOpenRC() bool {
	// check for openrc specific files/directories
	if _, err := os.Stat("/run/openrc"); err == nil {
		return true
	}
	return false
}
