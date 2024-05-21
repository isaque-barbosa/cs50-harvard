#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int A_UPPER_ASCII = 64, Z_UPPER_ASCII = 90, A_LOWER_ASCII = 96, Z_LOWER_ASCII = 122,
          ZERO_ASCII = 48;

void cipher_text(int key, string text);
int get_valid_key_from_string(string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = get_valid_key_from_string(argv[1]);
    if (key == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    cipher_text(key, text);

    printf("ciphertext: %s\n", text);
}

// a valid key is only numbers
int get_valid_key_from_string(string text)
{
    int key = 0, base = 1;
    for (int i = strlen(text) - 1; i >= 0; i--)
    {
        int current = text[i] - ZERO_ASCII;
        if (current >= 0 && current < 10)
        {
            current *= base;
            key += current;
            base *= 10;
        }
        else
        {
            return 0;
        }
    }
    return key;
}

int get_valid_alphabet_ascii(int code, int aLetter, int zLetter)
{
    while (code > zLetter)
    {
        code -= zLetter;
        code = aLetter + code;
    }
    return code;
}

void cipher_text(int key, string text)
{
    int encrypt;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int current = text[i];
        encrypt = current + key;
        if (current >= A_UPPER_ASCII && current <= Z_UPPER_ASCII)
        {
            text[i] = get_valid_alphabet_ascii(encrypt, A_UPPER_ASCII, Z_UPPER_ASCII);
        }
        else if (current >= A_LOWER_ASCII && current <= Z_LOWER_ASCII)
        {
            text[i] = get_valid_alphabet_ascii(encrypt, A_LOWER_ASCII, Z_LOWER_ASCII);
        }
    }
}
