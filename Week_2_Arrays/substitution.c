#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool checkArgs(int n);

int main(int argc, string argv[])
{
    if (checkArgs(argc))
    {
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Error. Please pass in a key of 26 alpha-characters.\n");
        return 1;
    }

    char keyCheck[26];

    for (int i = 0; i < 26; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Error. Please pass in a key of 26 unique alpha-characters.\n");
            return 1;
        }

        int letter = toupper(argv[1][i]) - 65;

        if (keyCheck[letter] == 1)
        {
            printf("Error. Please pass in a key of 26 unique alpha-characters.\n");
            return 1;
        }
        else
        {
            keyCheck[letter] = 1;
        }
    }

    string beforeEncryption = get_string("plaintext: ");

    int textLength = strlen(beforeEncryption);

    char encryptedText[textLength];

    for (int j = 0; j < textLength; j++)
    {
        if (beforeEncryption[j] > 64 && beforeEncryption[j] < 91)
        {
            int charNumber = beforeEncryption[j] - 65;

            encryptedText[j] = toupper(argv[1][charNumber]);
        }
        else if (beforeEncryption[j] > 96 && beforeEncryption[j] < 123)
        {
            int charNumber = beforeEncryption[j] - 97;

            encryptedText[j] = tolower(argv[1][charNumber]);
        }
        else
        {
            encryptedText[j] = beforeEncryption[j];
        }
    }

    if (textLength == 1)
    {
        printf("ciphertext: %c\n", encryptedText[0]);
        return 0;
    }

    printf("ciphertext: ");

    for (int k = 0; k < textLength; k++)
    {
        if (k != textLength - 1)
        {
            printf("%c", encryptedText[k]);
        }
        else
        {
            printf("%c\n", encryptedText[k]);
        }
    }
}

bool checkArgs(int n)
{
    if (n != 2)
    {
        printf("Error. Please pass only a key as an argument\n");
        return true;
    }

    return false;
}