#include <stdio.h>

// Iterative Binary Search
int getIndexbyIteration(int arr[], int size, int target) {
    int start = 0;
    int end = size - 1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}

// Recursive Binary Search
int getIndexbyRecursion(int arr[], int start, int end, int target) {
    if (start > end) {
        return -1; // Not found
    }
    
    int mid = start + (end - start) / 2;

    if (arr[mid] == target) {
        return mid; // Found
    } else if (arr[mid] < target) {
        return getIndexbyRecursion(arr, mid + 1, end, target); // Right side
    } else {
        return getIndexbyRecursion(arr, start, mid - 1, target); // Left side
    }
}

int main() {
    int size, target;
    printf("Enter the size of the sorted array: ");
    scanf("%d", &size);
    int arr[size];
    
    printf("Enter %d sorted elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search for: ");
    scanf("%d", &target);

    // Iterative Search
    int indexIter = getIndexbyIteration(arr, size, target);
    if (indexIter != -1) {
        printf("Iterative: Element %d found at index %d.\n", target, indexIter);
    } else {
        printf("Iterative: Element %d not found in the array.\n", target);
    }

    // Recursive Search
    int indexRec = getIndexbyRecursion(arr, 0, size - 1, target);
    if (indexRec != -1) {
        printf("Recursive: Element %d found at index %d.\n", target, indexRec);
    } else {
        printf("Recursive: Element %d not found in the array.\n", target);
    }

    return 0;
}
