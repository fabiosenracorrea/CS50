#include "helpers.h"
#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int roundedAvg = round(avg);
            image[i][j].rgbtBlue = roundedAvg;
            image[i][j].rgbtGreen = roundedAvg;
            image[i][j].rgbtRed = roundedAvg;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int wLimit = (width % 2 == 0) ? (width / 2) : ((width - 1) / 2);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < wLimit; j++)
        {
            // saves left pixels
            int placeBlue = image[i][j].rgbtBlue;
            int placeGreen = image[i][j].rgbtGreen;
            int placeRed = image[i][j].rgbtRed;

            // makes left = right
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            // makes right = saved left
            image[i][width - j - 1].rgbtBlue = placeBlue;
            image[i][width - j - 1].rgbtGreen = placeGreen;
            image[i][width - j - 1].rgbtRed = placeRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*newImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //control variables
            int accBlue = 0;
            int accGreen = 0;
            int accRed = 0;
            float squareCount = 0.0;

            // finds what squares exists and collects their data
            for (int w = -1; w < 2; w ++)
            {
                for (int k = -1; k < 2; k++)
                {
                    if ((i + w) >= 0 && (j + k) >= 0 && (i + w) < height && (j + k) < width)
                    {
                        accBlue += image[i + w][j + k].rgbtBlue;
                        accGreen += image[i + w][j + k].rgbtGreen;
                        accRed += image[i + w][j + k].rgbtRed;
                        squareCount += 1.0;
                    }
                }
            }

            // fills our 'blured' img with the calculations
            newImage[i][j].rgbtBlue = round(accBlue / squareCount);
            newImage[i][j].rgbtGreen = round(accGreen / squareCount);
            newImage[i][j].rgbtRed = round(accRed / squareCount);
        }
    }

    // copies the blured img to the actual img
    for (int s = 0; s < height; s++)
    {
        for (int t = 0; t < width; t++)
        {
            image[s][t].rgbtBlue = newImage[s][t].rgbtBlue;
            image[s][t].rgbtGreen = newImage[s][t].rgbtGreen;
            image[s][t].rgbtRed = newImage[s][t].rgbtRed;
        }
    }

    free(newImage);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*gxyImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //control variables
            int accGXBlue = 0;
            int accGXGreen = 0;
            int accGXRed = 0;
            int accGYBlue = 0;
            int accGYGreen = 0;
            int accGYRed = 0;

            // going to each '3x3 square' from current pixel
            for (int w = -1; w < 2; w ++)
            {
                for (int k = -1; k < 2; k++)
                {
                    if ((i + w) >= 0 && (j + k) >= 0 && (i + w) < height && (j + k) < width)
                    {
                        // GX matrix
                        if ((w == -1 && k == -1) || (w == 1 && k == -1))
                        {
                            accGXBlue += (image[i + w][j + k].rgbtBlue * -1);
                            accGXGreen += (image[i + w][j + k].rgbtGreen * -1);
                            accGXRed += (image[i + w][j + k].rgbtRed * -1);
                        }
                        else if ((w == -1 && k == 1) || (w == 1 && k == 1))
                        {
                            accGXBlue += (image[i + w][j + k].rgbtBlue * 1);
                            accGXGreen += (image[i + w][j + k].rgbtGreen * 1);
                            accGXRed += (image[i + w][j + k].rgbtRed * 1);
                        }
                        else if ((w == 0 && k == -1) || (w == 0 && k == 1))
                        {
                            accGXBlue += (image[i + w][j + k].rgbtBlue * 2 * k);
                            accGXGreen += (image[i + w][j + k].rgbtGreen * 2 * k);
                            accGXRed += (image[i + w][j + k].rgbtRed * 2 * k);
                        }

                        // GY matrix
                        if ((w == -1 && k != 0) || (w == 1 && k != 0))
                        {
                            accGYBlue += (image[i + w][j + k].rgbtBlue * 1 * w);
                            accGYGreen += (image[i + w][j + k].rgbtGreen * 1 * w);
                            accGYRed += (image[i + w][j + k].rgbtRed * 1 * w);
                        }
                        else if ((w == -1 && k == 0) || (w == 1 && k == 0))
                        {
                            accGYBlue += (image[i + w][j + k].rgbtBlue * 2 * w);
                            accGYGreen += (image[i + w][j + k].rgbtGreen * 2 * w);
                            accGYRed += (image[i + w][j + k].rgbtRed * 2 * w);
                        }
                    }
                }
            }

            int accBlue = (round(sqrt(pow(accGXBlue, 2) + pow(accGYBlue, 2))));
            int accGreen = (round(sqrt(pow(accGXGreen, 2) + pow(accGYGreen, 2))));
            int accRed = (round(sqrt(pow(accGXRed, 2) + pow(accGYRed, 2))));


            gxyImage[i][j].rgbtBlue = (accBlue > 255 ? 255 : accBlue);
            gxyImage[i][j].rgbtGreen = (accGreen > 255 ? 255 : accGreen);
            gxyImage[i][j].rgbtRed = (accRed > 255 ? 255 : accRed);
        }
    }

    for (int s = 0; s < height; s++)
    {
        for (int t = 0; t < width; t++)
        {
            image[s][t].rgbtBlue = gxyImage[s][t].rgbtBlue;
            image[s][t].rgbtGreen = gxyImage[s][t].rgbtGreen;
            image[s][t].rgbtRed = gxyImage[s][t].rgbtRed;
        }
    }

    free(gxyImage);
}
