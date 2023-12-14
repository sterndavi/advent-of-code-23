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

int getSize(char *text){
    char *ptr = text;
    int count = 0;
    while (*ptr) if (*ptr++ == '\n') count++;
    return count;
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

int getMaxArray(int *arr){
    int max = 0;
    for (int i =0; *(arr + i) != 0; i++) max = (*(arr + i) > max) ? *(arr + i) : max;
    return max;
}

void sortArray(int *arr){ // the simplest of all
                          // very inefficient, but it works for this small input (< 10000)
    int temp;
    for (int i = 0; *(arr + i) != 0; i++) 
        for (int j = i + 1; *(arr + j) != 0; j++) 
            if (*(arr + j) < *(arr + i)){ // if the next is lower than the current
                temp = *(arr + i); // get the current value
                *(arr + i) = *(arr + j); // change the current value to the lower value
                *(arr + j) = temp; // set the next value to the current value
            }
}
