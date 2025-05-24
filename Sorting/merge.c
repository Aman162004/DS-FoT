#include <stdio.h>

// Function to merge two sorted halves
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // size of left half
    int n2 = right - mid;    // size of right half

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data into temporary arrays
    for (i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temp arrays back into arr[]
    i = 0; // index for L[]
    j = 0; // index for R[]
    k = left; // index for merged array

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i]; // pick from left
            i++;
        } else {
            arr[k] = R[j]; // pick from right
            j++;
        }
        k++;
    }

    // Copy remaining elements (if any) from L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements (if any) from R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Find middle point

        // Recursively sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, size);

    mergeSort(arr, 0, size - 1); // Call merge sort

    printf("Sorted array:\n");
    printArray(arr, size);

    return 0;
}
