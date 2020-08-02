#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int pyramidSize = 0;

    do {
        pyramidSize = get_int("Height of the Pyramid: ");
    } while (pyramidSize < 1 || pyramidSize > 9);

    int lineChars = pyramidSize * 2 + 2;

    for (int i = 1; i <= pyramidSize; i++) {
        int lineEspaces = pyramidSize - i;

        for (int j = 1; j <= lineEspaces; j ++) {
            printf(" ");
        }

        for (int k = 1; k <= i; k ++) {
            printf("#");
        }

        printf("  ");

        for (int k = 1; k <= i; k ++) {
            if (k == pyramidSize) {
                printf("#\n");
            } else {
                printf("#");
            }
        }

        for (int j = 1; j <= lineEspaces; j ++) {
            if (j == lineEspaces) {
                printf(" \n");
            } else {
                printf(" ");
            }
        }
    }
}