package main

import (
	"fmt"
)

func main() {
	var T int
	fmt.Scan(&T)

	for i := 0; i < T; i++ {
		var N int
		var S string
		fmt.Scan(&N, &S)

		l := -1
		r := N

		for j := 0; j < N-1; j++ {
			if S[j] > S[j+1] {
				l = j
				break
			}
		}

		if l == -1 {
			fmt.Println(S)
			continue
		}

		for j := l + 1; j < N; j++ {
			if S[l] < S[j] {
				r = j
				break
			}
		}

		var ans string
		ans = S[:l] + S[l+1:r] + string(S[l]) + S[r:]
		fmt.Println(ans)
	}
}
