#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string text = get_string("Text: ");

    double letters = 0;
    double words = 0;
    double senteces = 0;
    int textSize = strlen(text);

    for (int i = 0; i < textSize; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        else if (text[i] == ' ' && isalpha(text[i - 1]))
        {
            words += 1;
        }
        else if ((text[i] == '!' && isalpha(text[i - 1])) || (text[i] == '?' && isalpha(text[i - 1])) ||
                 (text[i] == '.' && isalpha(text[i - 1])))
        {
            senteces += 1;
            words += 1;
        }
        else if (text[i] != ' ' && isalpha(text[i - 1]) && !isalpha(text[i + 1])) // commas and end quotes for instace
        {
            words += 1;
        }
    }

    if (isalpha(text[textSize - 1]))
    {
        words += 1;
    }

    double L = (letters / words) * 100.00;
    double S = (senteces / words) * 100.00;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index > 15)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    printf("Grade %i\n", index);
    return 0;


}