#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int A_UPPER_ASCII = 64, A_LOWER_ASCII = 96, SUM_ALPHABETIC = 351;
const int ERR = 1, OK = 0;

int is_valid_key(int size, string text);
void cipher_text(string key, string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("The key must contain 26 distinct characters.\n");
        return ERR;
    }
    int size = strlen(argv[1]);
    if (size != 26 || is_valid_key(size, argv[1]) == ERR)
    {
        printf("The key must contain 26 distinct characters.\n");
        return ERR;
    }

    string text = get_string("plaintext: ");

    cipher_text(argv[1], text);

    printf("ciphertext: %s\n", text);
}

// a valid key is a 26 string with the letters of the alphabet
int is_valid_key(int size, string text)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        int current = text[i];
        if (!islower(current) && !isupper(current))
        {
            return ERR;
        }
        else
        {
            sum += tolower(current) - A_LOWER_ASCII;
        }
    }
    if (sum != SUM_ALPHABETIC)
    {
        return ERR;
    }
    return OK;
}

void cipher_text(string key, string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int current = text[i] - 1;
        if (islower(text[i]))
        {
            text[i] = tolower(key[current - A_LOWER_ASCII]);
        }
        else if (isupper(text[i]))
        {
            text[i] = toupper(key[current - A_UPPER_ASCII]);
        }
    }
}
