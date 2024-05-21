#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Use: ./recover image.\n");
        return 1;
    }
    FILE *source = fopen(argv[1], "r");
    if (source == NULL)
    {
        printf("FILE NOT FOUND!");
        return 1;
    }

    int count_images = 0;
    char *filename = malloc(8);
    FILE *img = NULL;
    BYTE buffer[512];
    while (fread(buffer, sizeof(BYTE), 512, source) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count_images++);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create %s.\n", filename);
                return 1;
            }
        }
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
        if (count_images > 50)
        {
            break;
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(source);
    free(filename);
    return 0;
}
