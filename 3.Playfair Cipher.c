#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5

void prepareKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int i, j, k = 0, used[26] = {0};
    char temp[26];

    i = 0;  
    while (key[i] != '\0') {
        key[i] = toupper(key[i]);
        if (key[i] == 'J') key[i] = 'I';
        if (!used[key[i] - 'A']) {
            temp[k++] = key[i];
            used[key[i] - 'A'] = 1;
        }
        i++;
    }

    i = 0;
    while (i < 26) {
        if (i != ('J' - 'A') && !used[i]) temp[k++] = 'A' + i;
        i++;
    }

    k = 0;
    i = 0;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            keyTable[i][j] = temp[k++];
            j++;
        }
        i++;
    }
}

void printKeyTable(char keyTable[SIZE][SIZE]) {
    int i = 0, j;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            printf("%c ", keyTable[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void findPosition(char keyTable[SIZE][SIZE], char letter, int *row, int *col) {
    if (letter == 'J') letter = 'I';
    int i = 0, j;
    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            if (keyTable[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
            j++;
        }
        i++;
    }
}

void encryptPair(char keyTable[SIZE][SIZE], char a, char b, char *enc1, char *enc2) {
    int row1, col1, row2, col2;
    findPosition(keyTable, a, &row1, &col1);
    findPosition(keyTable, b, &row2, &col2);

    if (row1 == row2) {
        *enc1 = keyTable[row1][(col1 + 1) % SIZE];
        *enc2 = keyTable[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        *enc1 = keyTable[(row1 + 1) % SIZE][col1];
        *enc2 = keyTable[(row2 + 1) % SIZE][col2];
    } else {
        *enc1 = keyTable[row1][col2];
        *enc2 = keyTable[row2][col1];
    }
}

void preparePlaintext(char plaintext[], char prepared[]) {
    int len = strlen(plaintext), k = 0, i = 0;
    while (i < len) {
        prepared[k++] = toupper(plaintext[i]);
        if (i < len - 1 && plaintext[i] == plaintext[i + 1]) prepared[k++] = 'X';
        i++;
    }
    if (k % 2 != 0) prepared[k++] = 'X';
    prepared[k] = '\0';
}

void encrypt(char keyTable[SIZE][SIZE], char plaintext[]) {
    char prepared[100], ciphertext[100];
    int i = 0, k = 0;
    preparePlaintext(plaintext, prepared);
    printf("\nPrepared Plaintext: %s\n", prepared);
    while (i < strlen(prepared)) {
        char enc1, enc2;
        encryptPair(keyTable, prepared[i], prepared[i + 1], &enc1, &enc2);
        ciphertext[k++] = enc1;
        ciphertext[k++] = enc2;
        i += 2;
    }
    ciphertext[k] = '\0';
    printf("Encrypted Text: %s\n", ciphertext);
}

int main() {
    char key[50], plaintext[50], keyTable[SIZE][SIZE];
    printf("Enter the key: ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    prepareKeyTable(key, keyTable);
    printKeyTable(keyTable);
    encrypt(keyTable, plaintext);
    return 0;
}

