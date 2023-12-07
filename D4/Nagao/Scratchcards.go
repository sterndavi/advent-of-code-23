package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func readFile(filePath string) ([]string, error) {
	content, err := os.ReadFile(filePath)
	if err != nil {
		return nil, err
	}

	lines := strings.Split(string(content), "\n")
	fmt.Println(lines)
	return lines, nil
}

func findWinningNumbers(input string) float64 {
	var sum_points_game float64 = 0
	parts := strings.Split(input, "|")

	part1 := convertToFloatSlice(strings.Fields(parts[0]))
	part2 := convertToFloatSlice(strings.Fields(parts[1]))

	// Compare the two slices element-wise
	var count float64 = 0
	for _, num1 := range part1 {
		for _, num2 := range part2 {
			if num1 == num2 {
				count++
				break // break the inner loop when a match is found for the current number in part1
			}
		}
	}
	if count == 0 {
		fmt.Println("No Matching Number")
		return 0
	} else {
		fmt.Printf("Matching numbers: %f", count)
		sum_points_game = sum_points_game + math.Pow(2, count-1)
	}

	return sum_points_game
}

// Helper function to convert a slice of strings to a slice of integers
func convertToFloatSlice(strSlice []string) []float64 {
	intSlice := make([]float64, len(strSlice))
	for i, str := range strSlice {
		num, err := strconv.ParseFloat(str, 64)
		if err != nil {
			fmt.Println("Error converting string to int:", err)
			return nil
		}
		intSlice[i] = num
	}
	return intSlice
}

func main() {
	filePath := `C:\Users\BlueShift\Documents\GitHub\advent-of-code-23\D4\Nagao\input_Nagao_D4.txt`
	var sum_points float64 = 0
	fileContent, err := readFile(filePath)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
	for _, line := range fileContent {
		games := strings.Split(line, ":")

		points_per_game := findWinningNumbers(games[1])

		sum_points += points_per_game
		fmt.Println(sum_points)
		if err != nil {
			fmt.Println("Error reading file:", err)
			return
		}
	}
	fmt.Println((sum_points))

}
