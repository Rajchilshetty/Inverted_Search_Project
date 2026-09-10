#include "inverted_search.h"

void save_database(hash_node arr[])
{
    char file[100];

    // Read the filename from the user to save the database
    printf("Enter the filename to save the database (.txt): ");
    scanf("%s", file);

    // Check whether the filename has a .txt extension
    if (strstr(file, ".txt"))
    {
        // Open the file in write mode
        FILE *fp = fopen(file, "w");

        // Check whether the file is opened successfully
        if (fp == NULL)
        {
            printf("Error: File is not opened\n");
            return;
        }

        // Traverse all hash table indexes
        for (int i = 0; i < 27; i++)
        {
            // Check whether the hash index contains any main node
            if (arr[i].link != NULL)
            {
                // Point to the first main node
                main_node *savemain_temp = arr[i].link;

                // Traverse the main node list
                while (savemain_temp != NULL)
                {
                    // Write the index, word, and file count to the file
                    fprintf(fp, "#%d;%s;%d;", i,
                            savemain_temp->word,
                            savemain_temp->file_count);

                    // Point to the first sub node
                    sub_node *savesub_temp = savemain_temp->sub_link;

                    // Traverse the sub node list
                    while (savesub_temp != NULL)
                    {
                        // Write the filename and word count
                        fprintf(fp, "%s;%d;",
                                savesub_temp->filename,
                                savesub_temp->word_count);

                        // Move to the next sub node
                        savesub_temp = savesub_temp->link;
                    }

                    // Mark the end of one database entry
                    fprintf(fp, "#\n");

                    // Move to the next main node
                    savemain_temp = savemain_temp->main_link;
                }
            }
        }

        // Close the file
        fclose(fp);

        printf("%s Saved successfully into the database\n", file);
    }
    else
    {
        // Display an error message for an invalid filename
        printf("Invalid filename\n");
    }
}

