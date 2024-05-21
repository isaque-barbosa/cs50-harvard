from cs50 import get_float

coins = [25, 10, 5, 1]


def main():
    change = int(get_valid_float() * 100)
    change_coins = 0
    for coin in coins:
        if change >= coin:
            num_coins = change // coin
            change -= num_coins * coin
            change_coins += num_coins
    print(change_coins)


def get_valid_float():
    while True:
        change = get_float("Change owed: ")
        if change > 0:
            break
    return change


main()
