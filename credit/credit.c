#include <cs50.h>
#include <stdio.h>

int validate_card_number(long cardNumber);
int is_number_valid(int number);
int sum_card_number(int numbers[], int numberAmount);
int is_number_amex_valid(int numbers[], int numberAmount);
int is_number_visa_valid(int numbers[], int numberAmount);
int is_number_mastercard_valid(int numbers[], int numberAmount);

int main(void)
{
    long cardNumber = get_long("Número: ");
    return validate_card_number(cardNumber);
}

int validate_card_number(long cardNumber)
{
    int numberAmount = 0;
    int numbers[16];
    int sum = 0;
    while (cardNumber > 0)
    {
        numbers[numberAmount] = cardNumber % 10;
        cardNumber /= 10;
        numberAmount++;
    }
    if (is_number_valid(numberAmount) == 1)
    {
        printf("INVALID\n");
        return 0;
    }
    sum = sum_card_number(numbers, numberAmount);
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    if (is_number_amex_valid(numbers, numberAmount) == 0)
    {
        printf("AMEX\n");
        return 0;
    }
    if (is_number_visa_valid(numbers, numberAmount) == 0)
    {
        printf("VISA\n");
        return 0;
    }
    if (is_number_mastercard_valid(numbers, numberAmount) == 0)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    printf("INVALID\n");
    return 0;
}

// Se o número for válido irá retornar 0, se não irá retornar 1
int is_number_valid(int numberAmount)
{
    if (numberAmount < 13 || numberAmount == 14 || numberAmount > 16)
    {
        return 1;
    }
    return 0;
}

// Se o número for válido irá retornar 0, se não irá retornar 1
int is_number_amex_valid(int numbers[], int numberAmount)
{
    if (numbers[numberAmount - 1] == 3 &&
        (numbers[numberAmount - 2] == 4 || numbers[numberAmount - 2] == 7))
    {
        return 0;
    }
    return 1;
}

// Se o número for válido irá retornar 0, se não irá retornar 1
int is_number_visa_valid(int numbers[], int numberAmount)
{
    if (numbers[numberAmount - 1] == 4)
    {
        return 0;
    }
    return 1;
}

// Se o número for válido irá retornar 0, se não irá retornar 1
int is_number_mastercard_valid(int numbers[], int numberAmount)
{
    if (numbers[numberAmount - 1] == 5 &&
        (numbers[numberAmount - 2] == 1 || numbers[numberAmount - 2] == 2 ||
         numbers[numberAmount - 2] == 3 || numbers[numberAmount - 2] == 4 ||
         numbers[numberAmount - 2] == 5))
    {
        return 0;
    }
    return 1;
}

int sum_card_number(int numbers[], int numberAmount)
{
    int sum = 0;
    for (int i = 0; i < numberAmount; i++)
    {
        if (i % 2 == 0)
        {
            sum += numbers[i];
        }
        else
        {
            int doubled = numbers[i] * 2;
            sum += doubled / 10 + doubled % 10;
        }
    }
    return sum;
}
