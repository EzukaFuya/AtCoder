package main

import (
	"fmt"
)

func main() {
	var S string
	fmt.Scan(&S)

	var nums []int

	var counter int
	for _, c := range S {
		if c == '|' {
			if counter != 0 {
				nums = append(nums, counter)
				counter = 0
			}
		} else {
			counter++
		}
	}

	for i, n := range nums {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(n)
	}
	fmt.Println()
}
