// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int *RandomArray, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = *(RandomArray + l + i);
	for (j = 0; j < n2; j++)
		R[j] = *(RandomArray + m + 1 + j);

	// Merge the temp arrays back into arr[l..r
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			*(RandomArray + k) = L[i];
			i++;
		}
		else
		{
			*(RandomArray + k) = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[],
	// if there are any
	while (i < n1)
	{
		*(RandomArray + k) = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[],
	// if there are any
	while (j < n2)
	{
		*(RandomArray + k) = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int *RandomArray, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(RandomArray, l, m);
		mergeSort(RandomArray, m + 1, r);

		merge(RandomArray, l, m, r);
	}
}

// Function to print an array
void printArray(int *RandomArray, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", *(RandomArray + i));
	printf("\n");
}

// Driver code
int MergeSort(int *ConfigPointers, double *ExecutionTimeArray)
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
			mergeSort(RandomArray, 0, i - 1);

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
