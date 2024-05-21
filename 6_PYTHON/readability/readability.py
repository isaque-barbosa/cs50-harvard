from cs50 import get_string
import re


def main():
    text = get_string("Text: ")
    letters = len(re.findall(r'[a-zA-Z]', text))
    sentences = text.count('.') + text.count('!') + text.count('?')
    words = len(text.split())
    letters_per_100_words = letters / (words / 100.0)
    sentences_per_100_words = sentences / (words / 100.0)
    grade = round((0.0588 * letters_per_100_words) - (0.296 * sentences_per_100_words) - 15.8)

    if grade < 1:
        print("Before Grade 1")
        return
    if grade >= 16:
        print("Grade 16+")
        return
    print(f"Grade {grade}")


main()
