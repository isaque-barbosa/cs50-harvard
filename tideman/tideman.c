#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int higher_preference = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (j >= candidate_count)
            {
                continue;
            }
            int lower_preference = ranks[j];
            preferences[higher_preference][lower_preference]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int max = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int move;
    do
    {
        move = 0;
        pair aux;
        for (int i = pair_count - 1; i >= 0; i--)
        {
            if (i - 1 < 0)
            {
                continue;
            }
            int current = preferences[pairs[i].winner][pairs[i].loser];
            int next = preferences[pairs[i - 1].winner][pairs[i - 1].loser];
            if (current > next)
            {
                aux = pairs[i];
                pairs[i] = pairs[i - 1];
                pairs[i - 1] = aux;
                move++;
            }
        }
    }
    while (move == 0);
    return;
}

bool cycle(int winner, int loser)
{
    // Se chegarmos ao nó inicial novamente, há um ciclo
    if (loser == winner)
    {
        return true;
    }
    // Verifique todos os nós conectados ao nó perdedor
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // Adicione o par se não criar um ciclo
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool is_anyone_locked_on_me;
    for (int i = 0; i < pair_count; i++)
    {
        is_anyone_locked_on_me = false;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[j][i])
            {
                is_anyone_locked_on_me = true;
                break;
            }
        }
        if (!is_anyone_locked_on_me)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
