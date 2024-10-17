#include <stdio.h>
#include <string.h>
#define SIZE 5

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char matrix[SIZE][SIZE], char ch1, char ch2) {
    int row1, col1, row2, col2, temp;

    findPosition(matrix, ch1, &row1, &col1);
    findPosition(matrix, ch2, &row2, &col2);

    if (row1 == row2) {
        col1 = (col1 + 1) % SIZE;
        col2 = (col2 + 1) % SIZE;
    } else if (col1 == col2) {
        row1 = (row1 + 1) % SIZE;
        row2 = (row2 + 1) % SIZE;
    } else {
        temp = col1;
        col1 = col2;
        col2 = temp;
    }

    printf("%c%c", matrix[row1][col1], matrix[row2][col2]);
}

void playfairEncrypt(char matrix[SIZE][SIZE], char text[]) {
    int len = strlen(text);
    int i;
    char ch1, ch2;

    for (i = 0; i < len; i += 2) {
        ch1 = text[i];
        ch2 = (i + 1 < len) ? text[i + 1] : 'X';

        if (ch1 == ch2) {
            ch2 = 'X';
            i--;
        }

        encryptPair(matrix, ch1, ch2);
    }
    printf("\n");
}

int main() {
    char playfairMatrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char plaintext[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE.";

    printf("Original message: %s\n", plaintext);
    printf("Encrypted text: ");
    playfairEncrypt(playfairMatrix, plaintext);

    return 0;
}

