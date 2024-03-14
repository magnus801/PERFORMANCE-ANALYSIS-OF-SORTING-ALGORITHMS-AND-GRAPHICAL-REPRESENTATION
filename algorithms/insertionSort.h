#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int InsertionSort(int *ConfigPointers, double *ExecutionTimeArray)
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
            insertionSort(RandomArray, i);

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