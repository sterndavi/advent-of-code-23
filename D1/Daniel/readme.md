# Daniel Readme

## Highlights

- I'm creating a struct called Number and using it as a dictionary, with the value and the corresponding string to be searched in the file.
- I've tried creating partial matches using `isPartialSpelled`, but that didn't went well, because I couldn't cover edge cases like 'twone', or 'eighthree'. I tried using some pointer magic, like a linked list (checking before and after the value), but it would bring more complications than help (I've left the commented lines for history).
- Instead I changed my approach to switch inplace the values and replace the rest of the letters with garbage (in this case represented by 'l'), so the line 
'97ninesevenrhchvppnztvfbfpkzrbcone'
 is transformed into 
'979lll7llllrhchvppnztvfbfpkzrbc1ll'. 
- I'm trying to do everything without the stack and avoiding hardcoded counters at all costs, so there are A LOT of pointers. Some `malloc`s are still 'magic', but it's fine for now.
