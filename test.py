def main():
    N = get_positive_int("")
    elements = input("")
    elements = get_numbers_from_string(elements)

    min_operations = find_min_operations(elements)
    print(min_operations)

def find_min_operations(arr):
    n = len(arr)
    i, j = 0, n - 1
    operations = 0

    while i < j:
        if arr[i] == arr[j]:
            i += 1
            j -= 1
        elif arr[i] < arr[j]:
            arr[i + 1] += arr[i]
            i += 1
            operations += 1
        else:
            arr[j - 1] += arr[j]
            j -= 1
            operations += 1

    return operations

def get_positive_int(message):
    while True:
        number = input(message)
        if number is not None and number.isdigit():
            number = int(number)
            if 1 <= number <= 106:
                return number

def get_numbers_from_string(numbers):
    tamanhos = []
    for number in numbers.split(" "):
        if number is not None and number.isdigit():
            number = int(number)
            if 1 <= number <= 109:
                tamanhos.append(number)
    return tamanhos

main()
