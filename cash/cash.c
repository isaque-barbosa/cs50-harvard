#include <cs50.h>
#include <stdio.h>

float get_valid_change(void);
int calcule_change_coin_amount(float change);

int main(void)
{
    float change = get_valid_change();
    int coinAmount = calcule_change_coin_amount(change);
    printf("%i\n", coinAmount);
}

int calcule_change_coin_amount(float change)
{
    int coins[4] = {25, 10, 5, 1};
    int coinAmount = 0;
    int convertedChange = (int) (change * 100 + 0.5);
    while (convertedChange > 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (convertedChange - coins[i] >= 0)
            {
                convertedChange -= coins[i];
                coinAmount++;
                i--;
            }
        }
    }
    return coinAmount;
}

float get_valid_change(void)
{
    float change;
    do
    {
        change = get_float("Troca devida: ");
    }
    while (change < 0);
    return change;
}
