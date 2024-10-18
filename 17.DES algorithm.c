#include <stdio.h>
#include <stdint.h>
static const int IP[64] = {  2, 6, 3, 1, 4, 8, 5, 7 };
static const int IP_INV[64] = { 4, 1, 3, 5, 7, 2, 8, 6 };

static const int SHIFTS[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
uint64_t permute(uint64_t input, const int *table, int size) {
    uint64_t result = 0;
    int i;
    for ( i = 0; i < size; i++) {
        result |= ((input >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return result;
}
void generate_subkeys(uint64_t key, uint64_t *subkeys) {
}
uint32_t feistel(uint32_t half, uint64_t subkey) {
    return half ^ (subkey & 0xFFFFFFFF); 
}
uint64_t des_decrypt(uint64_t ciphertext, uint64_t *subkeys) {
    uint64_t permuted = permute(ciphertext, IP, 64);
    uint32_t left = permuted >> 32;
    uint32_t right = permuted & 0xFFFFFFFF;
    int i;
    for (i = 15; i >= 0; i--) {
        uint32_t temp = right;
        right = left ^ feistel(right, subkeys[i]);
        left = temp;
    }
    uint64_t combined = ((uint64_t)right << 32) | left;
    return permute(combined, IP_INV, 64);
}
int main() {
    uint64_t subkeys[16];
    generate_subkeys(0x133457799BBCDFF1, subkeys); 

    uint64_t decrypted = des_decrypt(0x0123456789ABCDEF, subkeys); 

    printf("Decrypted text: 0x%016llX\n", decrypted);

    return 0;
}

