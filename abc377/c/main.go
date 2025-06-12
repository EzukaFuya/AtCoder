package main

import (
	"fmt"
)

func main() {
	var N, M int
	fmt.Scan(&N, &M)
	
	// ナイトの攻撃方向（8方向）
	knightMoves := [][2]int{
		{2, 1}, {1, 2}, {-1, 2}, {-2, 1},
		{-2, -1}, {-1, -2}, {1, -2}, {2, -1},
	}
	
	// 攻撃される位置を記録するセット
	attacked := make(map[[2]int]bool)
	
	// 既存のコマの位置を記録するセット
	occupied := make(map[[2]int]bool)
	
	// 既存のコマを読み取り、攻撃範囲を計算
	for i := 0; i < M; i++ {
		var a, b int
		fmt.Scan(&a, &b)
		
		// このコマの位置を占有マスとして記録
		occupied[[2]int{a, b}] = true
		
		// このコマから攻撃できる位置を記録
		for _, move := range knightMoves {
			nx := a + move[0]
			ny := b + move[1]
			
			// グリッド内かチェック
			if nx >= 1 && nx <= N && ny >= 1 && ny <= N {
				attacked[[2]int{nx, ny}] = true
			}
		}
	}
	
	// 総マス数
	totalCells := int64(N) * int64(N)
	
	// 占有されているマス数
	occupiedCount := int64(len(occupied))
	
	// 攻撃されるマス数（ただし、既に占有されているマスは除く）
	attackedCount := int64(0)
	for pos := range attacked {
		if !occupied[pos] {
			attackedCount++
		}
	}
	
	// 安全に置けるマス数
	safeCount := totalCells - occupiedCount - attackedCount
	
	fmt.Println(safeCount)
}
