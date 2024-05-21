from cs50 import get_string

COMPANIES = {
    "AMEX": ["34", "37"],
    "VISA": ["4"],
    "MASTERCARD": ["51", "52", "53", "54", "55"]
}


def main():
    card_number = get_string("Number: ")
    validate_card_number(card_number)


def validate_card_number(card_number):
    size = len(card_number)
    if size < 13 or size == 14 or size > 16:
        print("INVALID")
        return
    sum = 0
    for index, number in enumerate(card_number[::-1]):
        digit = int(number)
        if index % 2 == 0:
            sum += digit
        else:
            sum += 2 * digit if digit < 5 else 2 * digit - 9
    if sum % 10 != 0:
        print("INVALID")
        return
    for company, prefixes in COMPANIES.items():
        if any(card_number.startswith(prefix) for prefix in prefixes):
            print(company)
            return
    print("INVALID")


main()
