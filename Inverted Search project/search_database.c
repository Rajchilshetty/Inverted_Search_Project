#include "inverted_search.h"

void search_database(hash_node arr[])
{
    char word[50];

    // Read the word to be searched
    printf("Enter the word: ");
    scanf("%s", word);

    int ind;
    char first = word[0];

    // Check whether the first character is an alphabet
    if (isalpha(first))
    {
        // Calculate the hash index for a-z or A-Z (0-25)
        ind = tolower(first) % 97;
    }
    else
    {
        // Assign index 26 for non-alphabetic characters
        ind = 26;
    }

    // Point to the first main node of the corresponding hash index
    main_node *search_temp1 = arr[ind].link;
    int found = 0;

    // Traverse the main node list
    while (search_temp1 != NULL)
    {
        // Compare the entered word with the current word
        if (strcmp(search_temp1->word, word) == 0)
        {
            found = 1;

            // Display the matched word
            printf("Word: %s\n", word);

            // Display the number of files containing the word
            printf("Found in %d file(s):\n", search_temp1->file_count);
            printf("---------------------------------\n");

            // Point to the first sub node
            sub_node *search_temp2 = search_temp1->sub_link;

            // Traverse the sub node list
            while (search_temp2 != NULL)
            {
                // Display the filename and word occurrence count
                printf("%s : %d time(s)\n",
                       search_temp2->filename,
                       search_temp2->word_count);

                printf("-----------------------------\n");

                // Move to the next sub node
                search_temp2 = search_temp2->link;
            }

            // Exit after finding the word
            break;
        }

        // Move to the next main node
        search_temp1 = search_temp1->main_link;
    }

    // Display a message if the word is not found
    if (!found)
    {
        printf("Word '%s' not found in the database.\n", word);
    }
}

