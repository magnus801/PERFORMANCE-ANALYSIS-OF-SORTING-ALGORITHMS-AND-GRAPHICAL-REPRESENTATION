#include <stdio.h>
#include <stdlib.h>

#include "pbPlots.h"
#include "supportLib.h"

int PlotGraph(double *ExecutionTimeArray, int *ConfigPointers, const char *AlgorithmName)
{
    _Bool success;
    int ArraySize = ((*(ConfigPointers + 3) - (*(ConfigPointers + 1))) / (*(ConfigPointers + 2)) + 1);

    double xs[ArraySize], ys[ArraySize];
    for (int i = 0; i < ArraySize; i++)
    {
        xs[i] = *(ConfigPointers + 1) + (i * (*(ConfigPointers + 2)));
        ys[i] = *(ExecutionTimeArray + i);
    }
    int precision = ArraySize / (*(ConfigPointers + 2));

    StartArenaAllocator();

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);
    success = DrawScatterPlot(canvasReference, 1500, 1200, xs, ArraySize, ys, ArraySize, errorMessage);

    int length = snprintf(NULL, 0, "output/%s.png", AlgorithmName);

    // Allocate memory for the resulting string
    char *path = (char *)malloc(length + 1);

    // Create the formatted string
    sprintf(path, "output/%s.png", AlgorithmName);

    char graphpath[length + 1];

    strcpy(graphpath, path);

    if (success)
    {
        size_t length;
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        WriteToFile(pngdata, graphpath);
        DeleteImage(canvasReference->image);
    }
    else
    {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++)
        {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

    printf("\n\t%s - Graph Plotting Complete\n", AlgorithmName);

    FreeAllocations();
    free(path);

    return 0;
}