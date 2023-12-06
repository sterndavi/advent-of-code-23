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

int charIsSpecial(char character){
    int ascii = (int) character; // considering the special characters in the ascii table, ranges 33~47 and 58~64
    if (((33 <= ascii && ascii <= 47) || (58 <= ascii && ascii <= 64)) && ascii != 46) return 1; // removing the dot as a special character from the ascii table as well
    return 0;
}

int charIsNumber(char character){
    int ascii = (int) character - '0';
    if (0 <= ascii && ascii <= 9) return 1; // if we find a digit between 0 and 9
    return 0;
}

int isSymbolAround(char *pos, int lineLength){
    char *character = pos;
    char positions[] = {
        *(pos - lineLength - 1), // diagonal up left
        *(pos - lineLength),     // up
        *(pos - lineLength + 1), // diagonal up right
        *(pos - 1),              // left
        *(pos + lineLength - 1), // diagonal left down
        *(pos + lineLength),     // down
        *(pos + lineLength + 1), // diagonal right down
        *(pos + 1),              // right
        'z'                      // random terminator
    };
    char *currPos = positions;
    while (*currPos != 'z'){ // iterate through every character in the defined positions
        if (charIsSpecial(*currPos++)) return 1;
    }
    return 0;
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

int main(int argc, char* argv[]){
    char *fileText, *startPos, *endPos;
    if (argv[1]){
        fileText = readFile(argv[1]);
    }
    else{
        printf("Por favor, informe um arquivo corretamente.");
        return 1;
    }
    int lineLength = getEndOfLine(fileText), hasSymbol = 0;
    int *numbers = (int *)malloc(sizeof(int) * 3);
    int nNumber = 0, nLine = 0, count, sum = 0, val;
    while (*fileText){
        // resets
        count = 0;
        hasSymbol = 0;
        numbers[0] = 0;
        numbers[1] = 0;
        numbers[2] = 0;
        if (charIsNumber(*fileText)){
            startPos = fileText; // set the start position for the first number
            hasSymbol = (!hasSymbol) ? isSymbolAround(startPos, lineLength) : hasSymbol; // if hasSymbol is still zero, check for presence; else, keep the old value (0 or 1)
            endPos = startPos;
            while (charIsNumber(*endPos)){
                numbers[count++] = (int) *endPos - '0';
                hasSymbol = (!hasSymbol) ? isSymbolAround(endPos, lineLength) : hasSymbol; // if hasSymbol is still zero, check for presence; else, keep the old value (0 or 1)
                endPos++;
            }
            if (hasSymbol){
                val = concatArray(numbers, count);
                printf("Line %d, %d° number: %d\n", nLine + 1, nNumber++ + 1, val);
                sum += val;
//              printf("Current Sum: %d\n", sum);
//              printf("-------------------------------------------\n");
//              getchar();
            } 
            fileText = endPos++; // jump to the end of the found number
        }
        if (*fileText == '\n') nLine++;
        fileText++;
    }
    printf("Sum: %d", sum);
    return 0;
}
