#include "utils.c"

#define HAND_SIZE 6 // one more than 5 so we can count the null terminator

enum Types { // ordered from lowest to highest type
    HIGHEST,
    ONE,
    TWO,
    THREE,
    HOUSE,
    FOUR,
    FIVE
};

enum Cards {
    T=10,
    J,
    Q,
    K,
    A
};

typedef struct Play{
    char hand[HAND_SIZE];
    int bet;
    enum Types type;
} play;

int getVal(char card){
    switch (card){
        case 'T': return T;
        case 'J': return J;
        case 'Q': return Q;
        case 'K': return K;
        case 'A': return A;
    }
    // if not any of those, go for the char to int
    int intChar = (int) card - '0';
    if (0 <= intChar && intChar <= 9) return intChar;
    return -1; // if nothing else, return an error
}

int getCardRepeats(char card, char hand[]){
    int repeats = 0;
    char *ptrHand = hand;
    for (int i = 0; *(hand + i) != '\0'; i++) if (*ptrHand++ == card) repeats++; 
    return repeats;
}

int comparePlay(play play1, play play2){
    char *hand1 = play1.hand;
    char *hand2 = play2.hand;
    for (int i = 0; *(hand1 + i) != '\0' && *(hand2 + i) != '\0'; i++){
        int val1 = getVal(*(hand1 + i)), val2 = getVal(*(hand2 + i));
        if ((!val1 || val1 == -1) || (!val2 || val2 == -1)) return -1; // one of the values got wrongfully read
        if (val1 > val2 || play1.type > play2.type) return 1;
        if (val2 > val1 || play2.type > play1.type) return 2;
    }
    return 0; // they're the same card
}

int *setRanks(play *playList, int size){
    int *ranks = (int *)calloc(sizeof(int),sizeof(int)*(size + 1)), *ptrRanks = ranks;
    int result;
    for (int i = 0; i < size; i++){
        for (int j = i + 1; j < size; j++){
            switch ((result = comparePlay(*(playList + i), *(playList + j)))){
                case 1: // play 1 is higher
                    *(ptrRanks + i) += 1;
                case 2: // play 2 is higher
                    *(ptrRanks + i) -= 1;
//              case 0:
//              case -1: // something gone wrong; why am I entering this case every time?
//                  printf("Error %d.\n", result);
            }
        }
    }
    return ranks;
}

void sortHands(play *listHands){
    play temp;
    for (int i = 0; (listHands+i)->type; i++)
        for (int j = i + 1; (listHands + j)->type; j++)
            if ((listHands+j)->type < (listHands + i)->type){
                temp = *(listHands+i);
                *(listHands + i) = *(listHands + j);
                *(listHands + j) = temp;
            }
}

int getHandType(char hand[HAND_SIZE]){
    char *ptrHand = hand;
    short house = 0, one = 0, triple = 0;
    int *freqRepeat = (int *)malloc(sizeof(int)*HAND_SIZE), *ptrFreq = freqRepeat;
    int nPairs = 0;
    // getting the frequency of repeats
    for (int i = 0; *(ptrHand + i) != '\0'; i++){
        *(freqRepeat + i) = getCardRepeats(*(ptrHand + i), hand);
    }
    int maxRepeat = getMaxArray(freqRepeat);
    while (*ptrFreq){
        if (*ptrFreq == maxRepeat) nPairs++;
        if (*ptrFreq == 1) one = 1;
        if (*ptrFreq == 2) house = 1;
        ptrFreq++;
    }
    free(freqRepeat); // freeing to not create another memory leak
    switch (nPairs){
        case 5:
            return FIVE;
        case 4:
            if (one) return TWO;
            return FOUR;
        case 3:
            if (house) return HOUSE;
            return THREE;
        case 2:
        case 1:
            if (one) return ONE;
            return HIGHEST;
        default:
            return -1;
    }
    return -1; // error handling
}

int main(int argc, char *argv[]){
    char *fileText;
    int nLines, count = 0;
    if (argv[1]){
        fileText = readFile(argv[1]);
    }
    else{
        printf("Por favor, informe um arquivo corretamente.");
        return 1;
    }
    nLines = getSize(fileText);
    play *plays = (play *)malloc(sizeof(play)*nLines), *ptrPlays = plays;
    while (*fileText != '\0'){
        while (*fileText != ' '){
            if (*fileText == '\0') break;
            ptrPlays->hand[count++] = *fileText++;
        }
        ptrPlays->hand[count] = '\0';
        while (charIsNumber(*fileText++)); // go to the next number
        ptrPlays->bet = createNumber(&fileText);
        ptrPlays->type = getHandType(ptrPlays->hand);
        ptrPlays++, fileText++, count = 0;
    }
    sortHands(plays);
    printf("Plays:\n");
    for (int i = 0; i < nLines; i++){
        printf("Hand: %s, Bet: %d, ", (plays+i)->hand, (plays+i)->bet);
        if ((plays+i)->type == -1) printf("Error on type. %d", (plays+i)->type);
        else printf("Type: %d\n", (plays+i)->type);
    }
    free(plays); // cleanup
    return 0;
}
