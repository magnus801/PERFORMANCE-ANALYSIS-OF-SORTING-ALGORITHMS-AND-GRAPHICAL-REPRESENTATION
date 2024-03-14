#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>


int partition(int a[], int start, int end)
{
    int pivot = a[end]; // pivot element
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        // If current element is smaller than the pivot
        if (a[j] < pivot)
        {
            i++; // increment index of smaller element
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    int t = a[i + 1];
    a[i + 1] = a[end];
    a[end] = t;
    return (i + 1);
}

/* function to implement quick sort */
void quick(int a[], int start, int end) /* a[] = array to be sorted, start = Starting index, end = Ending index */
{
    if (start < end)
    {
        int p = partition(a, start, end); // p is the partitioning index
        quick(a, start, p - 1);
        quick(a, p + 1, end);
    }
}

/* function to print an array */
void printArr(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
}
int QuickSort(int *ConfigPointers, double *ExecutionTimeArray)
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
            quick(RandomArray, 0, size - 1);

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