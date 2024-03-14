#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "./include/generateRandomArray.h"
#include "./include/graphPlot.h"
#include "./include/executionTime.h"

#include "./algorithms/mergeSort.h"
#include "./algorithms/bubbleSort.h"
#include "./algorithms/quickSort.h"
#include "./algorithms/insertionSort.h"
#include "./algorithms/selectionSort.h"

// Global Config Pointers Array
int ConfigVar[6];
int *ConfigPointers = ConfigVar;

// Function to read the configuration file and assign values to global integer pointers
int ReadConfigFile()
{
    // Open the file for reading
    FILE *file;
    file = fopen("config.txt", "r");

    // Check if the file is successfully opened
    if (file == NULL)
    {
        printf("main.c: Error opening the config.txt File.\n");
        return 1; // Return an error code
    }

    // Read each line from the file
    fscanf(file, "NumberofIterations: %d\n", &ConfigVar[0]);
    fscanf(file, "StartIterationFromSize: %d\n", &ConfigVar[1]);
    fscanf(file, "IterationGap: %d\n", &ConfigVar[2]);
    fscanf(file, "EndIterationTillSize: %d\n", &ConfigVar[3]);
    fscanf(file, "RandomArrayUpperBound: %d\n", &ConfigVar[4]);
    fscanf(file, "RandomArrayLowerBound: %d\n", &ConfigVar[5]);

    // Close the file
    fclose(file);

    return 0;
}

int main()
{
    // Read the configuration file
    ReadConfigFile();

    int ArraySize = ((*(ConfigPointers + 3) - (*(ConfigPointers + 1))) / (*(ConfigPointers + 2)) + 1);

    // Create an array to store the execution time of each iteration
    double *ExecutionTimeArray = (double *)malloc(ArraySize * sizeof(double));

    if (ExecutionTimeArray == NULL)
    {
        printf("main.c: Memory allocation failed.\n");
        return 1; // Return an error code
    }

    printf("Sorting Algorithms Calculation and Graph Plotting Started!\n");

    MergeSort(ConfigPointers, ExecutionTimeArray);
    PlotGraph(ExecutionTimeArray, ConfigPointers, "MergeSort");

    BubbleSort(ConfigPointers, ExecutionTimeArray);
    PlotGraph(ExecutionTimeArray, ConfigPointers, "BubbleSort");

    QuickSort(ConfigPointers, ExecutionTimeArray);
    PlotGraph(ExecutionTimeArray, ConfigPointers, "QuickSort");

    InsertionSort(ConfigPointers, ExecutionTimeArray);
    PlotGraph(ExecutionTimeArray, ConfigPointers, "InsertionSort");

    SelectionSort(ConfigPointers, ExecutionTimeArray);
    PlotGraph(ExecutionTimeArray, ConfigPointers, "SelectionSort");

    // Free the memory allocated to the ExecutionTimeArray
    free(ExecutionTimeArray);

    printf("\nSorting Algorithms Calculation and Graph Plotting Completed!\nPress any Key to Exit...");
    getchar();

    printf("\nSandesh!");
    return 0;
}