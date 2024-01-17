// As they're making the final adjustments, they discover that their calibration document (your puzzle input) has been amended by a very young Elf who was apparently just excited to show off her art skills. Consequently, the Elves are having trouble reading the values on the document.
// 
// The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.
// 
// For example:
// 
// 1abc2
// pqr3stu8vwx
// a1b2c3d4e5f
// treb7uchet
// 
// In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.
// 
// Consider your entire calibration document. What is the sum of all of the calibration values?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Number {
    int val;
    char *spell;
} Number;

Number createNumber(int val, char *spell){
    Number new;
    new.val = val;
    new.spell = (char *)malloc(sizeof(char) * 30);
    if (spell != NULL) strcpy(new.spell, spell);
    return new;
}

Number *specialStartup(){
    int vals[] = {21, 18, 82,83, 58, 98, 38, 0};
    char *spells[] = {
        "twone",
        "oneight",
        "eightwo",
        "eighthree",
        "fiveight",
        "nineight",
        "threeight",
        NULL
    };
    Number *numbers = (Number *)malloc(sizeof(Number)*10), *ptrNumber = numbers;
    int *ptrInt = vals;
    char **ptrChars = spells;
    while (*ptrInt && *ptrChars){
        *ptrNumber++ = createNumber(*ptrInt++, *ptrChars++);
    }
    ptrNumber->val = 0; 
    ptrNumber->spell = NULL;
    return numbers;
}

Number *startupNumbers(){
    int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    char *spells[] = { // must be aware of a solution to not return null pointers here
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
        NULL
    };
    Number *numbers = (Number *)malloc(sizeof(Number)*10), *ptrNumber = numbers;
    int *ptrInt = vals;
    char **ptrChars = spells;
    while (*ptrInt && *ptrChars){
        *ptrNumber++ = createNumber(*ptrInt++, *ptrChars++);
    }
    ptrNumber->val = 0; 
    ptrNumber->spell = NULL;
    return numbers;
}

int getNumberByName(char *name, Number *numberList){
    int counter = 0;
    Number *availables = numberList;
    while (availables->spell){
        if (strcmp(name, availables->spell) == 0) {
            return counter;
        }
        counter++, availables++;
    }
    return -1;
}

char *readFile(char* fileName){
    char *source = NULL;
    FILE *fp = fopen(fileName, "r");
    if (fp != NULL){
        if (fseek(fp, 0L, SEEK_END) == 0){
            long bufsize = ftell(fp);
            if (bufsize == -1) { return "Error on finding file size."; }
            source = malloc(sizeof(char) * bufsize);
            if (fseek(fp, 0L, SEEK_SET) != 0) { return "Error on returning to the start of the file."; }
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if (ferror(fp) != 0){ return "Error on reading the file."; }
            else{ source [newLen++] = '\0'; }
        }
    }
    fclose(fp);
    return source;
}

int twoDigitResult(int *arr){
    // get arr size, considering that there are not zeros in the input
    printf("Array: {");
    int *ptr = arr, count = 0;
    while (*ptr++ != 0){
        printf("%d, ", *(arr + count));
        count++;
    };
    printf("}\n");
    int alg = (count == 1) ? *arr : *(arr + count - 1); // if the size is one, then there's only one number, therefore we use it again as algarism
    int res = (*arr * 10) + alg; // the first number and the last number
    free(arr); // cleanup
    return res; 
}

int getNumbersInLine(char *line){
    char *character = line;
    int *arr = (int *)calloc(10, sizeof(int)*10), *ptr = arr;
    while (*character != '\n'){
        int asciiVal = (int) *character;
        if (0 <= asciiVal - 48 && asciiVal - 48 <= 9){ // if the true value is between 0 and 9, respectively
            *ptr++ = asciiVal - 48;
        }
           character++;
    }
    return twoDigitResult(arr);
}

int isPartialSpelled(char *ptrCopy, Number *numberList, char character, int pos){
    Number *ptrNumber = numberList;
    // char *ppCopy = ptrCopy;
    char *letter = NULL;
    while (ptrNumber->spell){
        letter = ptrNumber->spell + pos;
        if (*letter == character) // it shall return 1, since there's at least one char that, in the same position, may have the char array
            return 1;
        //      else if (*(ppCopy - 1)){
        //          if (*letter == character && *(ppCopy - 1) == *(letter - 1)) // check if the letter before and after are part of the word, kind of a linked list
        //              return 1;
        ptrNumber++;
    }
    // it shall return 0 if the next character isn't present, in that position, in any of the string arrays
    return 0;
    }

// sorry, I stole and adapted that one from
// https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
void replaceWord(char* str, char* oldWord, int newvalue) {
    char *pos = str;
    char *ptrOld = oldWord;
    int oldSize = 0;
    while (*ptrOld++) oldSize++; // get the size of the old word
    char *newWord = (char *)calloc(oldSize, sizeof(char)*oldSize); // max size will always be 2, but we'll assign some garbage here
    sprintf(newWord, "%d", newvalue);
 
    // Repeat This loop until all occurrences are replaced.
 
    while ((pos = strstr(str, oldWord)) != NULL) {
        // replace the word with the number, and leave the rest as garbage value
        // garbage value may not be a good idea, because it may include separators like '\n' or other numbers that may poison the data; maybe we'll replace them with zeroes?
        for (int i = 0; i < oldSize; i++){
            if (*(newWord + i) != '\0') *(pos + i) = *(newWord + i);
            else *(pos + i) = 'l';
        }
    }
}

int getAllNumbersInLine(char *line, Number *numberList){
    char *character = line;
    char *copy = (char *)calloc(10, sizeof(char)*10); // copy the character if it is part of any of the letters; if any of them is not, break away and free it;
                                                  // if copy isn't null and strcmp with any of the spelled out numbers is true, return that number
                                                  // else, free it
    char *ptrCopy = copy;
    int *arr = (int *)calloc(10, sizeof(int)*10), pos = 0, *ptr = arr;
    while (*character != '\n'){
        int asciiVal = (int) *character;
        if (0 <= asciiVal - 48 && asciiVal - 48 <= 9){ // if the true value is between 0 and 9, respectively
            *ptr++ = asciiVal - 48;
            pos = 0; // must return the position back to the place
            ptrCopy = copy;
        }
        else { // if it's not a number, check if it's part of a spelled number
            if (isPartialSpelled(ptrCopy, numberList, *character, pos)){
                *ptrCopy++ = *character;
                pos++;
            } 
            else {
                pos = 0; 
                ptrCopy = copy; // we return the pointer to the first original character
                if (isPartialSpelled(ptrCopy, numberList, *character, pos)){ // we check again if it's in the first position; it's not the right elegant
                    *ptrCopy++ = *character;
                    pos++;
                }
            }
            // check if the spelled string already forms a number
            int res = getNumberByName(copy, numberList);
            if (res != -1){ 
                // if it's true, then we found a value, clear the memory and let's do it again
                *ptr++ = numberList[res].val;
                // char *tempchar;
                // strcpy(tempchar, (ptrCopy - 1));
                free(copy); // if I free this, I lose possibilites like 'twone' or 'threeight'; how can I NOT hardcode them?
                copy = (char *)calloc(10, sizeof(char)*10);
                ptrCopy = copy;
                // *ptrCopy = *tempchar;
                pos = 0;
                // if (isPartialSpelled(ptrCopy, numberList, *character, pos)){ // again, not elegant, but let's see if it works
                //     *ptrCopy++ = *character;
                //     pos++;
                // }
            }
        }
        character++;
    }
    return twoDigitResult(arr);
}

int main(){
    char *text = readFile("day1.txt");
    Number *numbers = startupNumbers(), *specialNumbers = specialStartup();
    while (specialNumbers->val){ // cleaning all special numbers
        replaceWord(text, specialNumbers->spell, specialNumbers->val);
        specialNumbers++;
    }
    while (numbers->val){ // now replacing normal numbers
        replaceWord(text, numbers->spell, numbers->val);
        numbers++;
    }
    int counter = 0, sum = 0;
    // printf("%s", text);
    while (text){
        if (!*text) break;
        int res = getAllNumbersInLine(text, numbers);
        printf("%d: %d\n", counter++, res);
        sum += res;
        text = strchr(text, '\n');
        text++;
    }
    printf("Final: %d", sum);
    return 0;
}
