// Nを入力として受け取り、次にN個の整数を入力として受け取る。
// そして、入力された整数を小さい順に出力する。
package main

import (
    "fmt"
    "sort"
)

func main() {
    var n int
    fmt.Scan(&n)

    var a []int
    for i := 0; i < n; i++ {
        var x int
        fmt.Scan(&x)
        a = append(a, x)
    }

    sort.Ints(a)
    for _, x := range a {
        fmt.Printf("%d ", x)
    }
    fmt.Println()
}
