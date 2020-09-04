import re


def defineReadability():
    phrase = input("Text: ")

    # should remove -1 there because split returns an array
    # with one extra value if split pattern is the last char
    words = len(re.split(" ", phrase.lower()))
    letters = len(re.split("\w\W*", phrase.lower())) - 1
    sentences = len(re.split("\.|\?|\!", phrase.lower())) - 1


    L = (letters * 100.00) / words
    S = (sentences * 100.00) / words

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if (index > 0 and index < 16):
        print(f"Grade {index}")
        return True;
    elif (index < 1):
        print(f"Before Grade 1")
        return True;
    else:
        print(f"Grade 16+")
        return True;


defineReadability()
