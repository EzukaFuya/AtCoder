package main

import (
	"fmt"
	"strconv"
)

func main() {
	var N int
	fmt.Scan(&N)

	var N_string string
	N_string = strconv.Itoa(N)
	N_digit := make(map[int]int)

	for _, num := range N_string {
		var n int
		n, _ = strconv.Atoi(string(num))
		N_digit[n]++
	}

	if N_digit[1] == 1 && N_digit[2] == 2 && N_digit[3] == 3 {
		fmt.Println("Yes")
	} else {
		fmt.Println("No")
	}
}
