#include <stdio.h>
#include <string.h>

void railFenceEncrypt(const char *msg, int rails, char *encrypted) {
    int len = strlen(msg), k = 0, row = 0, direction = 1,i,j;
    char matrix[rails][len];
    memset(matrix, 0, sizeof(matrix));
    
    for ( i = 0; i < len; i++) {
        matrix[row][i] = msg[i];
        row += direction;
        if (row == 0 || row == rails - 1) direction *= -1;
    }

    for (i = 0; i < rails; i++)
        for (j = 0; j < len; j++)
            if (matrix[i][j] != 0) encrypted[k++] = matrix[i][j];

    encrypted[k] = '\0';
}

void railFenceDecrypt(const char *encrypted, int rails, char *decrypted) {
    int len = strlen(encrypted), k = 0, row = 0, direction = 1,i,j;
    char matrix[rails][len];
    memset(matrix, 0, sizeof(matrix));

    for ( i = 0; i < len; i++) {
        matrix[row][i] = '*';
        row += direction;
        if (row == 0 || row == rails - 1) direction *= -1;
    }

    for (i = 0; i < rails; i++)
        for (j = 0; j < len; j++)
            if (matrix[i][j] == '*') matrix[i][j] = encrypted[k++];

    row = 0, direction = 1;
    for ( i = 0; i < len; i++) {
        decrypted[i] = matrix[row][i];
        row += direction;
        if (row == 0 || row == rails - 1) direction *= -1;
    }

    decrypted[len] = '\0';
}

int main() {
    char message[] = "HELLOWORLD", encrypted[100], decrypted[100];
    int rails = 3;

    printf("Original Message: %s\n", message);
    railFenceEncrypt(message, rails, encrypted);
    printf("Encrypted Message: %s\n", encrypted);
    railFenceDecrypt(encrypted, rails, decrypted);
    printf("Decrypted Message: %s\n", decrypted);

    return 0;
}

