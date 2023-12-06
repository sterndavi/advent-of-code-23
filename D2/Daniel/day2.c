#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

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
    if (power < 0) return sum; // edge case for negatives
    while (power){
        sum *= base;
        power--;
    }
    return sum;
}

int concatArray(int *arr){
    // get arr length
    int *ptrArr = arr, size = 1, sum = 0;
    do {
        sum += *ptrArr * (myPow(10, size));
        size--, ptrArr++;
    } while (*ptrArr);
    return sum;
}

int strToInt(char *str){
    char *ptr = str;
    int conv = *ptr++ - '0', sum = 0;
    int *arr = (int *)calloc(2, sizeof(int)*2); // i'll add every value to an array, then sum it up by their position
    int *ptrArr = arr;
    do {
        *ptrArr = (0 <= conv && conv <= 9) ? conv : 0; 
        conv = *ptr++ - '0';
        ptrArr++;
    } // do it at least once, so we can skip the possible space
    while (0 <= conv && conv <= 9);
    return concatArray(arr);
}

int colorPerLine(char *line, char *color){
    char *pos = line, *sep = line;
    while (*sep != '\n') sep++; // get to the end of that line, so we can check per-game basis
    int count = 0, max = 0;
    while ((pos = strstr(pos, color)) != NULL && pos < sep){
        // get pos to the possible two-digit-number; kinda hacky, but it works; it will always be three digits to the left
        count = strToInt(pos - 3);
        if (count > max) max = count;
        pos = strchr(pos++, ';');
        if (pos == NULL) break;
    }
    return max;
}

// int redsPerLine(char *line){
//     char *pos = line, *sep = line;
//     while (*sep != '\n') sep++; // get to the end of that line, so we can check per-game basis
//     int count = 0, max = 0;
//     while ((pos = strstr(pos, "red")) != NULL && pos < sep){
//         // get pos to the possible two-digit-number; kinda hacky, but it works; it will always be three digits to the left
//         count = strToInt(pos - 3);
//         if (count > max) max = count;
//         pos = strchr(pos++, ';');
//         if (pos == NULL) break;
//     }
//     return max;
// }

// int greensperLine(char *line);
// int bluesPerLine(char *line);

int isGamePossible(int reds, int greens, int blues){
    return reds <= MAX_RED && greens <= MAX_GREEN && blues <= MAX_BLUE;
}

int main(int argc, char *argv[]){
    char *text;
    if (argv[1]){
        printf("Usando o arquivo suprido, %s.", argv[1]);
        text = readFile(argv[1]);
    }
    else {
        printf("Utilizando o arquivo padrão, 'day2.txt'.");
        text = readFile("day2.txt");
    }
    int count = 0, possible = 0, finalPower = 0, power;
    while (*text){
        int reds, blues, greens;
        reds = colorPerLine(text, "red");
        blues = colorPerLine(text, "blue");
        greens = colorPerLine(text, "green");
        power = reds*greens*blues;
        finalPower += power;
        printf("Line %d: %d reds, %d blues, %d greens. Is viable? %d! Power: %d\n", (count++) + 1, reds, greens, blues, isGamePossible(reds, greens, blues), power);
        if (isGamePossible(reds, greens, blues)) possible += count;
        text = strchr(text, '\n');
        text++;
    }
    printf("Final count: %d\n", possible);
    printf("Final power: %d\n", finalPower);
    return 0;
}
