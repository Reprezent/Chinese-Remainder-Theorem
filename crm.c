#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


typedef struct dll
{
    struct dll* next;
    struct dll* prev;
    unsigned long long val;
} DLL;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    unsigned long long temp;
    while(b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

DLL* newDLL()
{
    DLL* a = malloc(sizeof(struct dll));
    a->next = a;
    a->prev = a;
    return a;
}

void append(DLL* pos, unsigned long long val)
{
    DLL* temp = newDLL();
    temp->val = val;

    temp->next = pos->next;
    temp->prev = pos->next->prev;

    pos->next = temp;
    temp->next->prev = temp;
}

void prepend(DLL* pos, unsigned long long val)
{
    DLL* temp = newDLL();
    temp->val = val;

    temp->prev = pos->prev;
    temp->next = pos->prev->next;

    pos->prev = temp;
    temp->prev->next = temp;
}

void factors(unsigned long long a)
{
    unsigned long long count = 0;
    DLL* begin = newDLL();
    DLL* pos = begin;

    for(unsigned long long i = 1; i*i <= a; i++)
    {
        if(i*i == a)
        {
            append(pos, i);
            count++;
            break;
        }
        if(a % i != 0) continue;
        prepend(pos->next, a/i);
        append(pos, i);
        pos = pos->next;
        count += 2;
    }
        
    printf("Factors of %llu are:", a);
    pos = begin->next;
    while(pos != begin)
    {
        printf(" %llu", pos->val);
        pos = pos->next;
    }
    printf("\n");
    printf("Number of factors: %llu\n", count);
}

void printUsage()
{
    fprintf(stderr, "usage: crm N\n");
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printUsage();
        exit(-1);
    }

    char* end;
    unsigned long long x = strtoull(argv[1], &end, 10);
    unsigned long long size = 0;
    printf("Z_%llu = { ", x);
    for(unsigned long long i = 1; i < x; i++)
    {
        if(gcd(i, x) == 1)
        {
            printf("%llu ", i);
            ++size;
        }
    }
    printf("}\n");
    printf("Size of Z_%llu is: %llu\n\n", x, size);
    factors(x);

    return 0;
}

