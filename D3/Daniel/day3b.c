#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int getEndOfLine(char *text){
    // finds the length of the line and returns a pointer to the final '\n' or NULL character in the line.
    char *letter = text;
    int count = 0;
    while (*letter++ != '\n') count++;
    return count + 1;
}

int myPow(int base, int power){
    int sum = 1;
    if (power < 0) return 0; // edge case for negatives
    while (power){
        sum *= base;
        power--;
    }
    return sum;
}

int concatArray(int arr[], int count){
    int *ptr = arr, sum = 0;
    for (int i = 0; i < count; i++){
        sum += *(ptr + i) * myPow(10, (count - 1 - i));
    }
    return sum;
}


int charIsNumber(char character){
    int ascii = (int) character - '0';
    if (0 <= ascii && ascii <= 9) return 1; // if we find a digit between 0 and 9
    return 0;
}

int seekNumber(char *pos){
    int *arr = (int *)malloc(sizeof(int)*3), *ptrArr = arr; // always three digit numbers
    char *currPos = pos;
    int countForward = 0, countBackward = 0, moveBackwards, size = 1; // first size will always be 1
    *ptrArr = (int) *currPos - '0'; // we know the current position is a number
                                    // seek forward
    for (int i = 1; charIsNumber(*(currPos + i)); countForward++, i++);
    // seek backward
    for (int i = 1; charIsNumber(*(currPos - i)); countBackward++, i++);
    size += countForward + countBackward; // get the size of the array
    moveBackwards = countBackward; // saving the times I need to return the pointer
    while (countForward){
        *(ptrArr + countForward) = (int) *(currPos + countForward) - '0';
        countForward--;
    }
    while (countBackward){
        *(ptrArr - countBackward) = (int) *(currPos - countBackward) - '0';
        countBackward--;
    } 
    // move pointer to the first number, if it isn't this one
    while (moveBackwards) arr--, moveBackwards--;
    return concatArray(arr, size);
}

int searchAroundGear(char *pos, int lineLength){
    char *character = pos;
    char *positions[] = {
        (pos - lineLength - 1), // diagonal up left
        (pos - lineLength),     // up
        (pos - lineLength + 1), // diagonal up right
        (pos - 1),              // left
        (pos + lineLength - 1), // diagonal left down
        (pos + lineLength),     // down
        (pos + lineLength + 1), // diagonal right down
        (pos + 1),              // right
        NULL
    };
    char **currPos = positions;
    int numbers[2] = {0, 0}, *ptrNumber = numbers, result; // the two numbers that'll multiply
    while (*currPos != NULL){ // iterate through every character in the defined positions
        if (charIsNumber(**currPos)){
            character = *currPos; // will this work?
            result = seekNumber(character);
            if (result != *(ptrNumber - 1)){ // if it's the same number from the previous place
                *ptrNumber++ = result;
            }
        } 
        currPos++;
    }
    return numbers[0] * numbers[1];
}

int main(int argc, char *argv[]){
    char *fileText;
    if (argv[1]){
        fileText = readFile(argv[1]);
    }
    else{
        printf("Por favor, informe um arquivo corretamente.");
        return 1;
    }
    int lineLength = getEndOfLine(fileText);
    int nNumber = 0, nLine = 0, count, sum = 0, val;
    while (*fileText){
        if (*fileText=='*'){
            val = searchAroundGear(fileText, lineLength);
            printf("Line %d, gear %d: %d\n", nLine + 1, nNumber++ + 1, val);
            sum += val;
        }
        if (*fileText++ == '\n') nLine++;
    }
    printf("Sum: %d", sum);
    return 0;
}
