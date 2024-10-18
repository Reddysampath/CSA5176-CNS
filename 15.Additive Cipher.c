#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void decrypt(char *ciphertext, int shift) {
    int length = strlen(ciphertext),i;
    for (i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                ciphertext[i] = 'A' + (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            } else {
                ciphertext[i] = 'a' + (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            }
        }
    }
}

void countLetterFrequency(char *text, int *frequency) {
    int length = strlen(text),i;
    for ( i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i])) {
                frequency[text[i] - 'A']++;
            } else {
                frequency[text[i] - 'a']++;
            }
        }
    }
}

int findShiftValue(int *frequency) {
    int maxFrequency = 0;
    int mostFrequentIndex = 0,i;
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            mostFrequentIndex = i;
        }
    }
    int shift = (mostFrequentIndex - ('E' - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE;
    return shift;
}

int main() {
    char ciphertext[1000], temp[1000];
    int letterFrequency[ALPHABET_SIZE] = {0};
    int shift,i;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    countLetterFrequency(ciphertext, letterFrequency);
    shift = findShiftValue(letterFrequency);

    printf("Possible plaintexts in order of likelihood:\n");
    for ( i = 0; i < 10; i++) {
        strcpy(temp, ciphertext);
        decrypt(temp, (shift + i) % ALPHABET_SIZE);
        printf("%d. %s\n", i + 1, temp);
    }

    return 0;
}

