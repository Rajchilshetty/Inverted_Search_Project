#include "inverted_search.h"

void print_list(Slist *head)
{
    // Check whether the linked list is empty
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
        return;
    }

    // Display the heading for the list of valid files
    printf("List of valid files:\n");

    // Traverse the linked list until it reaches NULL
    while (head)
    {
        // Print the filename stored in the current node
        printf("%s\n", head->str);

        // Move to the next node
        head = head->link;
    }

    // Print a new line after displaying all filenames
    printf("\n");
}

