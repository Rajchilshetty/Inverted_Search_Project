#include "inverted_search.h"

void display_database(hash_node arr[])
{
    printf("\n");

    printf("+-------+----------------------+------------+---------------------------+------------+\n");
    printf("| Index | Word                 | File Count | File Name                 | Word Count |\n");
    printf("+-------+----------------------+------------+---------------------------+------------+\n");

    // Traverse all hash indexes
    for (int i = 0; i < 27; i++)
    {
        if (arr[i].link != NULL)
        {
            main_node *main_temp = arr[i].link;

            // Traverse all main nodes
            while (main_temp != NULL)
            {
                sub_node *sub_temp = main_temp->sub_link;

                // Print each sub node as a separate row
                while (sub_temp != NULL)
                {
                    printf("| %-5d | %-20s | %-10d | %-25s | %-10d |\n",
                           i,
                           main_temp->word,
                           main_temp->file_count,
                           sub_temp->filename,
                           sub_temp->word_count);

                    sub_temp = sub_temp->link;
                }

                main_temp = main_temp->main_link;
            }
        }
    }

    printf("+-------+----------------------+------------+---------------------------+------------+\n");
}