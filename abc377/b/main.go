package main

import (
	"fmt"
)

func main() {
	// 方法1: 文字列として読み取り、各文字をmapに登録
	var s [8][]rune
	for i := 0; i < 8; i++ {
		var str string
		fmt.Scan(&str)
		s[i] = []rune(str)
	}

	var luke_pos [][2]int
	for i := 0; i < 8; i++ {
		for j := 0; j < 8; j++ {
			if s[i][j] == '#' {
				luke_pos = append(luke_pos, [2]int{i, j})
			}
		}
	}

	for _, pos := range luke_pos {
		i, j := pos[0], pos[1]
		for k := 0; k < 8; k++ {
			s[i][k] = '#'
			s[k][j] = '#'
		}
	}

	var counter int
	for i := 0; i < 8; i++ {
		for j := 0; j < 8; j++ {
			if s[i][j] == '.' {
				counter++
			}
		}
	}

	fmt.Println(counter)
}
