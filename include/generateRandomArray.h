#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int GenerateRandomArray(int *RandomArray, int *ConfigPointers, int size, int seed)
{
    int i;
    srand(seed);
    for (i = 0; i < size; i++)
    {
        *(RandomArray + i) = rand() % (*(ConfigPointers + 4) - *(ConfigPointers + 5) + 1) + *(ConfigPointers + 5);
    }
    return 0;
}