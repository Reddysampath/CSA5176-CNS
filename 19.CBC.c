#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 24
#define BLOCK_SIZE 8

void xor_blocks(unsigned char *block1, unsigned char *block2, unsigned char *output, int size) {
    int i;
	for ( i = 0; i < size; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

void mock_encrypt_block(unsigned char *input, unsigned char *key, unsigned char *output) {
    int i;
	for ( i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i % KEY_LENGTH];
    }
}

void mock_decrypt_block(unsigned char *input, unsigned char *key, unsigned char *output) {
    int i;
	for ( i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i % KEY_LENGTH];
    }
}

void cbc_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, 
                 unsigned char *iv, unsigned char *ciphertext) {
    unsigned char block[BLOCK_SIZE], encrypted_block[BLOCK_SIZE];
    memcpy(block, iv, BLOCK_SIZE);
    int i;
    for ( i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        xor_blocks(plaintext + i, block, block, BLOCK_SIZE);
        mock_encrypt_block(block, key, encrypted_block);
        memcpy(ciphertext + i, encrypted_block, BLOCK_SIZE);
        memcpy(block, encrypted_block, BLOCK_SIZE);
    }
}

void cbc_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, 
                 unsigned char *iv, unsigned char *plaintext) {
    unsigned char block[BLOCK_SIZE], decrypted_block[BLOCK_SIZE], prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    int i;
    for ( i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        mock_decrypt_block(ciphertext + i, key, decrypted_block);
        xor_blocks(decrypted_block, prev_block, plaintext + i, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    unsigned char key[KEY_LENGTH] = "123456789012345678901234";
    unsigned char iv[BLOCK_SIZE] = "12345678";
    unsigned char plaintext[] = "This is a secret message!";
    int plaintext_len = strlen((char *)plaintext);
    int padded_len = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;
    unsigned char *padded_plaintext = calloc(padded_len, sizeof(unsigned char));
    memcpy(padded_plaintext, plaintext, plaintext_len);
    unsigned char *ciphertext = malloc(padded_len);
    unsigned char *decryptedtext = malloc(padded_len);
    cbc_encrypt(padded_plaintext, padded_len, key, iv, ciphertext);
    printf("Ciphertext: ");
    int i;
	for ( i = 0; i < padded_len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");
    cbc_decrypt(ciphertext, padded_len, key, iv, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    free(padded_plaintext);
    free(ciphertext);
    free(decryptedtext);
    return 0;
}

