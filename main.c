/*Name:Naveen B
Project Name:Inverted search
description:The Inverted Search Project is a file-based text searching system that enables fast and efficient
            searching of words across multiple text files. Instead of scanning each file every time a search is performed,
            this project builds an inverted index, which maps each unique word to the list of files in which it appears, 
            along with its frequency.This project is implemented using C programming and data structures like Hash Tables 
            and Linked Lists, making it highly efficient in terms of time complexity and memory usage.



*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include <stdio_ext.h>

#include"header.h"


int main(int argc,char **argv)
{
    ll *head=NULL;
    
    if(input_validate(argc,argv,&head)==success)//validating inputs
    {
        printf(GREEN"inputs validated successfully\n"RESET);
    }
    else{
        return 0;
    }

    hash hash_t[28];//hash table creation

    for(int i=0;i<28;i++)
    {
        hash_t[i].idx=-1;
        hash_t[i].link=NULL;
    }

    int option;
    int create=0;
    while(1)
    {
          
        printf("➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖\n");
        printf(MAGENTA"1. create database\n"RESET);
        printf(MAGENTA"2.display database\n"RESET);
        printf(MAGENTA"3.search database\n"RESET);
        printf(MAGENTA"4.update database\n"RESET);
        printf(MAGENTA"5.save database\n"RESET);
        printf(MAGENTA"6.exit database\n"RESET);
          printf("➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖\n");

        printf(CYAN"enter the choice\n"RESET);
    
        __fpurge(stdin);
        if(scanf(" %d",&option)!=1)
        {
            printf("==================================================\n");
            printf(RED"invalid input\n"RESET);
            printf("==================================================\n");
            continue;
        }
        switch(option)
        {
            case 1://create database
            {
                if(create ==1)
                {
                    printf("==================================================\n");
                    printf(RED"database already created\n"RESET);
                    printf("==================================================\n");
                    break;
                }
            
                 create_database(hash_t,&head);
                 create=1;
                 printf("==================================================\n");
                printf(YELLOW"database created successfully\n"RESET);
                printf("==================================================\n");
                 break;
            }

            case 2://display database
            {
                if(create==0)
                {
                    printf("==================================================\n");
                    printf(RED"databse not created\n"RESET);
                    printf("==================================================\n");
                    break;
                }
                print_database(hash_t);
                break;

            }
            case 3://search database
            {
                if(create==0)
                {
                    printf("==================================================\n");
                    printf(RED"databse not created\n"RESET);
                    printf("==================================================\n");
                    break;
                }
                search_database(hash_t);
                break;

            }
            case 4://update database
            {
                if(create==0)
                {
                    printf("==================================================\n");
                    printf(RED"databse not created\n"RESET);
                    printf("==================================================\n");
                    break;

                }
                char str[50];
                __fpurge(stdin);
                printf(YELLOW"enter the file name\n"RESET);
                scanf("%[^\n]",str);
                ll *temp=NULL;
                if(update_database(str,&head ,&temp))
                {
                    if(create_database(hash_t,&temp))
                    {
                        printf(RED"data base update failed\n"RESET);
                    }
                    else
                    {
                        printf(YELLOW"database updated successfully\n"RESET);
                    }
                }

                break;

            }
            case 5://save database
            {
                if(create==0)
                {
                    printf("==================================================\n");
                    printf(RED"database not created\n"RESET);
                    printf("==================================================\n");
                    break;
                }
                save_database(hash_t);
                break;

                
            }
           
            default:
            {
                printf("==================================================\n");
            printf(RED"enter valid input \n"RESET);
            printf("==================================================\n");
            break;

            }



        }


    }
    



}



