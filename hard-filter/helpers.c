#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE current = image[i][j];
            int avg = (current.rgbtRed + current.rgbtGreen + current.rgbtBlue + 1.5) / 3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE current = image[i][j];
            int sepiaRed = round(0.393 * current.rgbtRed + 0.769 * current.rgbtGreen +
                                 0.189 * current.rgbtBlue);
            int sepiaGreen = round(0.349 * current.rgbtRed + 0.686 * current.rgbtGreen +
                                   0.168 * current.rgbtBlue);
            int sepiaBlue = round(0.272 * current.rgbtRed + 0.534 * current.rgbtGreen +
                                  0.131 * current.rgbtBlue);
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int other_half = width - j - 1;
            RGBTRIPLE current = image[i][j];
            image[i][j] = image[i][other_half];
            image[i][other_half] = current;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            int counter = 0;

            // Soma os valores dos pixels ao redor
            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k >= height || j + h < 0 || j + h >= width)
                    {
                        continue;
                    }

                    sumBlue += image[i + k][j + h].rgbtBlue;
                    sumGreen += image[i + k][j + h].rgbtGreen;
                    sumRed += image[i + k][j + h].rgbtRed;
                    counter++;
                }
            }

            // Calcula a média e atribui ao pixel
            temp[i][j].rgbtBlue = round(sumBlue / (float) counter);
            temp[i][j].rgbtGreen = round(sumGreen / (float) counter);
            temp[i][j].rgbtRed = round(sumRed / (float) counter);
        }
    }

    // Copia a imagem temporária para a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
