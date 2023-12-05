# Daniel Readme

## Highlights

- This time, I separated the parts in two executables. In the first one, I searched for symbols around the numbers; in the second part, I did the opposite. The latter was more efficient, code-wise.
- I scrapped the helper functions like `charIsNumber` and `charIsSpecial`, and for part 1, used `isSymbolAround` to map a square around the value searching for a number.
- In part 2, I used `searchAroundGear` in conjunction of `seekNumber`, with a very simple (and inefficient) check if the value is the same as before.
