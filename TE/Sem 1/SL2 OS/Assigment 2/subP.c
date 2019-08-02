/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Assignment 2 Part B Array Sort Sub Process
Date : Jun 8 2019
Copyright : GNU public Library
=====================================================*/

// NOTE : D0 NOT RUN THIS DIRECTLY, ONLY COMPILE IT AND NAME OUTPUT FILE AS "b.out"
// gcc subP.c -o b.out

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// BINARY SEARCH FOR SEARCHING THE ELEMENT
void binarySearch(int n, int array[], int key)
{
    int i = 0, fs, ls, m;
    fs = 0;            // FIRST
    ls = n - 1;        // LAST
    m = (fs + ls) / 2; // MIDDLE

    while (1)
    {

        i++;
        if (i == 20) // EXIT WHEN ARRAY IS EXHAUSTED
            break;

        if (key == array[m]) // FOUND !!
        {
            printf("Found at position %d!\n", m + 1);
            break;
        }
        else if (key < array[m]) // PARSE LEFT
        {
            if (ls == m)
            {
                printf("\nNOT FOUND !\n");
                break;
            }
            ls = m;
            m = (fs + ls) / 2;
        }
        else if (key > array[m]) // PARSE RIGHT
        {
            if (m == fs)
            {
                printf("\nNOT FOUND !\n");
                break;
            }
            fs = m;
            m = (fs + ls) + 1/ 2;
        }
    }
}

int main(int argc, char *argv[])
{
    int i, key, *array;
    int ch = 1;
    array = (int *)malloc(sizeof(int) * argc);

    while (ch == 1)
    {
        printf("\nEnter the element you want to search : ");
        scanf("%d", &key);
        for (i = 0; i < argc; i++)
        {
            *(array + i) = atoi(argv[i]);
        }
        binarySearch(argc, array, key);
        printf("\nDo you want to search again ?\n 1) YES \n 2) NO \n Your Choice : ");
        scanf("%d", &ch);
    }
    return (0);
}
