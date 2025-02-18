import csv
from sys import argv


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    with open(argv[1], "r") as file:
        reader = csv.reader(file)
        dnas = dict.fromkeys(next(reader)[1:], 0)

    with open(argv[2], "r") as file2:
        sequence = file2.read()

    for dna in dnas:
        dnas[dna] = longest_match(sequence, dna)

    with open(argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            if all(int(row[dna]) == dnas[dna] for dna in dnas):
                print(row["name"])
                return

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
