
#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdio_ext.h>

#define success 0
#define failure 1
#define duplicate -1
#define full 2

#define RED         "\033[1;3;31m"
#define GREEN       "\033[1;32m"
#define YELLOW      "\033[0;3;33m"
#define BLUE        "\033[1;3;34m"
#define MAGENTA     "\033[1;3;35m"
#define CYAN        "\033[1;3;36m"
#define RESET       "\033[0m"



typedef struct S_node
{
    int wordcount;
    char f_name[20];
    struct S_node *s_link;

}s_node;
typedef struct M_node
{
    char word[20];
    int f_count;
    s_node *s_link;
    struct M_node *m_link;

}m_node;
typedef struct Hash
{
    int idx;
    m_node *link;

}hash;

typedef struct LL
{
    char str[20];

    struct LL *link;
}ll;
int input_validate(int argc,char *argv[],ll **head);

int insert_fname(ll **head,char *str);

int create_database(hash *hash_t,ll **head);

int print_database(hash *hash_t);

void search_database(hash *hash_t);

void save_database(hash *hash_t);

int update_database(char*,ll** ,ll**);

int insert_last(ll**,const char*);






#endif

