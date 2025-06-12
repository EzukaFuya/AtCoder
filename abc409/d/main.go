package main

import (
	"fmt"
)

func solve(s string) string {
	n := len(s)
	best := s

	for l := 0; l < n; l++ {
		for r := l; r < n; r++ {
			// 左巡回シフトした結果を直接比較
			// s[l+1:r+1] + s[l] + の部分だけ見て判断可能
			if l < r {
				// s[l]を後ろに移動することで改善されるかチェック
				if s[l+1] < s[l] {
					rotated := s[:l] + s[l+1:r+1] + string(s[l]) + s[r+1:]
					if rotated < best {
						best = rotated
					}
				}
			}
		}
	}

	return best
}

func main() {
	var T int
	fmt.Scan(&T)

	for i := 0; i < T; i++ {
		var N int
		var S string
		fmt.Scan(&N, &S)

		fmt.Println(solve(S))
	}
}
