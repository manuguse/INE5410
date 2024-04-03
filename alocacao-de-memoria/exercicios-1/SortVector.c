#include <stdlib.h>
#include <stdio.h>

const int MAX_SIZE = 10;

void printArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
}
void inputArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        scanf("%d", &arr[i]);
    } }

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

int sort_vector() {
    int arr[MAX_SIZE];
    int size = MAX_SIZE;

    printf("Enter elements in array: ");
    inputArray(arr, size);
    printf("\n\nElements before sorting: ");
    printArray(arr, size);
    // Sort and print sorted array in ascending order.
    printf("\nArray in ascending order: ");
    bubbleSort(arr, size, sortAscending);
    printArray(arr, size);
    // Sort and print sorted array in descending order.
    printf("\nArray in descending order: ");
    bubbleSort(arr, size, sortDescending);
    printArray(arr, size);

    return 0;
}