#include <stdio.h>
#include <string.h>

void encrypt(const char *plaintext, const int *key, char *ciphertext) {
    int plaintextLen = strlen(plaintext),i;
    for ( i = 0; i < plaintextLen; i++) {
        ciphertext[i] = (plaintext[i] - 'A' + key[i]) % 26 + 'A';
    }
    ciphertext[plaintextLen] = '\0';
}
void decrypt(const char *ciphertext, const int *key, char *plaintext) {
    int ciphertextLen = strlen(ciphertext),i;
    for (i = 0; i < ciphertextLen; i++) {
        plaintext[i] = (ciphertext[i] - 'A' - key[i] + 26) % 26 + 'A';
    }
    plaintext[ciphertextLen] = '\0';
}

int main() {
    char plaintext[100];
    int key[100];
    int textLen,i;

    printf("Enter the plaintext (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    textLen = strlen(plaintext);

    printf("Enter the key values separated by spaces (same length as plaintext): ");
    for ( i = 0; i < textLen; i++) {
        scanf("%d", &key[i]);
    }

    char ciphertext[100];
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    char decryptedText[100];
    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

