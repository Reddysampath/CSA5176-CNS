#include <stdio.h>
#include <string.h>
#include <ctype.h>
void substitutionDecrypt(char *ciphertext, char *key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isdigit(ciphertext[i])) {
            ciphertext[i] = key[ciphertext[i] - '0'];
        }
    }
}
int main() {
    char ciphertext[] = "53111305))6:4826)41.)41):806"; 
    char key[10] = "abcdefghij";  

    printf("Ciphertext: %s\n", ciphertext);
    substitutionDecrypt(ciphertext, key);
    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}

