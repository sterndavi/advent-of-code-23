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

	return lines, nil
}

func countDiceThrows(input string) int {
	gameCounts := make(map[string][]int)
	redRegex := regexp.MustCompile(`(\d+)\s*red`)
	blueRegex := regexp.MustCompile(`(\d+)\s*blue`)
	greenRegex := regexp.MustCompile(`(\d+)\s*green`)
	rounds := strings.Split(input, ";")

	for _, round := range rounds {
		redMatches := redRegex.FindAllStringSubmatch(round, -1)
		blueMatches := blueRegex.FindAllStringSubmatch(round, -1)
		greenMatches := greenRegex.FindAllStringSubmatch(round, -1)
		//fmt.Println(redMatches, blueMatches, greenMatches)
		for _, match := range redMatches {
			count := toInt(match[1])
			gameCounts["red"] = append(gameCounts["red"], count)
			// fmt.Println(gameCounts["red"])
		}

		for _, match := range blueMatches {
			count := toInt(match[1])
			gameCounts["blue"] = append(gameCounts["blue"], count)
			// fmt.Println(gameCounts["blue"])
		}

		for _, match := range greenMatches {
			count := toInt(match[1])
			gameCounts["green"] = append(gameCounts["green"], count)
			// fmt.Println(gameCounts["green"])
		}

	}
	max := findMaxValues(gameCounts)
	power := max["red"] * max["blue"] * max["green"]
	// fmt.Println(max, power)
	return power

}

func findMaxValues(colorValues map[string][]int) map[string]int {
	maxValues := make(map[string]int)

	for color, values := range colorValues {

		max := findMax(values)

		maxValues[color] = max
	}

	return maxValues
}

func findMax(values []int) int {
	if len(values) == 0 {
		return 0
	}
	max := values[0]
	for _, v := range values[1:] {
		if v > max {
			max = v
		}
	}
	return max
}

func toInt(s string) int {
	val, err := strconv.Atoi(s)
	if err != nil {
		return 0
	}
	return val
}

func main() {
	filePath := `C:\Users\BlueShift\Documents\GitHub\advent-of-code-23\D2\Nagao\input_Nagao_D2.txt`
	sum_id := 0
	fileContent, err := readFile(filePath)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}
	for _, line := range fileContent {
		games := strings.Split(line, ":")

		teste := countDiceThrows(games[1])

		sum_id += teste

		if err != nil {
			fmt.Println("Error reading file:", err)
			return
		}
	}
	fmt.Println((sum_id))

}
