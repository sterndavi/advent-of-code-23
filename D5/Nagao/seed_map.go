package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strings"
)

func readFile(filePath string, mode string) ([]string, error) {
	if mode == "line" {
		content, err := os.ReadFile(filePath)
		if err != nil {
			return nil, err
		}

		lines := strings.Split(string(content), "\n")
		fmt.Println(lines)
		return lines, nil
	} else {
		file, err := os.Open(filePath)
		if err != nil {
			fmt.Println("Error opening file:", err)
			return nil, nil
		}
		defer file.Close()

		scanner := bufio.NewScanner(file)
		var grid []string
		for scanner.Scan() {
			grid = append(grid, scanner.Text())
		}
		return grid, nil

	}
}

func SplitMaps(grid string) ([]int, []int, []int, []int, []int, []int, []int, []int) {
	seedsMatch := regexp.MustCompile(`(\d+)\s*seeds`) //`(\d+)\s*red`
	seeds := seedsMatch.FindAllStringSubmatch(grid, -1)
	return
}

func main() {

	filePath := `C:\Users\BlueShift\Documents\GitHub\advent-of-code-23\D5\Nagao\example_Nagao_D5.txt`

	fileContent, err := readFile(filePath, "grid")
	if err != nil {
		fmt.Println("Error reading file1:", err)
		return
	}
	seeds, soil, fertilizer, water, light, temperature, humiditu, location := SplitMaps(fileContent)

}
