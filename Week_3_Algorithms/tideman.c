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
}
pair;

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
bool check_path(int line, int target);
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0) // if name on vote is a candidate
        {
            ranks[rank] = i; // update preference with candidate NUMBER!
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < (candidate_count); j++)
        {
            if (preferences[ranks[i]][ranks[j]] >= 1)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
            else
            {
                preferences[ranks[i]][ranks[j]] = 1;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair compare;
                compare.winner = i;
                compare.loser = j;
                pairs[pair_count] = compare;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pair compare;
                compare.winner = j;
                compare.loser = i;
                pairs[pair_count] = compare;
                pair_count += 1;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
      int highestDiff = preferences[pairs[i].winner][pairs[i].loser];
      int indexDiff = i;

      int j = i + 1;

      while (j < pair_count)
      {
          int currentDiff = preferences[pairs[j].winner][pairs[j].loser];
          if (currentDiff > highestDiff)
          {
              highestDiff = currentDiff;
              indexDiff = j;
          }
          j = j + 1;
      }

      if (indexDiff != i)
      {
          pair placeholder = pairs[indexDiff];
          pairs[indexDiff] = pairs[i];
          pairs[i] = placeholder;
      }
    }
}

bool check_path(int line, int target)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[line][i])
        {
            if (i == target)
            {
                return false;
            }
            else
            {
                bool newCheck = check_path(i, target);
                if (!newCheck)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        // check path starting from loser
        bool canAddPath1 = check_path(loser, winner);
        bool canAddPath2 = check_path(winner, loser);
        if (canAddPath1 && canAddPath2)
        {
            locked[winner][loser] = true;
            printf("Added!\n");
        }
    }
}


// Print the winner of the election
void print_winner(void)
{
    int winnerIndex = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        bool winner = true;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                winner = false;
                break;
            }
        }
        if (winner)
        {
            winnerIndex = j;
        }
    }
    printf("%s\n", candidates[winnerIndex]);
}

