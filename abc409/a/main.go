package main

import (
	"fmt"
)

func main() {
	var N int
	var T, A string
	fmt.Scan(&N)
	fmt.Scan(&T)
	fmt.Scan(&A)

	for i := 0; i < N; i++ {
		if T[i] == A[i] && A[i] == 'o' {
			fmt.Println("Yes")
			return
		}
	}
	fmt.Println("No")
	return
}
