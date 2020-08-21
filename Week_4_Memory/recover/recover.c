#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Warning: only pass in the file you are trying to recover.\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    int jpgCount = 0;

    // will hold name of the file
    char filename[8];

    BYTE block[512];

    // creates a pointer to file
    FILE *img;

    // this has to be here because the do/while i was doing generates errors on last img.
    while (fread(&block, sizeof(block), 1, inptr) == 1)
    {
        // checks first 3 bytes
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && ((block[3] & 0xf0) == 0xe0))
        {
            if (jpgCount == 0)
            {
                // initialize 000.img
                sprintf(filename, "%03i.jpg", jpgCount);
                jpgCount += 1;

                // open and write to file on previous created pointer
                img = fopen(filename, "w");
                fwrite(block, sizeof(block), 1, img);
            }
            else
            {
                // close file
                fclose(img);

                // increment
                sprintf(filename, "%03i.jpg", jpgCount);
                jpgCount += 1;

                // open file
                img = fopen(filename, "w");

                // write
                fwrite(block, sizeof(block), 1, img);
            }
        }
        // if we found a jpg already
        else if (jpgCount)
        {
            fwrite(block, sizeof(block), 1, img);
        }
    }
    fclose(img);
    fclose(inptr);
}