package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"unicode"
)

func replaceWordsWithNumbers(input string) string {
	wordsToNumbers := map[string]string{
		"one":   "1",
		"two":   "2",
		"three": "3",
		"four":  "4",
		"five":  "5",
		"six":   "6",
		"seven": "7",
		"eight": "8",
		"nine":  "9",
	}

	input = strings.Replace(input, "twone", "21", -1)
	input = strings.Replace(input, "oneight", "18", -1)
	input = strings.Replace(input, "eightwo", "82", -1)
	input = strings.Replace(input, "eighthree", "83", -1)
	input = strings.Replace(input, "fiveight", "58", -1)
	input = strings.Replace(input, "nineight", "98", -1)
	input = strings.Replace(input, "threeight", "38", -1)

	for word, number := range wordsToNumbers {
		input = strings.Replace(input, word, number, -1)
	}
	return input
}

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
	filePath := ``

	fileContent, err := readFile(filePath)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	sumCalibration := 0
	for _, line := range fileContent {
		line_converted := replaceWordsWithNumbers(line)
		value, err := findFirstAndLastDigit(line_converted)
		if err != nil {
			fmt.Println("Error reading file:", err)
			return
		}
		sumCalibration += value
	}

	fmt.Println(sumCalibration)
}
