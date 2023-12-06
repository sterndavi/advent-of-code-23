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

int myPow(int base, int power){
    int sum = 1;
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

int concatArray(int arr[], int count){
    int *ptr = arr, sum = 0;
    for (int i = 0; i < count; i++){
        sum += *(ptr + i) * myPow(10, (count - 1 - i));
    }
    return sum;
}

int createNumber(char **pos){
    int *arr = (int *)malloc(sizeof(int)*2), *item = arr, size = 0;
    while (charIsNumber(**pos)) *item++ = (int) *(*pos)++ - '0', size++;
    return concatArray(arr, size);
}

int *getWinningNumbers(char **line){
    int size = 0;
    char *pos = *line;
    while (*pos++ != '|') if (*pos == ' ') size++; // get the amount of numbers by the amount of spaces after the game number
                                                   // this doesn't account for numbers that have only one digit, therefore leaking memory
                                                   // just writing it down
    int *winning = (int *)calloc(size, sizeof(int)*size), *ptrWinning = winning; 
    while (*(*line)++ != '|'){
        if (charIsNumber(**line)) *ptrWinning++ = createNumber(line);
    }
    return winning;
}

int *getPlayingNumbers(char **line){
    int size = 0;
    char *pos = *line;
    while (*pos++ != '\n') if (*pos == ' ') size++; // get the amount of numbers by the amount of spaces after the game number
                                                         // this doesn't account for numbers that have only one digit, therefore leaking memory
                                                         // just writing it down
    int *playing = (int *)calloc(size, sizeof(int)*size), *ptrPlaying = playing; 
    while (*(*line)++ != '\n'){
        if (charIsNumber(**line)) *ptrPlaying++ = createNumber(line);
    }
    return playing;
}

int getCardPoints(int *winning, int *playing){
    int *ptrWin = winning, *ptrPlay = playing;
    int sum = 0;
    while (*ptrWin){
        while (*ptrPlay) if (*ptrPlay++ == *ptrWin) sum = (!sum) ? 1 : sum * 2; // since there'll always be some extra memory, I can go until *ptrPlay == 0
                                                                                // not a good guarantee, but let's see if it works
        ptrWin++;
        ptrPlay = playing; // return to the start of the playing numbers
    }
    return sum;
}

int getWinCount(int *winning, int *playing){
    int *ptrWin = winning, *ptrPlay = playing;
    int count = 0;
    while (*ptrWin){
        while (*ptrPlay) if (*ptrPlay++ == *ptrWin) count++; // since there'll always be some extra memory, I can go until *ptrPlay == 0
                                                             // not a good guarantee, but let's see if it works
        ptrWin++;
        ptrPlay = playing; // return to the start of the playing numbers
    }
    return count;
}

int main(int argc, char *argv[]){
    char *fileText;
    int *winningNumbers, *playingNumbers;
    int sum = 0, cardPoints, nLine = 1;
    if (argv[1]){
        fileText = readFile(argv[1]);
    }
    else{
        printf("Por favor, informe um arquivo corretamente.");
        return 1;
    }
    while (*fileText){
        while (!charIsNumber(*fileText++)); // go to the next number
        fileText++; // skip this number
        printf("Card %d: ", nLine++);
        winningNumbers = getWinningNumbers(&fileText); // seek fileText to the playing numbers
        playingNumbers = getPlayingNumbers(&fileText); // seek fileText to the '\n' char and add the pointer to the next line
        cardPoints = getCardPoints(winningNumbers, playingNumbers);
        printf("%d points!\n", cardPoints);
        sum += cardPoints;
    }
    printf("Final points: %d", sum);
    return 0;
}
