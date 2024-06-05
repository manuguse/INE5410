#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAX_SIZE = 10;

void printArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
}
void inputArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("Element %d:", i + 1);
        scanf("%d", &arr[i]); // NOLINT(*-err34-c)
    }
}

int sortAscending(const int *num1, const int *num2) {
    return *num1 - *num2;
}

int sortDescending(const int *num1, const int *num2) {
    return *num2 - *num1;
}

void bubbleSort(int *arr, int size, int (*compare)(const int *, const int *)) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (compare(&arr[j], &arr[j + 1]) > 0) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

static void initVector(int *vector) {
    srand ( time(NULL) );
    printf("[ ");
    for (int i = 0; i < MAX_SIZE; i++) {
        vector[i] = rand() % 100;
        printf("%d ", vector[i]);
    }
    printf("]\n");
}

void definesArray(int *arr) {
    int userInputArray;
    printf("Do you want to enter elements in array or use the std? (1 for enter, 0 for std):");
    scanf("%d", &userInputArray); // NOLINT(*-err34-c)
    if (userInputArray) {
        printf("Enter elements in array: \n");
        inputArray(arr, MAX_SIZE);
    } else {
        printf("Using std array: \n");
        initVector(arr);
    }
}

void sort_vector() {
    int arr[MAX_SIZE];
    definesArray(arr);
    printf("\nElements before sorting: ");
    printArray(arr, MAX_SIZE);
    // Sort and print sorted array in ascending order.
    printf("\nArray in ascending order: ");
    bubbleSort(arr, MAX_SIZE, sortAscending);
    printArray(arr, MAX_SIZE);
    // Sort and print sorted array in descending order.
    printf("\nArray in descending order: ");
    bubbleSort(arr, MAX_SIZE, sortDescending);
    printArray(arr, MAX_SIZE);
}