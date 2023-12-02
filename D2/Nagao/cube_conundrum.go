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
	validGames := 0

	// Define regular expressions for red, blue, and green dice
	redRegex := regexp.MustCompile(`(\d+)\s*red`)
	blueRegex := regexp.MustCompile(`(\d+)\s*blue`)
	greenRegex := regexp.MustCompile(`(\d+)\s*green`)

	// Split the input string by semicolon
	rounds := strings.Split(input, ";")

	// Iterate through each round
	for _, round := range rounds {
		gameCounts := make(map[string]int)

		// Count the occurrences of each color in each round
		redMatches := redRegex.FindAllStringSubmatch(round, -1)
		blueMatches := blueRegex.FindAllStringSubmatch(round, -1)
		greenMatches := greenRegex.FindAllStringSubmatch(round, -1)
		//fmt.Println(redMatches, blueMatches, greenMatches)
		// Update gameCounts based on matches
		for _, match := range redMatches {
			count := toInt(match[1])
			gameCounts["red"] += count
		}

		for _, match := range blueMatches {
			count := toInt(match[1])
			gameCounts["blue"] += count
		}

		for _, match := range greenMatches {
			count := toInt(match[1])
			gameCounts["green"] += count
		}

		// Check conditions for valid game
		if gameCounts["red"] <= 12 && gameCounts["green"] <= 13 && gameCounts["blue"] <= 14 {
			validGames = 1
		} else {
			return 0
		}
	}

	return validGames
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
		id := strings.Split(games[0], " ")
		if teste := countDiceThrows(games[1]); teste > 0 {
			fmt.Println("Jogo válido:")
			Id_int, erro := strconv.Atoi(id[1])
			sum_id += Id_int
			if erro != nil {
				fmt.Println("Error reading file:", err)
				return
			}
		} else {
			fmt.Println("Jogo Inválido")
		}

		if err != nil {
			fmt.Println("Error reading file:", err)
			return
		}
	}
	fmt.Println((sum_id))

}
