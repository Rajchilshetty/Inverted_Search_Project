#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#define SUCCESS 0
#define FAILURE -1
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct node
{
	char str[30];
	struct node *link;
}Slist;
// Node for file list in database 
typedef struct sub_node
{
    int word_count;
    char filename[30];
    struct sub_node *link;
}sub_node;
// Node for word list
typedef struct main_node
{
    int file_count;
    char word[30];
    struct main_node *main_link; 
    struct sub_node *sub_link;
} main_node;
//node for hashtable
typedef struct hash_node
{
    unsigned int key;
    struct main_node *link;
}hash_node;

/* Include the prototypes here */
void create_database(Slist *head, hash_node arr[]);
void display_database(hash_node arr[]);
void save_database(hash_node arr[]);
void search_database(hash_node arr[]);
int update_database(hash_node arr[],Slist **head);
void exit_program(Slist *head, hash_node arr[]);
void print_list(Slist *head);


#endif  // INVERTED_SEARCH_H