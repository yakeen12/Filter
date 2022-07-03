#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Done.

    int avgColor = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avgColor =  round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue  = avgColor;
            image[i][j].rgbtRed = avgColor;
            image[i][j].rgbtGreen = avgColor;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue  = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE leftImage[height][width];

    // Saving left side of the image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {


            leftImage[i][j].rgbtBlue  = image[i][j].rgbtBlue;
            leftImage[i][j].rgbtRed = image[i][j].rgbtRed;
            leftImage[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }



    // Putting the left copy at the right ... from width to zero.
    for (int i = 0; i < height; i++)
    {
        int k = 0;
        for (int j = width - 1; j >= 0; j--)
        {


            image[i][j].rgbtBlue  = leftImage[i][k].rgbtBlue;
            image[i][j].rgbtRed = leftImage[i][k].rgbtRed;
            image[i][j].rgbtGreen = leftImage[i][k].rgbtGreen;
            k++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // I'll make a copy image then use it.
    RGBTRIPLE copyImage[height][width];
    int avgRed = 0;
    int avgBlue = 0;
    int avgGreen = 0;
    // 1 1 ---> -1 -1
    // Middle pixels.
    for (int i = 1; i < height - 1; i++)
    {

        for (int j = 1; j < width - 1; j++)
        {
            avgRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed
                            + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                            + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);

            avgGreen = round((image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen
                              + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                              + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9.0);

            avgBlue = round((image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue
                             + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                             + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 9.0);

            // Save them in the array

            copyImage[i][j].rgbtRed = avgRed;
            copyImage[i][j].rgbtGreen = avgGreen;
            copyImage[i][j].rgbtBlue = avgBlue;

        }
    }

    // Upper row ---> height = 0, width changes.
    for (int j = 1; j < width - 1; j++)
    {
        avgRed = round((image[0][j - 1].rgbtRed + image[0][j].rgbtRed + image[0][j + 1].rgbtRed
                        + image[1][j - 1].rgbtRed + image[1][j].rgbtRed + image[1][j + 1].rgbtRed) / 6.0);

        avgGreen = round((image[0][j - 1].rgbtGreen + image[0][j].rgbtGreen + image[0][j + 1].rgbtGreen
                          + image[1][j - 1].rgbtGreen + image[1][j].rgbtGreen + image[1][j + 1].rgbtGreen) / 6.0);

        avgBlue = round((image[0][j - 1].rgbtBlue + image[0][j].rgbtBlue + image[0][j + 1].rgbtBlue
                         + image[1][j - 1].rgbtBlue + image[1][j].rgbtBlue + image[1][j + 1].rgbtBlue) / 6.0);

        // Save them in the array

        copyImage[0][j].rgbtRed = avgRed;
        copyImage[0][j].rgbtGreen = avgGreen;
        copyImage[0][j].rgbtBlue = avgBlue;

    }


    // Lower row ---> height = height - 1, width changes.
    for (int j = 1; j < width - 1; j++)
    {
        avgRed = round((image[height - 2][j - 1].rgbtRed + image[height - 2][j].rgbtRed + image[height - 2][j + 1].rgbtRed
                        + image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed + image[height - 1][j + 1].rgbtRed) / 6.0);

        avgGreen = round((image[height - 2][j - 1].rgbtGreen + image[height - 2][j].rgbtGreen + image[height - 2][j + 1].rgbtGreen
                          + image[height - 1][j - 1].rgbtGreen + image[height - 1][j].rgbtGreen + image[height - 1][j + 1].rgbtGreen) / 6.0);

        avgBlue = round((image[height - 2][j - 1].rgbtBlue + image[height - 2][j].rgbtBlue + image[height - 2][j + 1].rgbtBlue
                         + image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue + image[height - 1][j + 1].rgbtBlue) / 6.0);

        // Save them in the array

        copyImage[height - 1][j].rgbtRed = avgRed;
        copyImage[height - 1][j].rgbtGreen = avgGreen;
        copyImage[height - 1][j].rgbtBlue = avgBlue;

    }



    // Right column ---> width = width - 1, height changes.
    for (int i = 1; i < height - 1; i++)
    {
        avgRed = round((image[i - 1][width - 2].rgbtRed + image[i - 1][width - 1].rgbtRed + image[i][width - 2].rgbtRed
                        + image[i][width - 1].rgbtRed + image[i + 1][width - 2].rgbtRed + image[i + 1][width - 1].rgbtRed) / 6.0);

        avgGreen = round((image[i - 1][width - 2].rgbtGreen + image[i - 1][width - 1].rgbtGreen + image[i][width - 2].rgbtGreen
                          + image[i][width - 1].rgbtGreen + image[i + 1][width - 2].rgbtGreen + image[i + 1][width - 1].rgbtGreen) / 6.0);

        avgBlue = round((image[i - 1][width - 2].rgbtBlue + image[i - 1][width - 1].rgbtBlue + image[i][width - 2].rgbtBlue
                         + image[i][width - 1].rgbtBlue + image[i + 1][width - 2].rgbtBlue + image[i + 1][width - 1].rgbtBlue) / 6.0);

        // Save them in the array

        copyImage[i][width - 1].rgbtRed = avgRed;
        copyImage[i][width - 1].rgbtGreen = avgGreen;
        copyImage[i][width - 1].rgbtBlue = avgBlue;
    }



    // Left column ---> width = 0, height changes till height - 2.
    for (int i = 1; i < height - 1; i++)
    {
        avgRed = round((image[i - 1][0].rgbtRed + image[i - 1][1].rgbtRed + image[i][0].rgbtRed
                        + image[i][1].rgbtRed + image[i + 1][0].rgbtRed + image[i + 1][1].rgbtRed) / 6.0);

        avgGreen = round((image[i - 1][0].rgbtGreen + image[i - 1][1].rgbtGreen + image[i][0].rgbtGreen
                          + image[i][1].rgbtGreen + image[i + 1][0].rgbtGreen + image[i + 1][1].rgbtGreen) / 6.0);

        avgBlue = round((image[i - 1][0].rgbtBlue + image[i - 1][1].rgbtBlue + image[i][0].rgbtBlue
                         + image[i][1].rgbtBlue + image[i + 1][0].rgbtBlue + image[i + 1][1].rgbtBlue) / 6.0);

        // Save them in the array

        copyImage[i][0].rgbtRed = avgRed;
        copyImage[i][0].rgbtGreen = avgGreen;
        copyImage[i][0].rgbtBlue = avgBlue;
    }

    // Left upper corner. [0][0]
    avgRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed
                    + image[1][1].rgbtRed) / 4.0);

    avgGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen
                      + image[1][1].rgbtGreen) / 4.0);

    avgBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue
                     + image[1][1].rgbtBlue) / 4.0);

    // Save it.
    copyImage[0][0].rgbtRed = avgRed;
    copyImage[0][0].rgbtGreen = avgGreen;
    copyImage[0][0].rgbtBlue = avgBlue;


    // Right upper corner. [0][width - 1]
    avgRed = round((image[0][width - 2].rgbtRed + image[0][width - 1].rgbtRed + image[1][width - 2].rgbtRed
                    + image[1][width - 1].rgbtRed) / 4.0);

    avgGreen = round((image[0][width - 2].rgbtGreen + image[0][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen
                      + image[1][width - 1].rgbtGreen) / 4.0);

    avgBlue = round((image[0][width - 2].rgbtBlue + image[0][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue
                     + image[1][width - 1].rgbtBlue) / 4.0);

    // Save it.
    copyImage[0][width - 1].rgbtRed = avgRed;
    copyImage[0][width - 1].rgbtGreen = avgGreen;
    copyImage[0][width - 1].rgbtBlue = avgBlue;


    // Left lower corner. [height - 1][0]
    avgRed = round((image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed + image[height - 1][0].rgbtRed
                    + image[height - 1][1].rgbtRed) / 4.0);

    avgGreen = round((image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen + image[height - 1][0].rgbtGreen
                      + image[height - 1][1].rgbtGreen) / 4.0);

    avgBlue = round((image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue + image[height - 1][0].rgbtBlue
                     + image[height - 1][1].rgbtBlue) / 4.0);

    // Save it.
    copyImage[height - 1][0].rgbtRed = avgRed;
    copyImage[height - 1][0].rgbtGreen = avgGreen;
    copyImage[height - 1][0].rgbtBlue = avgBlue;

    // Right lower corner. [height - 1][width - 1]
    avgRed = round((image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed
                    + image[height - 1][width - 2].rgbtRed
                    + image[height - 1][width - 1].rgbtRed) / 4.0);

    avgGreen = round((image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen
                      + image[height - 1][width - 2].rgbtGreen
                      + image[height - 1][width - 1].rgbtGreen) / 4.0);

    avgBlue = round((image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue
                     + image[height - 1][width - 2].rgbtBlue
                     + image[height - 1][width - 1].rgbtBlue) / 4.0);

    // Save it.
    copyImage[height - 1][width - 1].rgbtRed = avgRed;
    copyImage[height - 1][width - 1].rgbtGreen = avgGreen;
    copyImage[height - 1][width - 1].rgbtBlue = avgBlue;

    // Set the image as the array.
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (copyImage[i][j].rgbtRed > 255)
            {
                copyImage[i][j].rgbtRed = 255;
            }
            if (copyImage[i][j].rgbtGreen > 255)
            {
                copyImage[i][j].rgbtGreen = 255;
            }
            if (copyImage[i][j].rgbtBlue > 255)
            {
                copyImage[i][j].rgbtBlue = 255;
            }
            image[i][j].rgbtRed = copyImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = copyImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copyImage[i][j].rgbtBlue;

        }

    }


    return;
}
