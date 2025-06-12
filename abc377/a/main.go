package main

import (
	"fmt"
)

func main() {
	// 方法1: 文字列として読み取り、各文字をmapに登録
	var s string
	fmt.Scan(&s)
	
	alphabet := make(map[rune]bool)
	
	// 文字列の各文字をmapに登録
	for _, char := range s {
		alphabet[char] = true
	}
	
	// A, B, Cの存在確認
	_, exist_A := alphabet['A']
	_, exist_B := alphabet['B']
	_, exist_C := alphabet['C']
	
	if exist_A && exist_B && exist_C {
		fmt.Println("Yes")
	} else {
		fmt.Println("No")
	}
}
