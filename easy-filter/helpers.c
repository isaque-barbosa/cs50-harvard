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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxBlue = 0, GxGreen = 0, GxRed = 0;
            int GyBlue = 0, GyGreen = 0, GyRed = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k >= height || j + h < 0 || j + h >= width)
                    {
                        continue;
                    }

                    GxBlue += image[i + k][j + h].rgbtBlue * Gx[k + 1][h + 1];
                    GxGreen += image[i + k][j + h].rgbtGreen * Gx[k + 1][h + 1];
                    GxRed += image[i + k][j + h].rgbtRed * Gx[k + 1][h + 1];

                    GyBlue += image[i + k][j + h].rgbtBlue * Gy[k + 1][h + 1];
                    GyGreen += image[i + k][j + h].rgbtGreen * Gy[k + 1][h + 1];
                    GyRed += image[i + k][j + h].rgbtRed * Gy[k + 1][h + 1];
                }
            }

            int blue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            int green = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int red = round(sqrt(GxRed * GxRed + GyRed * GyRed));

            temp[i][j].rgbtBlue = blue > 255 ? 255 : blue;
            temp[i][j].rgbtGreen = green > 255 ? 255 : green;
            temp[i][j].rgbtRed = red > 255 ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
