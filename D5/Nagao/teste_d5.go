package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	// Read input from the file
	file, err := os.Open(`C:\Users\BlueShift\Documents\GitHub\advent-of-code-23\D5\Nagao\example_Nagao_D5.txt`)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	// Define maps for relationships
	seedToSoil := make(map[int][]int)
	soilToFertilizer := make(map[string][]int)
	fertilizerToWater := make(map[string][]int)
	waterToLight := make(map[string][]int)
	lightToTemperature := make(map[string][]int)
	temperatureToHumidity := make(map[string][]int)
	humidityToLocation := make(map[string][]int)

	// Parse input and populate maps
	currentMap := ""
	for scanner.Scan() {
		line := scanner.Text()

		if strings.Contains(line, "seed-to-soil map") {
			currentMap = "seed-to-soil"
		} else if strings.Contains(line, "soil-to-fertilizer map") {
			currentMap = "soil-to-fertilizer"
		} else if strings.Contains(line, "fertilizer-to-water map") {
			currentMap = "fertilizer-to-water"
		} else if strings.Contains(line, "water-to-light map") {
			currentMap = "water-to-light"
		} else if strings.Contains(line, "light-to-temperature map") {
			currentMap = "light-to-temperature"
		} else if strings.Contains(line, "temperature-to-humidity map") {
			currentMap = "temperature-to-humidity"
		} else if strings.Contains(line, "humidity-to-location map") {
			currentMap = "humidity-to-location"
		} else if strings.Contains(line, ":") {
			// Parse the current map relationships
			parts := strings.Split(line, ":")
			category, values := strings.TrimSpace(parts[0]), strings.Fields(parts[1])

			key_value := category

			var valueSlice []int
			for _, valueStr := range values {
				value, err := strconv.Atoi(valueStr)
				if err != nil {
					fmt.Println("Error converting value to integer:", err)
					return
				}
				valueSlice = append(valueSlice, value)
			}

			// Populate the appropriate map
			switch currentMap {
			case "seed-to-soil":
				seedToSoil[key_value] = valueSlice
			case "soil-to-fertilizer":
				soilToFertilizer[key_value] = valueSlice
			case "fertilizer-to-water":
				fertilizerToWater[key_value] = valueSlice
			case "water-to-light":
				waterToLight[key_value] = valueSlice
			case "light-to-temperature":
				lightToTemperature[key_value] = valueSlice
			case "temperature-to-humidity":
				temperatureToHumidity[key_value] = valueSlice
			case "humidity-to-location":
				humidityToLocation[key_value] = valueSlice
			}
		}
	}

	// Print the populated maps
	fmt.Println("Seed to Soil Map:", seedToSoil)
	fmt.Println("Soil to Fertilizer Map:", soilToFertilizer)
	fmt.Println("Fertilizer to Water Map:", fertilizerToWater)
	fmt.Println("Water to Light Map:", waterToLight)
	fmt.Println("Light to Temperature Map:", lightToTemperature)
	fmt.Println("Temperature to Humidity Map:", temperatureToHumidity)
	fmt.Println("Humidity to Location Map:", humidityToLocation)
}
