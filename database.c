
#include "header.h"
//input validation function
int input_validate(int argc,char *argv[],ll **head)
{
    if(argc < 2)
    {
        printf(RED"No input file is given\n"RESET);
        return failure;

    }
    for(int i=1;argv[i]!=NULL;i++)
    {
        char *ptr;

        if(ptr=strstr(argv[i],".txt"))
        {
            if(*(ptr+4)!='\0')
            {
                printf("please enter .txt files\n");
                continue;
            }
        }
        else
        {
               printf("please enter .txt files\n");
                continue;
        }
        FILE *fptr=fopen(argv[i],"r");
        if(fptr==NULL)
        {
            printf("file doesn't exist\n");
            continue;
        }
        fseek(fptr,0,SEEK_END);
        if(ftell(fptr)==0)
        {
            printf("file is empty\n");
            continue;
        }
        fclose(fptr);

        insert_fname(head,argv[i]);
    }
    return success;



}
//insert file nae to linked list

int insert_fname(ll **head,char *str)
{
    ll *new=malloc(sizeof(ll));
    if(new==NULL){
        return failure;
    }
    strcpy(new->str,str);
    new->link=NULL;
    if(*head==NULL)
    {
        *head=new;
        return success;
    }
    else{
        ll *temp=*head;
        while(temp->link)
        {
            temp=temp->link;
        }
        temp->link=new;
        return success;

    }


}

//creating the datbase using the hashmap
int create_database(hash *hash_t,ll **head)
{
    ll *temp=*head;
    int stat=0;
    int idx=0;
    for(;temp!=NULL;temp=temp->link)
    {
        FILE *fptr=fopen(temp->str,"r");
        char name[20];
        while(fscanf(fptr,"%s",name)!=EOF)
        {
            if(name[0] >='A' && name[0]<='Z')
            idx=name[0]-'A';
            else if(name[0] >='a' && name[0]<='z')
            idx=name[0]-'a';
            else if(name[0] >='0' && name[0]<='9')
            idx=26;
            else{
                idx=27;
            }
            if(hash_t[idx].link==NULL)
            {
                m_node *m_new=malloc(sizeof(m_node));
                if(m_new==NULL)
                {
                    printf("main node not created\n");
                    return failure;
                }
                strcpy(m_new->word,name);
                m_new->f_count=1;
                s_node *s_new=malloc(sizeof(s_node));
                if(s_new==NULL)
                {
                    printf("subnode not created\n");
                    return failure;
                }
                m_new->s_link=s_new;
                s_new->wordcount=1;
                strcpy(s_new->f_name,temp->str);
                s_new->s_link=NULL;
                m_new->m_link=NULL;
                hash_t[idx].link=m_new;

            }
            else{
                m_node *m_temp=hash_t[idx].link;
                m_node *m_prev=NULL;
                while(m_temp )
                {
                    if(strcmp(m_temp->word,name)==0)
                    {
                        s_node *s_temp=m_temp->s_link;
                        s_node *s_prev=NULL;
                        while(s_temp!=NULL)
                        {
                            if(strcmp(temp->str,s_temp->f_name)==0)
                            {
                                s_temp->wordcount=s_temp->wordcount+1;
                                stat=0;
                                break;
                            }
                            s_prev = s_temp;
                            s_temp = s_temp -> s_link;
                        }
                        if(s_temp==NULL )
                        {
                            s_node *s_new=malloc(sizeof(s_node));
                            if(s_new==NULL)
                            {
                                printf("subnode not created\n");
                                return failure;
                            }
                            s_new->wordcount=1;
                            strcpy(s_new->f_name,temp->str);
                            s_prev->s_link=s_new;
                            m_temp->f_count++;
                            stat=0;
                        }
                    }
                    m_temp=m_temp->m_link;
                }
                if(m_temp==NULL && stat )
                {
                    m_node *m_new=malloc(sizeof(m_node));
                    if(m_new==NULL)
                    {
                        printf("main node not created \n");
                        return failure;

                    }
                    strcpy(m_new->word,name);
                    m_new->f_count=1;
                    s_node *s_new=malloc(sizeof(s_node));
                    if(s_new==NULL)
                    {
                        printf("sub node not created \n");
                        return failure;
                    }
                    m_new->s_link=s_new;
                    s_new->wordcount=1;
                    strcpy(s_new->f_name,temp->str);
                    s_new->s_link=NULL;
                    m_new->m_link=NULL;

                    m_prev->m_link=m_new;
                }

            }


        }
    }

}

//function to printing the database
int print_database(hash *hash_t)
{
    printf("-------------------------------------------\n");
        printf(GREEN"WORD      FILENAME    COUNT     \n"RESET);
        printf("-------------------------------------------\n");
    for(int i=0;i<28;i++)
    {
        
        m_node *temp=hash_t[i].link;
         
        
        while(temp!=NULL)
        {
            int count=0;
            //printf("%s ",temp->word);
            
             s_node *s_temp=temp->s_link;
             
            while(s_temp!=NULL)
            {

                printf("-------------------------------------------\n");
                printf("%-10s ",temp->word);
                if(count==0)
                {
               printf("%-12s %-10d\n",s_temp->f_name,s_temp->wordcount);

                }
                else{
                 printf("%-12s %-10d\n",s_temp->f_name,s_temp->wordcount);
                 }

                s_temp=s_temp->s_link;
                count=1;
                printf("--------------------------------------------\n");

            }
             temp=temp->m_link;
        }
    

    }


}

//function to searching database
void search_database(hash *hash_t)
{
    printf(GREEN"enter the data to search\n"RESET);
    char str[20];
    __fpurge(stdin);
    scanf("%[^\n]",str);
    int i;
    if(str[0]>='A' && str[0]<='Z') i=str[0]-'A';
    else if(str[0]>='a' && str[0]<='z') i=str[0]-'a';
    else if(str[0]>='0' && str[0]<='9') i=26;
    else i=27;


    m_node *m_temp=hash_t[i].link;
    while(m_temp!=NULL)
    {
        if(strcmp(m_temp->word,str)==0)
        {
            printf(YELLOW"%-12s %-10d\n"RESET,m_temp->word,m_temp->f_count);

            s_node *s_temp=m_temp->s_link;
             printf("-------------------------------------------\n");
            printf(GREEN"FILENAME    COUNT     \n"RESET);
            printf("-------------------------------------------\n");
            

            while(s_temp !=NULL)
            {
                printf("%-12s %-10d\n",s_temp->f_name,s_temp->wordcount);
                s_temp=s_temp->s_link;
            }
            printf("-------------------------------------------\n");
            break;
        }
        m_temp=m_temp->m_link;
        
       
    }
    
    if(m_temp==NULL)
    {
        printf("======================================\n");
        printf(RED"word %s is not present\n"RESET,str);
        
        printf("======================================\n");

    }
    

    
}

//function to save database
void save_database(hash *hash_t)
{
    char str[20];
    int count;

    int ch;
    while((ch=getchar())!='\n' && ch!=EOF);

    printf(YELLOW"Enter the file name to store:\n "RESET);
    scanf("%[^\n]", str);

    char *ptr = strstr(str, ".txt");
    if(ptr == NULL || *(ptr+4) != '\0')
    {
        printf("======================================\n");
        printf(YELLOW"Please give a .txt file\n"RESET);
        printf("======================================\n");
        return;
    }

    FILE *fptr = fopen(str, "w");
    if(fptr == NULL)
    {
        printf("======================================\n");
        perror(RED"File open failed"RESET);
        printf("======================================\n");
        return;
    }

    for(int i = 0; i < 28; i++)
    {
        m_node *m_temp = hash_t[i].link;

        while(m_temp != NULL)
        {
            fprintf(fptr, "%d;WORD:%s;FILE COUNT:%d\n", 
                    count+1, m_temp->word, m_temp->f_count);
            fprintf(fptr,"-------------------------------\n");
            count++;

            s_node *s_temp = m_temp->s_link;
           


            while(s_temp != NULL)
            {
                fprintf(fptr, "FILE NAME:%s;WORD COUNT:%d\n", 
                        s_temp->f_name, s_temp->wordcount);

                s_temp = s_temp->s_link;
            }
            

            m_temp = m_temp->m_link;
             fprintf(fptr,"-------------------------------\n");
        }
    }

    fclose(fptr);
    printf("======================================\n");
    printf(GREEN"Database saved successfully into %s\n"RESET, str);
    printf("======================================\n");
}


//function to updating database
int update_database(char* str,ll** head ,ll** temp)
{
    
            if(strstr(str,".txt")==NULL)
            {
                printf("======================================\n");
                printf(RED"Wrong file extension \n"RESET);
                printf("======================================\n");
                return 0;
            }

            FILE *fptr=fopen(str,"r");
            if(fptr==NULL)
            {
                printf("======================================\n");
                printf(RED"%s is not present in the directory \n"RESET,str);
                printf("======================================\n");
                return 0;
            }
            fseek(fptr,0,SEEK_END);
            if(ftell(fptr)==0)
            {
                printf("======================================\n");
                printf(RED"%s is empty \n"RESET,str);
                printf("======================================\n");
                return 0;
            }
            rewind(fptr);
            fclose(fptr);

            int res=insert_last(head,str);
            if(res!=success)
            {
                if(res==full)
                {
                   
                    return 0;
                }
                else if(res==duplicate)
                {
                    printf("======================================\n");
                  printf(RED"%s this file is already added in directory this one is Duplicate of that \n"RESET,str);
                  printf("======================================\n");
                }
                return 0;

            }
            insert_last(temp,str);
            return 1;

}
//insert last for linked list
int insert_last(ll **head,const char*str)
{

    ll *new=malloc(sizeof(ll));
     if(new==NULL) 
    {
        printf("======================================\n");
        printf(RED"Heap memory is full \n"RESET);
        printf("======================================\n");
       return full;
    }
    new->link=NULL;
    strcpy(new->str,str);

        if(*head==NULL)
        {
           
            *head=new;
            return success;
        }

        ll *temp=*head;

        while(temp->link!=NULL)
        {
            if(strcmp(temp->str, str) == 0)
            {
                free(new);
                return duplicate;
            }
            else
            {
              temp=temp->link;
            }
        }
        
           if(strcmp(temp->str, str) == 0)
            {      
                 free(new);
                return duplicate;
            }
            else  
            {
              temp->link=new;
                return success;
            }

        
}


