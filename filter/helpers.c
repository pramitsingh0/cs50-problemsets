#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            avg = round(avg);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float sepiaBlue = 0.272 * image[i][j].rgbtRed  + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            //Rounding the values of RGB
            sepiaRed = round(sepiaRed);
            sepiaBlue = round(sepiaBlue);
            sepiaGreen = round(sepiaGreen);
            //cap color values at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            //replacing the value of RGB
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < round(width / 2); i++)
        {
            RGBTRIPLE tempimage;
            tempimage = image[j][i];
            image[j][i] = image[j][width - 1 - i];
            image[j][width - 1 -i] = tempimage;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            tempimage[a][b] = image[a][b];
        }
    }
    float totalred, totalgreen, totalblue, count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalred = totalgreen = totalblue = count = 0;

            for (int a = i - 1; a <= i + 1; a++)
            {
                if (a < 0 || a > height - 1)
                {
                    continue;
                }

                for (int b = j - 1; b <= j + 1; b++)
                {
                    if (b < 0 || b > width - 1)
                    {
                        continue;
                    }

                    totalred += tempimage[a][b].rgbtRed;
                    totalgreen += tempimage[a][b].rgbtGreen;
                    totalblue += tempimage[a][b].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = (int) round((totalred)/count);
            image[i][j].rgbtGreen = (int) round((totalgreen)/count);
            image[i][j].rgbtBlue = (int) round((totalblue)/count);
        }

    }
    return;
}
