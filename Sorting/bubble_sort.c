#include <stdio.h>

// Function to perform Bubble Sort
void bubble_sort(int arr[], int n) {
    // Run the steps n-1 times
    for (int i = 0; i < n - 1; i++) {
        // The inner loop should start from 0
        for (int j = 0; j < n - i - 1; j++) {
            // Swap the elements if the current element is greater than the next one
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Time Complexity of Bubble sort is O(n) in the best case and O(n^2) in the worst case
    int arr[] = {2, 3, 1, 5, -6, 9, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n);
    printArray(arr, n);

    return 0;
}