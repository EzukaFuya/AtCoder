package main

import (
	"fmt"
)

func main() {
	var N, L int
	fmt.Scan(&N)
	fmt.Scan(&L)

	d := make([]int, N)

	d[0] = 0
	for i := 1; i < N; i++ {
		var num int
		fmt.Scan(&num)
		d[i] = (d[i-1] + num) % L
	}

	var mp map[int]int
	mp = make(map[int]int)
	for i := 0; i < N; i++ {
		mp[d[i]]++
	}

	var counter int
	for i := 0; i < L/3; i++ {
		if L%3 != 0 {
			continue
		}
		counter += mp[i] * mp[i+L/3] * mp[i+2*L/3]
	}

	fmt.Println(counter)

}

func min(a, b, c int) int {
	if a > b && b > c {
		return c
	} else if a > b && c > b {
		return b
	} else if b > a && a > c {
		return c
	} else if b > a && c > a {
		return a
	}
	return a
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
