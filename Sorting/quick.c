#include <stdio.h>
// Swap two values (no pointers)
void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
// Partition function
int partition(int a[], int low, int high) {
    int pivot = a[high];  // Choose the last element as pivot
    int i = low - 1;      // Index of smaller element
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a, i, j);  // Swap elements if smaller than pivot
        }
    }
    swap(a, i + 1, high);  // Place pivot in correct position
    return i + 1;          // Return index of pivot
}
// Quick Sort function
void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);  // Find pivot position

        quickSort(a, low, pi - 1);   // Sort left side
        quickSort(a, pi + 1, high);  // Sort right side
    }
}
// Print array
void printArray(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
// Main function
int main() {
    int data[] = {10, 7, 8, 9, 1, 5};
    int size = sizeof(data) / sizeof(data[0]);
    printf("Original array:\n");
    printArray(data, size);
    quickSort(data, 0, size - 1);
    printf("Sorted array:\n");
    printArray(data, size);
    return 0;
}
