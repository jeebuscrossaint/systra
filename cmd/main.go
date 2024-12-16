package main

import (
	"fmt"
        "tuinit/pkg/initsys"
)

func main() {
	fmt.Println("Hello, World!")
	fmt.Println("Is systemd? ", initsys.IsSystemd())
}
