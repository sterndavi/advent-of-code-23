package main

import (
	"fmt"
	"os"
	"regexp"
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

func findWinningNumbers(input string) int {

	parts := strings.Split(input, "|")

	part1 := convertToIntSlice(strings.Fields(parts[0]))
	part2 := convertToIntSlice(strings.Fields(parts[1]))

	// Compare the two slices element-wise
	var count int = 0
	for _, num1 := range part1 {
		for _, num2 := range part2 {
			if num1 == num2 {
				count++
				break
			}
		}
	}
	if count == 0 {
		return 0
	} else {
		return count

	}
}

func convertToIntSlice(strSlice []string) []int {
	intSlice := make([]int, len(strSlice))
	for i, str := range strSlice {
		num, err := strconv.Atoi(str)
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

	fileContent, err := readFile(filePath)
	fmt.Println(len(fileContent))
	copies := make([]int, len(fileContent))
	for i := range copies {
		copies[i] = 1
	}
	if err != nil {
		fmt.Println("Error reading file1:", err)
		return
	}
	fmt.Println(copies)

	for _, line := range fileContent {
		re := regexp.MustCompile(`\s+`)
		cleaned_line := re.ReplaceAllString(line, " ")
		games := strings.Split(cleaned_line, ":")

		index := strings.Split(string(games[0]), " ")
		index_line, error := strconv.Atoi(index[1])
		fmt.Printf("games: %s, index[0]: %s, index[1]: %d \n", games, index[0], index_line)
		counter := copies[index_line-1]
		for j := 0; j < counter; j++ {
			//fmt.Printf(" Copies: %d, j: %d, copies{j]: %d, line: %s \n", copies, j, copies[j], line)
			countOfGameCopies := findWinningNumbers(games[1])
			for i := 0; i < countOfGameCopies; i++ {
				fmt.Printf("i: %d, index_line: %d\n", i, index_line)
				copies[i+index_line]++
			}
		}
		if error != nil {
			fmt.Println("Error reading file2:", err)
			return
		}

	}
	sum := 0
	for _, value := range copies {
		sum += value
	}
	fmt.Println(sum)
}
