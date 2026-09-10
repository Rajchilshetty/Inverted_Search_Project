#include "inverted_search.h"

// Function to check whether the given filename already exists in the linked list
int is_duplicate(Slist *head, const char *filename)
{
    while (head)
    {
        if (strcmp(head->str, filename) == 0)
        {
            return 1;
        }

        head = head->link;
    }

    return 0;
}

// Function to create a new node and add the filename to the linked list
Slist* add_to_list(Slist *head, const char *filename)
{
    // Allocate memory for a new node
    Slist *new = malloc(sizeof(Slist));

    // Check whether memory allocation is successful
    if (new == NULL)
    {
        return NULL;
    }

    // Copy the filename into the new node
    strcpy(new->str, filename);

    // Insert the node at the beginning of the list
    new->link = head;

    return new;
}

int main(int argc, char *argv[])
{
    Slist *head = NULL;

    // Check whether the required command-line arguments are provided
    if (argc < 2)
    {
        printf("USE: ./a.out <file1.txt> <file2.txt>...\n");
        return FAILURE;
    }

    // Traverse all command-line arguments
    for (int i = 1; i < argc; i++)
    {
        char *filename = argv[i];

        // Check whether the file has a .txt extension
        if (!strstr(filename, ".txt"))
        {
            printf("Error: The file does not have a .txt extension\n");
            continue;
        }

        // Open the file in read mode
        FILE *fp = fopen(filename, "r");

        // Check whether the file is opened successfully
        if (fp == NULL)
        {
            printf("%s file is not opened\n", filename);
            continue;
        }

        // Check whether the file is empty
        fseek(fp, 0, SEEK_END);

        if (ftell(fp) == 0)
        {
            printf("%s file is empty\n", filename);
            fclose(fp);
            continue;
        }

        // Close the file
        fclose(fp);

        // Check whether the filename is already present
        if (is_duplicate(head, filename))
        {
            printf("The file name already exists: %s\n", filename);
            continue;
        }

        // Add the filename to the linked list
        Slist *temp = add_to_list(head, filename);

        // Check whether node creation is successful
        if (temp == NULL)
        {
            printf("Error: Memory allocation failed for file\n");
            continue;
        }

        // Update the head pointer
        head = temp;

        printf("%s File added successfully\n", filename);
    }

    // Display all valid filenames
    print_list(head);

    // Create and initialize the hash table
    hash_node arr[27] = {0};

    // Flag:
    // 0  -> Only create operation is allowed
    // 1  -> Only update operation is allowed
    // -1 -> Create and update are restricted
    int flag = 0;

    // Display the menu continuously
    while (1)
    {
        int choice;

        printf("1. Create database\n");
        printf("2. Display database\n");
        printf("3. Save database\n");
        printf("4. Search database\n");
        printf("5. Update database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            // Create the database
            case 1:
                if (flag == 0)
                {
                    create_database(head, arr);
                    printf("Database Created Successfully\n");
                    flag = -1;
                }
                else if (flag == 1)
                {
                    if (head != NULL)
                    {
                        create_database(head, arr);
                        printf("Database Created for new files\n");
                        head = NULL;
                    }
                    else
                    {
                        printf("INFO: No new files to create database.\n");
                    }
                }
                else
                {
                    printf("INFO: Create already done. Not allowed again.\n");
                }
                break;

            // Display the database
            case 2:
                display_database(arr);
                printf("Database displayed successfully\n");
                break;

            // Save the database into a file
            case 3:
                save_database(arr);
                break;

            // Search a word in the database
            case 4:
                search_database(arr);
                break;

            // Update the database from a backup file
            case 5:
                if (flag == 0)
                {
                    int ret = update_database(arr, &head);

                    if (ret == SUCCESS)
                    {
                        flag = 1;
                    }
                }
                else if (flag == 1)
                {
                    printf("INFO: Update already done. Not allowed again.\n");
                }
                else
                {
                    printf("INFO: Update not allowed after create.\n");
                }
                break;

            // Exit the program
            case 6:
                printf("Exited the program.\n");
                return SUCCESS;

            // Handle invalid menu choice
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return SUCCESS;
}

