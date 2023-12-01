package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"unicode"
)

func readFile(filePath string) ([]string, error) {
	content, err := os.ReadFile(filePath)
	if err != nil {
		return nil, err
	}

	lines := strings.Split(string(content), "\n")

	return lines, nil
}

func findFirstAndLastDigit(line string) (int, error) {
	var firstDigit, lastDigit rune
	for _, char := range line {
		if unicode.IsDigit(char) {
			if firstDigit == 0 {
				firstDigit = char
			}
			lastDigit = char
		}
	}
	if firstDigit == 0 {
		return 0, fmt.Errorf("no digits found in the string")
	}

	joinedStr := string(firstDigit) + string(lastDigit)
	joinedInt, err := strconv.Atoi(joinedStr)
	if err != nil {
		return 0, err
	}

	return joinedInt, nil
}

func main() {
	filePath := `C:\Users\BlueShift\Documents\GitHub\advent-of-code-23\D1\Nagao\input_modified.txt`

	fileContent, err := readFile(filePath)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	sumCalibration := 0
	for _, line := range fileContent {
		value, err := findFirstAndLastDigit(line)
		if err != nil {
			fmt.Println("Error reading file:", err)
			return
		}
		sumCalibration += value
	}

	fmt.Println(sumCalibration)
}
