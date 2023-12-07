package main

import (
	"bufio"
	"fmt"
	"os"
)

// func FindSymbol(line string) [] {
// 	return

// }

func readFile(filePath string) ([]string, error) {
	file, err := os.Open(filePath)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return nil, nil
	}
	defer file.Close()

	// Read lines from the file
	scanner := bufio.NewScanner(file)
	var grid []string
	for scanner.Scan() {
		grid = append(grid, scanner.Text())
	}
	fmt.Println(grid)
	return grid, nil
}

func main() {
	filePath := `C:\Users\BlueShift\Documents\GitHub\advent-of-code-23\D3\Nagao\input_Nagao_teste.txt`
	// sum_id := 0
	grid, err := readFile(filePath)
	fmt.Println(grid)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	var totalSum int

	//matrix_teste := [][]string

	// for _, line := range fileContent {
	// 	fmt.Println(line)
	// 	// for char := range line { //char é a posição dentro do array
	// 		// if char != '.' {
	// 		// 	//teste = append(teste, char, strings.Index(line, strings.Index[line, char]))

	// 		// }
	// 	}
	// }
	// fmt.Println((sum_id))

}
