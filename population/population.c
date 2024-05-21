#include <cs50.h>
#include <stdio.h>

int get_valid_start(void);
int get_valid_end(int start);
int calculate_population_years_to_size(int population, int goal);

int main(void)
{
    int startSize = get_valid_start();
    int endSize = get_valid_end(startSize);
    int years = calculate_population_years_to_size(startSize, endSize);
    printf("Years: %i\n", years);
}

int get_valid_start(void)
{
    int start = 0;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    return start;
}

int get_valid_end(int start)
{
    int end = 0;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    return end;
}

int calculate_population_years_to_size(int population, int goal)
{
    int years = 0;
    while (population < goal)
    {
        int grow = population / 3;
        int death = population / 4;
        population += (grow - death);
        years++;
    }
    return years;
}
