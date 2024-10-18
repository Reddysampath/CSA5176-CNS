#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define NUM_TOP_PLAINTEXTS 10
const double englishLetterFreq[ALPHABET_SIZE] = 
{ 
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609,
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193,
    0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015,
    0.0197, 0.0007
};
void calculateLetterFrequency(const char *text, double *freq);
double calculateScore(const double *freq);
void decryptSubstitution(const char *ciphertext, char *plaintext, int shift);

int main() {
    const char *ciphertext = "FALSXY XS LSX!";  
    double ciphertextFreq[ALPHABET_SIZE] = {0.0};
    double scores[NUM_TOP_PLAINTEXTS] = {0.0};
    char possiblePlaintexts[NUM_TOP_PLAINTEXTS][100]; 
    int shift, i;
    calculateLetterFrequency(ciphertext, ciphertextFreq);
    printf("Ciphertext: %s\n\n", ciphertext);
    printf("Top %d possible plaintexts:\n", NUM_TOP_PLAINTEXTS);

    for (shift = 0; shift < ALPHABET_SIZE; shift++) {
        char possiblePlaintext[100];  
        decryptSubstitution(ciphertext, possiblePlaintext, shift);
        double possiblePlaintextFreq[ALPHABET_SIZE] = {0.0};
        calculateLetterFrequency(possiblePlaintext, possiblePlaintextFreq);
        double score = calculateScore(possiblePlaintextFreq);

        if (score > scores[NUM_TOP_PLAINTEXTS - 1]) {
            scores[NUM_TOP_PLAINTEXTS - 1] = score;
            strcpy(possiblePlaintexts[NUM_TOP_PLAINTEXTS - 1], possiblePlaintext);
            for (i = NUM_TOP_PLAINTEXTS - 1; i > 0 && scores[i] > scores[i - 1]; i--) {
                double tempScore = scores[i];
                scores[i] = scores[i - 1];
                scores[i - 1] = tempScore;
                char tempText[100];
                strcpy(tempText, possiblePlaintexts[i]);
                strcpy(possiblePlaintexts[i], possiblePlaintexts[i - 1]);
                strcpy(possiblePlaintexts[i - 1], tempText);
            }
        }
    }
    for (i = 0; i < NUM_TOP_PLAINTEXTS; i++) {
        printf("Shift %d: %s (Score: %.4f)\n", i, possiblePlaintexts[i], scores[i]);
    }

    return 0;
}
void calculateLetterFrequency(const char *text, double *freq) {
    int totalLetters = 0, i;

    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            freq[tolower(text[i]) - 'a']++;
            totalLetters++;
        }
    }
    for (i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] /= totalLetters;  
    }
}
double calculateScore(const double *freq) {
    double score = 0.0;
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        score += freq[i] * englishLetterFreq[i];
    }
    return score;
}
void decryptSubstitution(const char *ciphertext, char *plaintext, int shift) {
    int i;
    for (i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[i] = '\0';
}

