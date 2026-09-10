#include "inverted_search.h"

void create_database(Slist *head, hash_node arr[])
{
    Slist *temp = head;

    // Traverse the file list until it reaches NULL
    while (temp != NULL)
    {
        // Open the current file in read mode
        FILE *fp = fopen(temp->str, "r");

        // Check whether the file is opened successfully
        if (fp == NULL)
        {
            printf("%s file could not be opened\n", temp->str);

            // Move to the next file
            temp = temp->link;
            continue;
        }

        char word[50];

        // Read each word from the file until EOF
        while (fscanf(fp, "%s", word) != EOF)
        {
            printf("%s\n", word);

            int index;
            char first = word[0];

            // Check whether the first character is an alphabet
            if (isalpha(first))
            {
                // Calculate hash index for a-z (0-25)
                index = tolower(first) % 97;
            }
            else
            {
                // Assign index 26 for special characters and numbers
                index = 26;
            }

            // Validate the calculated index
            if (index < 0 || index > 26)
            {
                printf("Invalid index for word %s\n", word);
                continue;
            }

            // Case 1: Hash table index is empty
            if (arr[index].link == NULL)
            {
                // Create a new main node
                main_node *new_main = malloc(sizeof(main_node));

                // Create a new sub node
                sub_node *new_sub = malloc(sizeof(sub_node));

                // Initialize the main node
                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->main_link = NULL;

                // Initialize the sub node
                strcpy(new_sub->filename, temp->str);
                new_sub->word_count = 1;
                new_sub->link = NULL;

                // Link the sub node to the main node
                new_main->sub_link = new_sub;

                // Insert the main node into the hash table
                arr[index].link = new_main;
            }
            else
            {
                main_node *n_pointer = arr[index].link;
                int found_word = 0;

                // Traverse the main node list
                while (n_pointer != NULL)
                {
                    // Check whether the word already exists
                    if (strcmp(n_pointer->word, word) == 0)
                    {
                        found_word = 1;

                        sub_node *s_pointer = n_pointer->sub_link;
                        int found_file = 0;

                        // Traverse the sub node list
                        while (s_pointer != NULL)
                        {
                            // Check whether the file already exists
                            if (strcmp(s_pointer->filename, temp->str) == 0)
                            {
                                // Increment the word count
                                s_pointer->word_count++;
                                found_file = 1;
                                break;
                            }

                            // Move to the next sub node
                            s_pointer = s_pointer->link;
                        }

                        // Case 2: Word exists but file is new
                        if (!found_file)
                        {
                            // Create a new sub node
                            sub_node *new_sub = malloc(sizeof(sub_node));

                            // Initialize the new sub node
                            strcpy(new_sub->filename, temp->str);
                            new_sub->word_count = 1;
                            new_sub->link = n_pointer->sub_link;

                            // Insert the sub node
                            n_pointer->sub_link = new_sub;

                            // Increment the file count
                            n_pointer->file_count++;
                        }

                        break;
                    }

                    // Move to the next main node
                    n_pointer = n_pointer->main_link;
                }

                // Case 3: Word does not exist in the hash table
                if (!found_word)
                {
                    // Create a new main node
                    main_node *new_main = malloc(sizeof(main_node));

                    // Create a new sub node
                    sub_node *new_sub = malloc(sizeof(sub_node));

                    // Initialize the main node
                    strcpy(new_main->word, word);
                    new_main->file_count = 1;
                    new_main->main_link = arr[index].link;

                    // Initialize the sub node
                    strcpy(new_sub->filename, temp->str);
                    new_sub->word_count = 1;
                    new_sub->link = NULL;

                    // Link the sub node to the main node
                    new_main->sub_link = new_sub;

                    // Insert the main node into the hash table
                    arr[index].link = new_main;
                }
            }
        }

        // Close the current file
        fclose(fp);

        // Move to the next file in the list
        temp = temp->link;
    }
}