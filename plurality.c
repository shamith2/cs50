#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; ++i)
    {
        // linear search for invalid candidate name
        string cand_name = candidates[i].name;
        if (strcmp(cand_name, name) == 0)
        {
            ++candidates[i].votes;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int max_val = candidates[0].votes;   // max vote value
    string names[candidate_count];  // array of winners
    names[0] = candidates[0].name; // name of candidate with max vote value

    // linear search to find max vote value
    for (int i = 1; i < candidate_count; ++i)
    {
        int vote_count = candidates[i].votes;
        string name = candidates[i].name;

        if (vote_count > max_val)
        {
            max_val = vote_count;
            names[0] = name;
        }
    }

    // index for multiple winner
    int j = 1;

    // linear search for finding multiple winners
    for (int i = 0; i < candidate_count; ++i)
    {
        int vote_count = candidates[i].votes;
        string name = candidates[i].name;

        if (vote_count == max_val && names[0] != name)
        {
            names[j] = name;
            ++j;
        }
    }

    // error check
    names[j] = NULL;

    // declare winner
    for (int i = 0; names[i] != NULL; ++i)
    {
        printf("%s\n", names[i]);
    }

    return;
}
