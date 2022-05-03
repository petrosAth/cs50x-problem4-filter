#include <math.h>
#include <string.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0, tmp = 0; j < width; ++j)
        {
            tmp = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    memcpy(tmp, image, sizeof(tmp));
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j] = tmp[i][width - 1 - j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temp array
    RGBTRIPLE tmp[height][width];
    // Copy items from image to temp array
    memcpy(tmp, image, sizeof(tmp));

    // Loop for rows
    for (int i = 0; i < height; ++i)
    {
        // Loop for columns
        for (int j = 0; j < width; ++j)
        {
            // Top left corner
            if ((i == 0) && (j == 0))
            {
                image[i][j].rgbtBlue = round((tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) /
                                             4.0);
                image[i][j].rgbtGreen = round((tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j +
                                               1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = round((tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 4.0);
            }
            // Top right corner
            else if ((i == 0) && (j == width - 1))
            {
                image[i][j].rgbtBlue = round((tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue) /
                                             4.0);
                image[i][j].rgbtGreen = round((tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i +
                                               1][j].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = round((tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed) / 4.0);
            }
            // Bottom right corner
            else if ((i == height - 1) && (j == width - 1))
            {
                image[i][j].rgbtBlue = round((tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue) /
                                             4.0);
                image[i][j].rgbtGreen = round((tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i][j - 1].rgbtGreen +
                                               tmp[i][j].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = round((tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed) / 4.0);
            }
            // Bottom left corner
            else if ((i == height - 1) && (j == 0))
            {
                image[i][j].rgbtBlue = round((tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue) /
                                             4.0);
                image[i][j].rgbtGreen = round((tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j +
                                               1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = round((tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed) / 4.0);
            }
            // Top side
            else if (((i == 0) && (j != 0)) || ((i == 0) && (j != width - 1)))
            {
                image[i][j].rgbtBlue = round((tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue +
                                              tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen
                                               + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = round((tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i +
                                             1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 6.0);
            }
            // Right side
            else if (((j == width - 1) && (i != 0)) || ((j == width - 1) && (i != height - 1)))
            {
                image[i][j].rgbtBlue = round((tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue +
                                              tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen
                                               + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = round((tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i +
                                             1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed) / 6.0);
            }
            // Bottom side
            else if (((i == height - 1) && (j != 0)) || ((i == height - 1) && (j != width - 1)))
            {
                image[i][j].rgbtBlue = round((tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j -
                                              1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j -
                                               1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = round((tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed +
                                             tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed) / 6.0);
            }
            // Left side
            else if (((j == 0) && (i != 0)) || ((j == 0) && (i != height - 1)))
            {
                image[i][j].rgbtBlue = round((tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue +
                                              tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen
                                               + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = round((tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i +
                                             1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 6.0);
            }
            // Main body
            else
            {
                image[i][j].rgbtBlue = round((tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue + tmp[i][j -
                                              1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j +
                                                      1].rgbtBlue) / 9.0);
                image[i][j].rgbtGreen = round((tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen + tmp[i][j -
                                               1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j
                                                       + 1].rgbtGreen) / 9.0);
                image[i][j].rgbtRed = round((tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed + tmp[i][j - 1].rgbtRed +
                                             tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed + tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed) / 9.0);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Temp array
    RGBTRIPLE tmp[height][width];

    int GxBlue = 0, GxGreen = 0, GxRed = 0, GyBlue = 0, GyGreen = 0, GyRed = 0;
    int tmpBlue = 0, tmpGreen = 0, tmpRed = 0;

    // Copy items from image to temp array
    memcpy(tmp, image, sizeof(tmp));

    // Loop for rows
    for (int i = 0; i < height; ++i)
    {
        // Loop for columns
        for (int j = 0; j < width; ++j)
        {
            // Top left corner
            if ((i == 0) && (j == 0))
            {
                GxBlue = tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 2 + tmp[i + 1][j].rgbtBlue * 0 + tmp[i + 1][j + 1].rgbtBlue * 1;
                GyBlue = tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 0 + tmp[i + 1][j].rgbtBlue * 2 + tmp[i + 1][j + 1].rgbtBlue * 1;

                GxGreen = tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 2 + tmp[i + 1][j].rgbtGreen * 0 + tmp[i + 1][j + 1].rgbtGreen * 1;
                GyGreen = tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 0 + tmp[i + 1][j].rgbtGreen * 2 + tmp[i + 1][j + 1].rgbtGreen * 1;

                GxRed = tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 2 + tmp[i + 1][j].rgbtRed * 0 + tmp[i + 1][j + 1].rgbtRed * 1;
                GyRed = tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 0 + tmp[i + 1][j].rgbtRed * 2 + tmp[i + 1][j + 1].rgbtRed * 1;

            }
            // Top right corner
            else if ((i == 0) && (j == width - 1))
            {
                GxBlue = tmp[i][j - 1].rgbtBlue * -2 + tmp[i][j].rgbtBlue * 0 + tmp[i + 1][j - 1].rgbtBlue * -1 + tmp[i + 1][j].rgbtBlue * 0;
                GyBlue = tmp[i][j - 1].rgbtBlue * 0 + tmp[i][j].rgbtBlue * 0 + tmp[i + 1][j - 1].rgbtBlue * 1 + tmp[i + 1][j].rgbtBlue * 2;

                GxGreen = tmp[i][j - 1].rgbtGreen * -2 + tmp[i][j].rgbtGreen * 0 + tmp[i + 1][j - 1].rgbtGreen * -1 + tmp[i + 1][j].rgbtGreen * 0;
                GyGreen = tmp[i][j - 1].rgbtGreen * 0 + tmp[i][j].rgbtGreen * 0 + tmp[i + 1][j - 1].rgbtGreen * 1 + tmp[i + 1][j].rgbtGreen * 2;

                GxRed = tmp[i][j - 1].rgbtRed * -2 + tmp[i][j].rgbtRed * 0 + tmp[i + 1][j - 1].rgbtRed * -1 + tmp[i + 1][j].rgbtRed * 0;
                GyRed = tmp[i][j - 1].rgbtRed * 0 + tmp[i][j].rgbtRed * 0 + tmp[i + 1][j - 1].rgbtRed * 1 + tmp[i + 1][j].rgbtRed * 2;
            }
            // Bottom right corner
            else if ((i == height - 1) && (j == width - 1))
            {
                GxBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * 0 + tmp[i][j - 1].rgbtBlue * -2 + tmp[i][j].rgbtBlue * 0;
                GyBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * -2 + tmp[i][j - 1].rgbtBlue * 0 + tmp[i][j].rgbtBlue * 0;

                GxGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * 0 + tmp[i][j - 1].rgbtGreen * -2 + tmp[i][j].rgbtGreen * 0;
                GyGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * -2 + tmp[i][j - 1].rgbtGreen * 0 + tmp[i][j].rgbtGreen * 0;

                GxRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * 0 + tmp[i][j - 1].rgbtRed * -2 + tmp[i][j].rgbtRed * 0;
                GyRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * -2 + tmp[i][j - 1].rgbtRed * 0 + tmp[i][j].rgbtRed * 0;
            }
            // Bottom left corner
            else if ((i == height - 1) && (j == 0))
            {
                GxBlue = tmp[i - 1][j].rgbtBlue * 0 + tmp[i - 1][j + 1].rgbtBlue * 1 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 2;
                GyBlue = tmp[i - 1][j].rgbtBlue * -2 + tmp[i - 1][j + 1].rgbtBlue * -1 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 0;

                GxGreen = tmp[i - 1][j].rgbtGreen * 0 + tmp[i - 1][j + 1].rgbtGreen * 1 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 2;
                GyGreen = tmp[i - 1][j].rgbtGreen * -2 + tmp[i - 1][j + 1].rgbtGreen * -1 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 0;

                GxRed = tmp[i - 1][j].rgbtRed * 0 + tmp[i - 1][j + 1].rgbtRed * 1 + tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 2;
                GyRed = tmp[i - 1][j].rgbtRed * -2 + tmp[i - 1][j + 1].rgbtRed * -1 + tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 0;
            }
            // Top side
            else if (((i == 0) && (j != 0)) || ((i == 0) && (j != width - 1)))
            {
                GxBlue = tmp[i][j - 1].rgbtBlue * -2 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 2 + tmp[i + 1][j - 1].rgbtBlue * -1 + tmp[i
                         + 1][j].rgbtBlue * 0 + tmp[i + 1][j + 1].rgbtBlue * 1;
                GyBlue = tmp[i][j - 1].rgbtBlue * 0 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 0 + tmp[i + 1][j - 1].rgbtBlue * 1 + tmp[i +
                         1][j].rgbtBlue * 2 + tmp[i + 1][j + 1].rgbtBlue * 1;

                GxGreen = tmp[i][j - 1].rgbtGreen * -2 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 2 + tmp[i + 1][j - 1].rgbtGreen * -1 +
                          tmp[i + 1][j].rgbtGreen * 0 + tmp[i + 1][j + 1].rgbtGreen * 1;
                GyGreen = tmp[i][j - 1].rgbtGreen * 0 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 0 + tmp[i + 1][j - 1].rgbtGreen * 1 +
                          tmp[i + 1][j].rgbtGreen * 2 + tmp[i + 1][j + 1].rgbtGreen * 1;

                GxRed = tmp[i][j - 1].rgbtRed * -2 + tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 2 + tmp[i + 1][j - 1].rgbtRed * -1 + tmp[i +
                        1][j].rgbtRed * 0 + tmp[i + 1][j + 1].rgbtRed * 1;
                GyRed = tmp[i][j - 1].rgbtRed * 0 + tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 0 + tmp[i + 1][j - 1].rgbtRed * 1 + tmp[i +
                        1][j].rgbtRed * 2 + tmp[i + 1][j + 1].rgbtRed * 1;
            }
            // Right side
            else if (((j == width - 1) && (i != 0)) || ((j == width - 1) && (i != height - 1)))
            {
                GxBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * 0 + tmp[i][j - 1].rgbtBlue * -2 + tmp[i][j].rgbtBlue * 0 + tmp[i
                         + 1][j - 1].rgbtBlue * -1 + tmp[i + 1][j].rgbtBlue * 0;
                GyBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * -2 + tmp[i][j - 1].rgbtBlue * 0 + tmp[i][j].rgbtBlue * 0 + tmp[i
                         + 1][j - 1].rgbtBlue * 1 + tmp[i + 1][j].rgbtBlue * 2;

                GxGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * 0 + tmp[i][j - 1].rgbtGreen * -2 + tmp[i][j].rgbtGreen * 0 +
                          tmp[i + 1][j - 1].rgbtGreen * -1 + tmp[i + 1][j].rgbtGreen * 0;
                GyGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * -2 + tmp[i][j - 1].rgbtGreen * 0 + tmp[i][j].rgbtGreen * 0 +
                          tmp[i + 1][j - 1].rgbtGreen * 1 + tmp[i + 1][j].rgbtGreen * 2;

                GxRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * 0 + tmp[i][j - 1].rgbtRed * -2 + tmp[i][j].rgbtRed * 0 + tmp[i +
                        1][j - 1].rgbtRed * -1 + tmp[i + 1][j].rgbtRed * 0;
                GyRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * -2 + tmp[i][j - 1].rgbtRed * 0 + tmp[i][j].rgbtRed * 0 + tmp[i +
                        1][j - 1].rgbtRed * 1 + tmp[i + 1][j].rgbtRed * 2;
            }
            // Bottom side
            else if (((i == height - 1) && (j != 0)) || ((i == height - 1) && (j != width - 1)))
            {
                GxBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * 0 + tmp[i - 1][j + 1].rgbtBlue * 1 + tmp[i][j - 1].rgbtBlue * -2
                         + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 2;
                GyBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * -2 + tmp[i - 1][j + 1].rgbtBlue * -1 + tmp[i][j - 1].rgbtBlue *
                         0 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 0;

                GxGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * 0 + tmp[i - 1][j + 1].rgbtGreen * 1 + tmp[i][j - 1].rgbtGreen
                          * -2 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 2;
                GyGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * -2 + tmp[i - 1][j + 1].rgbtGreen * -1 + tmp[i][j -
                          1].rgbtGreen * 0 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 0;

                GxRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * 0 + tmp[i - 1][j + 1].rgbtRed * 1 + tmp[i][j - 1].rgbtRed * -2 +
                        tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 2;
                GyRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * -2 + tmp[i - 1][j + 1].rgbtRed * -1 + tmp[i][j - 1].rgbtRed * 0 +
                        tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 0;

            }
            // Left side
            else if (((j == 0) && (i != 0)) || ((j == 0) && (i != height - 1)))
            {
                GxBlue = tmp[i - 1][j].rgbtBlue * 0 + tmp[i - 1][j + 1].rgbtBlue * 1 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 2 + tmp[i +
                         1][j].rgbtBlue * 0 + tmp[i + 1][j + 1].rgbtBlue * 1;
                GyBlue = tmp[i - 1][j].rgbtBlue * -2 + tmp[i - 1][j + 1].rgbtBlue * -1 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 0 + tmp[i
                         + 1][j].rgbtBlue * 2 + tmp[i + 1][j + 1].rgbtBlue * 1;

                GxGreen = tmp[i - 1][j].rgbtGreen * 0 + tmp[i - 1][j + 1].rgbtGreen * 1 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 2 +
                          tmp[i + 1][j].rgbtGreen * 0 + tmp[i + 1][j + 1].rgbtGreen * 1;
                GyGreen = tmp[i - 1][j].rgbtGreen * -2 + tmp[i - 1][j + 1].rgbtGreen * -1 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 0 +
                          tmp[i + 1][j].rgbtGreen * 2 + tmp[i + 1][j + 1].rgbtGreen * 1;

                GxRed = tmp[i - 1][j].rgbtRed * 0 + tmp[i - 1][j + 1].rgbtRed * 1 + tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 2 + tmp[i +
                        1][j].rgbtRed * 0 + tmp[i + 1][j + 1].rgbtRed * 1;
                GyRed = tmp[i - 1][j].rgbtRed * -2 + tmp[i - 1][j + 1].rgbtRed * -1 + tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 0 + tmp[i +
                        1][j].rgbtRed * 2 + tmp[i + 1][j + 1].rgbtRed * 1;
            }
            // Main body
            else
            {
                GxBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * 0 + tmp[i - 1][j + 1].rgbtBlue * 1 + tmp[i][j - 1].rgbtBlue * -2
                         + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 2 + tmp[i + 1][j - 1].rgbtBlue * -1 + tmp[i + 1][j].rgbtBlue * 0 + tmp[i + 1][j
                                 + 1].rgbtBlue * 1;
                GyBlue = tmp[i - 1][j - 1].rgbtBlue * -1 + tmp[i - 1][j].rgbtBlue * -2 + tmp[i - 1][j + 1].rgbtBlue * -1 + tmp[i][j - 1].rgbtBlue *
                         0 + tmp[i][j].rgbtBlue * 0 + tmp[i][j + 1].rgbtBlue * 0 + tmp[i + 1][j - 1].rgbtBlue * 1 + tmp[i + 1][j].rgbtBlue * 2 + tmp[i + 1][j
                                 + 1].rgbtBlue * 1;

                GxGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * 0 + tmp[i - 1][j + 1].rgbtGreen * 1 + tmp[i][j - 1].rgbtGreen
                          * -2 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 2 + tmp[i + 1][j - 1].rgbtGreen * -1 + tmp[i + 1][j].rgbtGreen * 0 +
                          tmp[i + 1][j + 1].rgbtGreen * 1;
                GyGreen = tmp[i - 1][j - 1].rgbtGreen * -1 + tmp[i - 1][j].rgbtGreen * -2 + tmp[i - 1][j + 1].rgbtGreen * -1 + tmp[i][j -
                          1].rgbtGreen * 0 + tmp[i][j].rgbtGreen * 0 + tmp[i][j + 1].rgbtGreen * 0 + tmp[i + 1][j - 1].rgbtGreen * 1 + tmp[i + 1][j].rgbtGreen
                          * 2 + tmp[i + 1][j + 1].rgbtGreen * 1;

                GxRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * 0 + tmp[i - 1][j + 1].rgbtRed * 1 + tmp[i][j - 1].rgbtRed * -2 +
                        tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 2 + tmp[i + 1][j - 1].rgbtRed * -1 + tmp[i + 1][j].rgbtRed * 0 + tmp[i + 1][j +
                                1].rgbtRed * 1;
                GyRed = tmp[i - 1][j - 1].rgbtRed * -1 + tmp[i - 1][j].rgbtRed * -2 + tmp[i - 1][j + 1].rgbtRed * -1 + tmp[i][j - 1].rgbtRed * 0 +
                        tmp[i][j].rgbtRed * 0 + tmp[i][j + 1].rgbtRed * 0 + tmp[i + 1][j - 1].rgbtRed * 1 + tmp[i + 1][j].rgbtRed * 2 + tmp[i + 1][j +
                                1].rgbtRed * 1;

            }

            // Check if Blue value is above 255
            tmpBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            if (tmpBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = tmpBlue;
            }

            // Check if Green value is above 255
            tmpGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            if (tmpGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = tmpGreen;
            }

            // Check if Red value is above 255
            tmpRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            if (tmpRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = tmpRed;
            }
        }
    }
    return;
}
