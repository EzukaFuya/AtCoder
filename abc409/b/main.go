package main

import (
	"fmt"
	"sort"
)

func main() {
	var N int
	fmt.Scan(&N)

	A := make([]int, N)
	for i := 0; i < N; i++ {
		fmt.Scan(&A[i])
	}

	sort.Ints(A)
	sort.Slice(A, func(i, j int) bool {
		return A[i] > A[j]
	})

	ans := 0
	for i := 0; i < N; i++ {
		if A[i] <= (i + 1) {
			ans = max(ans, A[i])
		} else {
			ans = max(ans, i+1)
		}
	}
	fmt.Println(ans)
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
