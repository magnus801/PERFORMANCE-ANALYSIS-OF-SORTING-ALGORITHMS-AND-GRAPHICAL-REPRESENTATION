#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

void selectionswap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        if (min_idx != i)
            selectionswap(&arr[min_idx], &arr[i]);
    }
}

// Driver program to test above functions
int SelectionSort(int *ConfigPointers, double *ExecutionTimeArray)
{
    int size = *(ConfigPointers + 3);
    int *RandomArray = (int *)malloc(size * sizeof(int));
    double Avg = 0;

    LARGE_INTEGER start, end;
    /* <-------> */

    for (int i = *(ConfigPointers + 1); i <= size; i = i + (*(ConfigPointers + 2)))
    {
        for (int j = 0; j < *(ConfigPointers + 0); j++)
        {
            // Generate a random array
            GenerateRandomArray(RandomArray, ConfigPointers, i, i + j);

            QueryPerformanceCounter(&start); // Record the start time

            // function
            selectionSort(RandomArray, i);

            QueryPerformanceCounter(&end); // Record the end time

            // Get the CPU frequency
            uint64_t cpu_frequency = get_cpu_frequency();

            // printf("CPU Frequency: %llu Hz\n", cpu_frequency);

            // Calculate the elapsed time in ticks
            uint64_t elapsed_ticks = end.QuadPart - start.QuadPart;

            // Convert ticks to nanoseconds using the CPU frequency
            double elapsed_time = (double)elapsed_ticks / cpu_frequency * 1e6;

            Avg += elapsed_time;
        }
        *(ExecutionTimeArray + ((i - *(ConfigPointers + 1)) / (*(ConfigPointers + 2)))) = Avg / *(ConfigPointers + 0);
    }

    return 0;
}