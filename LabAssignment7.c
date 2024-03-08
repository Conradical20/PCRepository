#include <stdio.h>

// Function to perform Bubble Sort and calculate swaps
int bubbleSort(int arr[], int n, int individualSwaps[]) {
    int i, j, temp, swaps = 0;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swaps++;

                // Increment swaps for the swapped values
                individualSwaps[arr[j]]++;
                individualSwaps[arr[j+1]]++;
            }
        }
    }
    return swaps;
}

// Function to perform Selection Sort and calculate swaps
int selectionSort(int arr[], int n, int individualSwaps[]) {
    int i, j, minIndex, temp, swaps = 0;
    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap arr[i] and arr[minIndex]
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        swaps++;

        // Increment swaps for the swapped values
        individualSwaps[arr[i]]++;
        individualSwaps[arr[minIndex]]++;
    }
    return swaps;
}

int main() {
    int array1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int n1 = sizeof(array1) / sizeof(array1[0]);
    int n2 = sizeof(array2) / sizeof(array2[0]);

    // Bubble Sort
    int bubbleIndividualSwaps1[100] = {0};  // Assuming values in the array are less than 100
    int bubbleSwaps1 = bubbleSort(array1, n1, bubbleIndividualSwaps1);
    printf("Bubble Sort - Array 1: %d swaps\n", bubbleSwaps1);
    for (int i = 0; i < n1; i++) {
        printf("Value %2d swapped %2d times\n", array1[i], bubbleIndividualSwaps1[array1[i]]);
    }

    int bubbleIndividualSwaps2[100] = {0};  // Assuming values in the array are less than 100
    int bubbleSwaps2 = bubbleSort(array2, n2, bubbleIndividualSwaps2);
    printf("Bubble Sort - Array 2: %d swaps\n", bubbleSwaps2);
    for (int i = 0; i < n2; i++) {
        printf("Value %2d swapped %2d times\n", array2[i], bubbleIndividualSwaps2[array2[i]]);
    }

    // Selection Sort
    int selectionIndividualSwaps1[100] = {0};  // Assuming values in the array are less than 100
    int selectionSwaps1 = selectionSort(array1, n1, selectionIndividualSwaps1);
    printf("\nSelection Sort - Array 1: %d swaps\n", selectionSwaps1);
    for (int i = 0; i < n1; i++) {
        printf("Value %2d swapped %2d times\n", array1[i], selectionIndividualSwaps1[array1[i]]);
    }

    int selectionIndividualSwaps2[100] = {0};  // Assuming values in the array are less than 100
    int selectionSwaps2 = selectionSort(array2, n2, selectionIndividualSwaps2);
    printf("Selection Sort - Array 2: %d swaps\n", selectionSwaps2);
    for (int i = 0; i < n2; i++) {
        printf("Value %2d swapped %2d times\n", array2[i], selectionIndividualSwaps2[array2[i]]);
    }

    return 0;
}


