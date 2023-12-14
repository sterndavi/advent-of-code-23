# Daniel Readme
## Highlights

- Quick and dirty solution. There are some gaps in the memory allocation, counting spaces as size but having more spaces than needed generates memory leaks. Since the example is small it's fine, but it's a fair warning.
- I reuse some of my helper functions like `myPow`, `readFile` and `concatArray`. Next time I'll make a `utils.c` with them and ship it with the result, so the code looks a little less cluttered.
- I created two modes in the `getLineNums`, one for each part of the challenge. It seeks the whole line for all numbers, so to avoid create a new function, I just created a dirty `switch-case` method.
- I had to convert every `int` method to `long` and adjust variables accordingly, and may start to use them as longs for the next challenges just to avoid this kind of hackiness if I find the inputs too long.
