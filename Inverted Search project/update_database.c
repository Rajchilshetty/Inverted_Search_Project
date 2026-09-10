#include "inverted_search.h"

int delete_element(Slist **head, char *filename)
{
    // Check whether the linked list is empty
    if (*head == NULL)
    {
        return FAILURE;
    }

    // Initialize current and previous pointers
    Slist *temp = *head;
    Slist *prev = NULL;

    // Traverse the linked list
    while (temp != NULL)
    {
        // Compare the filename with the current node
        if (strcmp(temp->str, filename) == 0)
        {
            // Check whether the node to be deleted is the head node
            if (prev == NULL)
            {
                *head = temp->link;
            }
            else
            {
                // Update the previous node link
                prev->link = temp->link;
            }

            // Free the deleted node
            free(temp);

            return SUCCESS;
        }

        // Move to the next node
        prev = temp;
        temp = temp->link;
    }

    // Return failure if the filename is not found
    return FAILURE;
}

int update_database(hash_node arr[], Slist **head)
{
    char filename[100];

    // Read the database filename from the user
    printf("Enter the database file (.txt):\n");
    scanf("%s", filename);

    // Validate the file extension
    if (strstr(filename, ".txt") == NULL)
    {
        printf("Error: Enter a valid .txt file\n");
        return FAILURE;
    }

    // Open the database file in read mode
    FILE *fp = fopen(filename, "r");

    // Check whether the file is opened successfully
    if (fp == NULL)
    {
        printf("DATABASE file not found or empty\n");
        return FAILURE;
    }

    char word[50];
    int index, filecount;

    // Read the first character of the file
    char word1 = getc(fp);

    // Move to the second last character
    fseek(fp, -2, SEEK_END);

    // Read the last '#' character
    char word2 = getc(fp);

    // Validate the database file format
    if (word1 != '#' || word2 != '#')
    {
        printf("Entered file is NOT a valid DATABASE file\n");
        fclose(fp);
        return FAILURE;
    }

    // Reset the file pointer to the beginning
    fseek(fp, 0, SEEK_SET);

    // Read each database entry
    while (fscanf(fp, "#%d;%[^;];%d;", &index, word, &filecount) == 3)
    {
        printf("Index: %d, Word: %s, Filecount: %d\n",
               index, word, filecount);

        // Read all files associated with the current word
        for (int i = 0; i < filecount; i++)
        {
            char file_name[100];
            int word_count;

            // Read the filename and word count
            if (fscanf(fp, "%[^;];%d;", file_name, &word_count) != 2 ||
                file_name[0] == '#')
            {
                break;
            }

            // Remove the filename from the linked list if already present
            delete_element(head, file_name);

            // Point to the first main node
            main_node *main_temp = arr[index].link;
            main_node *found = NULL;

            // Search for the word in the main node list
            while (main_temp)
            {
                if (strcmp(main_temp->word, word) == 0)
                {
                    found = main_temp;
                    break;
                }

                main_temp = main_temp->main_link;
            }

            // Create a new main node if the word is not found
            if (found == NULL)
            {
                main_node *new_main = malloc(sizeof(main_node));

                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->sub_link = NULL;

                new_main->main_link = arr[index].link;
                arr[index].link = new_main;

                found = new_main;
            }
            else
            {
                // Increment the file count if the word already exists
                found->file_count++;
            }

            // Create a new sub node
            sub_node *new_sub = malloc(sizeof(sub_node));

            // Initialize the sub node
            strcpy(new_sub->filename, file_name);
            new_sub->word_count = word_count;

            // Insert the sub node
            new_sub->link = found->sub_link;
            found->sub_link = new_sub;
        }

        // Skip the remaining characters until the next line
        int ch;
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
    }

    // Close the database file
    fclose(fp);

    return SUCCESS;
}


