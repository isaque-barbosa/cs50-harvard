#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int PERIOD = 46, EXCLAMATION_MARK = 33, QUESTION_MARK = 63, SPACE = 32;

int letters_per_word(int letters, int words);
int sentences_per_word(int sentences, int words);

int main(void)
{
    string text = get_string("Text: ");

    int sentences = 0, letters = 0, words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];
        if (current == PERIOD || current == EXCLAMATION_MARK || current == QUESTION_MARK)
        {
            sentences++;
        }
        else if (current == SPACE)
        {
            words++;
        }
        else
        {
            letters++;
        }
    }
    int l = letters / (words / 100.0);
    int s = sentences / (words / 100.0);
    int grade = (0.0588 * letters_per_word(letters, words)) -
                (0.296 * sentences_per_word(sentences, words)) - 15.8;

    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (grade >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", grade);
}

int letters_per_word(int letters, int words)
{
    return letters / (words / 100.0) + 0.5;
}

int sentences_per_word(int sentences, int words)
{
    return sentences / (words / 100.0) + 0.5;
}
