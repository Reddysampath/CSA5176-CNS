#include <stdio.h>
int main() 
{
    char text[100];
    int key,i;
    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter key: ");
    scanf("%d", &key);
    for ( i = 0; text[i] != '\0'; i++) 
	{
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')) 
		{
            char base = (text[i] >= 'A' && text[i] <= 'Z') ? 'A' : 'a';
            text[i] = (text[i] - base + key) % 26 + base;
        }
    }
    printf("Encrypted text: %s", text);
}
