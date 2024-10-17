#include <stdio.h>
int modInverse(int a, int m) {
	int x;
    for ( x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

void affineDecrypt(char* ciphertext, int a, int b) {
    int inv_a = modInverse(a, 26),i;
    if (inv_a == -1) {
        printf("Decryption not possible. No modular inverse for 'a'.\n");
        return;
    }

    for ( i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int C = ciphertext[i] - 'A';
            int P = (inv_a * (C - b + 26)) % 26; 
            ciphertext[i] = P + 'A';
        }
    }
}

int main() {
    char ciphertext[] = "BUUUUU";  
    int a = 5, b = 8;  

    printf("Ciphertext: %s\n", ciphertext);
    affineDecrypt(ciphertext, a, b);
    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}
