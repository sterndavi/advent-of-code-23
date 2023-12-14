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

long myPow(int base, int power){
    long sum = 1;
    if (power < 0) return 0; // edge case for negatives
    while (power){
        sum *= base;
        power--;
    }
    return sum;
}

int charIsNumber(char character){
    int ascii = (int) character - '0';
    if (0 <= ascii && ascii <= 9) return 1; // if we find a digit between 0 and 9
    return 0;
}

long concatArray(int arr[], int count){
    int *ptr = arr;
    long sum = 0;
    if (!(*ptr)) return -1;
    for (int i = 0; i < count; i++){
        sum += *(ptr + i) * myPow(10, (count - 1 - i));
    }
    free(ptr); // when I do this I SEGFAULT; wtf?
    return sum;
}

int createNumber(char **text){
    // while (!charIsNumber(**text++)) if (**text == '\n') return 0; // moving to the next number, if it isn't there yet; also returning if we find a linebreak
    char *ptr = *text;
    int size = 0, *arr;
    while (charIsNumber(*ptr++)) size++; // must ensure the next char IS indeed a number, always, else it'll break
    arr = (int *)malloc(sizeof(int)*(size + 1)); // giving space for the null terminator
    int i = 0;
    for (; i < size; *(arr + i) = (int) *(*text)++ - '0', i++); // moving the cursor to the next number
    *(arr + i) = 0; // putting the terminator
    text++; // moving one more to the right
    return concatArray(arr, size);
}

int *getLineNums(char **text, int part){
    char *ptr = *text;
    int size = 0, temp;
    while (!charIsNumber(**text)) (*text)++; // move to the next number
    while (*ptr != '\n') if (*ptr++ == ' ') size++; // get the size until the EOL
    int *arr = (int *)malloc(sizeof(int)*size), *ptrArr = arr;
    switch (part){
        case 1:
            while (**text != '\n'){
                while (!charIsNumber(**text)) (*text)++; // move to the next number
                if ((temp = createNumber(text))) *ptrArr++ = temp;
            }
            *ptrArr = -1;
        case 2:
            while (**text != '\n'){
                while (!charIsNumber(**text)) (*text)++; // move to the next number
                if (charIsNumber(**text)) *ptrArr++ = (int) *(*text)++ - '0';
            }
            *ptrArr = -1;
    }
    return arr;
}

long getWinningPlays(long time, long minDistance){
    long wins = 0, thisDistance;
    // if holding the button means +1u/ms for each ms you hold it, find the
    // minimum needed to hold to achieve the minDistance
    for (int hold = 0; hold < time; hold++){
        thisDistance = hold * (time - hold); 
        if (thisDistance > minDistance) wins++;
    }
    return wins;
}

int main(int argc, char *argv[]){
    char *fileText, *startPos;
    int *times,
     *distances,
     *newTimes,
     *newDistances,
     sum = 1,
     res;
    long finalTime = 1, finalDistance = 1;
    if (argv[1]){
        fileText = readFile(argv[1]);
    }
    else{
        printf("Por favor, informe um arquivo corretamente.");
        return 1;
    }
    startPos = fileText;
    times = getLineNums(&fileText, 1);
    distances = getLineNums(&fileText, 1);
    printf("Times: ");
    for (int i = 0 ; *(times + i) != -1; i++) printf("%d, ", *(times + i));
    printf("\nDistances: ");
    for (int i = 0; *(distances + i) != -1; i++) printf("%d, ", *(distances + i));
    printf("\nPossible wins per game:\n");
    for (int j = 0; *(times + j) != -1 && *(distances + j) != -1; j++){
        res = getWinningPlays(*(times + j), *(distances + j));
        printf("%d, ", res);
        sum *= res;
    }
    printf("\nResult (part 1): %d\n", sum);
    free(times);
    free(distances);
    // part 2
    int size = 0;
    fileText = startPos;
    // get newTimes and finalTime
    newTimes = getLineNums(&fileText, 2);
    for (int i = 0; *(newTimes + i) != -1; size++, i++);
    finalTime = concatArray(newTimes, size);
    // get newDistances and finalDistance
    size = 0;
    newDistances = getLineNums(&fileText, 2);
    for (int i = 0; *(newDistances + i) != -1; size++, i++);
    finalDistance = concatArray(newDistances, size);
    printf("Final Time: %ld\n", finalTime);
    printf("Final Distance: %ld\n", finalDistance);
    printf("True result (part 2): %ld", getWinningPlays(finalTime, finalDistance));
    return 0;
}
