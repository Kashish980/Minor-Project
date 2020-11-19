#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#define SHA256_DIGEST_LENGTH 32

struct block
{
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char Hash[SHA256_DIGEST_LENGTH];
    int blockData;
    struct block *link;
};
struct block* head=NULL;

void addBlock(int);
void verifyChain();
void alterNthBlock(int,int);
int hashCompare(unsigned char*, unsigned char*);
void hashPrinter();
unsigned char* toString(struct block);
void printBlock();
void printAllBlocks();

void addBlock(int data)
{
        //Allocate new node
        struct block* newBlock = (struct block*)malloc (sizeof(struct block));
        struct block* last = head;
        newBlock->blockData = data;
        newBlock->link = NULL;
    if(head==NULL)
    {
        head = newBlock;
        SHA256 ("",sizeof(""),head->prevHash);
        return;
    }
    while(last -> link != NULL)
        last = last->link; 
    last->link = newBlock;
    int *h=&last->blockData;
    sprintf(last->Hash, "%d", *h);
    SHA256(last->Hash,sizeof(last->Hash),newBlock->prevHash);
}

void verifyChain()
{
    if(head==NULL)
    {
        printf("Hey, Blockchain is empty! Please try after adding some block !\n");
        return;
    }
    struct block *curr = head -> link, *prev = head;
    int count =1;
    int flag=0;
    while(curr!=NULL)
    {
        printf("\n%d.\t[%d]\t",count++, curr-> blockData);
        hashPrinter(SHA256(toString(*prev),sizeof(*prev),NULL),SHA256_DIGEST_LENGTH);
 	printf(" - ");
        hashPrinter(curr -> prevHash, SHA256_DIGEST_LENGTH);
        if(hashCompare(SHA256(toString(*prev),sizeof(*prev),NULL),curr->prevHash))
            printf("\n Block is valid ! \n");
        else{
            printf("\n Blockchain is not valid !");
            flag=1;
            }
       prev=curr;
       curr=curr->link;
    }
    if(flag==0)
     printf("\n ***** Kashish's blockchain is validated and verified! *****");
     else
     printf("\n Sorry, blockchain is not valid!");
}

unsigned char* toString(struct block b)
{
    unsigned char *str=malloc(sizeof(unsigned char)*sizeof(b));
    memcpy(str,&b,sizeof(b));
    return str;
}

void hashPrinter(unsigned char hash[], int length)
{
    for(int i=0; i<length; i++)
        printf("%02x",hash[i]);
}

int hashCompare(unsigned char *str1, unsigned char *str2)
{
    for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
        if(str1[i]==str2[i])
            return 0;
    return 1;
}

void printBlock(struct block *b)
{
    printf("%p\t",b);                                     //address of this particular block
    hashPrinter(b->prevHash, sizeof(b->prevHash));        //hash value of previous block hash
    printf("\t[%d]\t",b->blockData);                      //data stored
    printf("%p\n",b->link);
}

void printAllBlocks()
{
    struct block *curr=head;
    int count=0;
    while(curr)
    {
        printBlock(curr);
        curr = curr->link;
    }
}

void main()
{
    printf("\n        ******************************************************************************\n");
    printf("        !!!                                                                        !!!\n");
    printf("        !!!  Minor I Project : Implementation of Blockchain Network in C language  !!!\n");
    printf("        !!!                                                                        !!!\n");
    printf("        ******************************************************************************\n\n");
//    printf
    int c,n,r;

    while(1)
    {   printf("\n\n ENTER YOUR CHOICE \n1: Add a new block Block \n2: Add n numbers of blocks in chain \n3: Print all blocks in Blockchain \n4: Check Validity of Blockchain \n5: EXIT\n\n");
        printf("\n\nChoice: ");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                printf("Enter the numerical data you want in your Block: ");
                scanf("%d",&n);
                addBlock(n);
                printf("1 Block is added in Blockchain successfully");
                break;
            case 2:
                printf("How many Blocks you want to add in chain? : ");
                scanf("%d",&n);
                for(int i=0;i<n;i++)
                {
                    r=rand()%(n*10);
                    printf("Entering random numerical data (by rand()function) in this Block: %d\n",r);
                    addBlock(r);
                }
                printf("%d Blocks are added in Blockchain Successfully",n);
                break;
           case 3: 
                printf("\nThese are the Parameters in a Block of our Blockchain : \n");
                printAllBlocks();
                break;
            case 4:
                verifyChain();
                break;
            case 5:
                printf("FINALLY DONE!  \n **All your choices were accepted. Thankyou for your patience** \n\n -KASHISH SRIVASTAVA\n R134218079\n 500067405 \n CSF-B2\n");
                exit(1);
            default:
                printf("Wrong choice !\nPlease try again\n");
                break;
        }
    }
}
