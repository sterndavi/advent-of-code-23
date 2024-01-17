# Daniel Readme

## Highlights

- I'm reusing the same function to read the whole file into an char array, so it makes it easier for me not to separate the buffer. 
- I get the position of the last line, separated by '\n', and iterate through the line while it isn't separated. A lot of strstr and strchr.
- I use `strToInt` to make my custom `strtol` or `atoi`.
- I save the numbers to an array and sum this by the power of the size (which will always be 1). Kind of overengineered.
- I generalized the perLine functions to `colorPerLine`, and used a simple boolean to see if the game is viable or not.
- I SHOULD use argc and argv to feed in the file, but I'm gonna wait for the test to be solved so I can refactor it to do so.
