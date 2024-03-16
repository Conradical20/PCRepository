#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void *Alloc(size_t sz)
{
    extraMemoryAllocated += sz;
    size_t* ret = malloc(sizeof(size_t) + sz);
    *ret = sz;
    printf("Extra memory allocated, size: %ld\n", sz);
    return &ret[1];
}

void DeAlloc(void* ptr)
{
    size_t* pSz = (size_t*)ptr - 1;
    extraMemoryAllocated -= *pSz;
    printf("Extra memory deallocated, size: %ld\n", *pSz);
    free((size_t*)ptr - 1);
}

size_t Size(void* ptr)
{
    return ((size_t*)ptr)[-1];
}

// Implement merge sort directly including the merge process
void mergeSort(int pData[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);

        int n1 = m - l + 1;
        int n2 = r - m;

        // Allocate memory for temporary arrays
        int* L = (int*)Alloc(n1 * sizeof(int));
        int* R = (int*)Alloc(n2 * sizeof(int));

        // Copy data to temp arrays L[] and R[]
        for (int i = 0; i < n1; i++)
            L[i] = pData[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = pData[m + 1 + j];

        // Merge temporary arrays back into pData[l..r]
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                pData[k] = L[i];
                i++;
            } else {
                pData[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy any remaining elements of L[], then R[]
        while (i < n1) {
            pData[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            pData[k] = R[j];
            j++;
            k++;
        }

        // Deallocate temporary arrays
        DeAlloc(L);
        DeAlloc(R);
    }
}

int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0, i, n, *data;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            fscanf(inFile, "%d ", &n);
            data = *ppData + i;
            *data = n;
        }
        fclose(inFile);
    }
    return dataSz;
}

void printArray(int pData[], int dataSz)
{
    int i, sz = (dataSz > 100) ? dataSz - 100 : 0;
    printf("\tData:\n\t");
    for (i = 0; i < 100 && i < dataSz; ++i) {
        printf("%d ", pData[i]);
    }
    if (dataSz > 100) {
        printf("\n\t...");
        for (i = sz; i < dataSz; ++i) {
            printf("%d ", pData[i]);
        }
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };

    for (i = 0; i < 4; ++i) {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0)
            continue;

        pDataCopy = (int *)malloc(sizeof(int) * dataSz);
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("---------------------------\n");
        printf("Dataset Size : %d\n", dataSz);
        printf("---------------------------\n");
        printf("Merge Sort:\n");
        printf("\truntime\t\t\t: %.2lf seconds\n", cpu_time_used);
        printf("\textra memory allocated\t: %d bytes\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }

    return 0;
}
