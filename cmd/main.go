package main

import (
	"flag"
	"fmt"
	"os"
	"os/user"
	"runtime"
        "tuinit/pkg/initsys"
)

const (
	Version = "0.1.0"
)

func checkRoot() bool {
	currentUser, err := user.Current()
	if err != nil {
		fmt.Println("Error getting current user: ", err)
		os.Exit(1)
	}
	return currentUser.Uid == "0"
}

func printVersion() {
	fmt.Printf("tuinit version %s\n", Version)
	fmt.Printf("Go version: %s\n", runtime.Version())
	// add other dependencies versions here
	os.Exit(0)
}

func main() {
	// define flags
	version := flag.Bool("version", false, "print version information")
	flag.Parse()

	// handle version flag
	if *version {
		printVersion()
	}

	// check if running as root
	if !checkRoot() {
		fmt.Println("tuinit must be run as root")
		os.Exit(1)
	}

	fmt.Println("tuinit is running as root")
	initsys.IsSystemd()
}
