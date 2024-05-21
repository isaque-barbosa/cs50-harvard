#include <cs50.h>
#include <stdio.h>

#define INFERIOR_LIMIT 1
#define SUPERIOR_LIMIT 8

int get_wall_size(void);
void print_wall(int size);

int main(void)
{
    int size = get_wall_size();
    print_wall(size);
}

// Função para imprimir a parede
void print_wall(int size)
{
    char bricks[size];
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j >= 0; j--)
        {
            if (j <= i)
            {
                bricks[i] = '#';
            }
            else
            {
                printf(" ");
            }
        }
        printf("%s ", bricks);
        printf(" %s\n", bricks);
    }
}

// Função para obter e validar o tamanho da parede
int get_wall_size(void)
{
    int wall_size;
    do
    {
        wall_size = get_int("Tamanho: ");
    }
    while (wall_size < INFERIOR_LIMIT || wall_size > SUPERIOR_LIMIT);
    return wall_size;
}
