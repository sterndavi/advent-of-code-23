# Daniel Readme

## Highlights

- Part 1 iterates through the numbers, moving the pointer through it, and skipping lines with it. It has a lot of memory leaks, and this method wouldn't work for part 2.
- I refactored the code in part 2 via `day4b.c`, in which I created a `int map[]` of multiple numbers that represent the amount of times that game'll play. It is NOT efficient, nor it's the best way to do it; however, I was running out of options, and taking too much time.
- The memory leaking, I guess it's fixed in `day4b`? Nonetheless it takes a lot of time to work through these 240 numbers. I'd love some feedback on how to do this without the arrays, but for now, that'll have to suffice.
- I used `winCount` and removed the part of calculated points from part 1 so it could go a little faster; I was very wrong.
