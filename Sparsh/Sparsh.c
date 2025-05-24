#include <stdio.h>
#include <stdlib.h>

// Define the structure for a sparse matrix element
typedef struct {
    int row, col, value;
} SparseElement;

// Define the structure for a sparse matrix
typedef struct {
    int rows, cols, numElements; // Number of rows, columns, and non-zero elements
    int capacity; // Capacity of the elements array
    SparseElement *elements; // Array of non-zero elements
} SparseArray;

// Function to create a sparse matrix
SparseArray* createSparseArray(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    
    SparseArray *arr = (SparseArray*)malloc(sizeof(SparseArray)); // Allocate memory for the sparse matrix
    if (!arr) return NULL;

    arr->rows = rows;
    arr->cols = cols;
    arr->numElements = 0;
    arr->capacity = 10; // Initial capacity
    arr->elements = (SparseElement*)malloc(arr->capacity * sizeof(SparseElement)); // Allocate memory for the elements array
    
    if (!arr->elements) {
        free(arr);
        return NULL;
    }
    return arr;
}

// Function to ensure the capacity of the elements array
void ensureCapacity(SparseArray *arr) {
    if (arr->numElements >= arr->capacity) {
        arr->capacity *= 2; // Double the capacity
        SparseElement *temp = (SparseElement*)realloc(arr->elements,arr->capacity * sizeof(SparseElement)); // Reallocate memory for the elements array
        if (temp) {
            arr->elements = temp;
        }
    }
}

// Function to set a value in the sparse matrix
void setValue(SparseArray *arr, int row, int col, int value) {
    if (!arr || row < 0 || row >= arr->rows || col < 0 || col >= arr->cols) 
        return;

    // Check if element already exists
    for (int i = 0; i < arr->numElements; i++) {
        if (arr->elements[i].row == row && arr->elements[i].col == col) {
            if (value == 0) {
                // Remove element if value is 0
                removeValue(arr, row, col);
            } else {
                arr->elements[i].value = value;
            }
            return;
        }
    }

    // Add new element if value is not 0
    if (value != 0) {
        ensureCapacity(arr);
        arr->elements[arr->numElements].row = row;
        arr->elements[arr->numElements].col = col;
        arr->elements[arr->numElements].value = value;
        arr->numElements++;
    }
}

// Function to get a value from the sparse matrix
int getValue(SparseArray *arr, int row, int col) {
    if (!arr || row < 0 || row >= arr->rows || col < 0 || col >= arr->cols) 
        return 0;

    for (int i = 0; i < arr->numElements; i++) {
        if (arr->elements[i].row == row && arr->elements[i].col == col) {
            return arr->elements[i].value;
        }
    }
    return 0;
}

// Function to add a value to the sparse matrix
void addValue(SparseArray *arr, int row, int col, int value) {
    if (!arr || value == 0) return;
    
    int currentValue = getValue(arr, row, col);
    setValue(arr, row, col, currentValue + value);
}

// Function to remove a value from the sparse matrix
void removeValue(SparseArray *arr, int row, int col) {
    if (!arr) return;

    for (int i = 0; i < arr->numElements; i++) {
        if (arr->elements[i].row == row && arr->elements[i].col == col) {
            // Move last element to this position
            arr->numElements--;
            if (i < arr->numElements) {
                arr->elements[i] = arr->elements[arr->numElements];
            }
            return;
        }
    }
}

// Function to transpose the sparse matrix
SparseArray* transpose(SparseArray *arr) {
    if (!arr) return NULL;

    SparseArray *transposed = createSparseArray(arr->cols, arr->rows); // Create a new sparse matrix with transposed dimensions
    if (!transposed) return NULL;

    for (int i = 0; i < arr->numElements; i++) {
        setValue(transposed, arr->elements[i].col,arr->elements[i].row, arr->elements[i].value); // Set the transposed values
    }
    return transposed;
}

// Function to add two sparse matrices
SparseArray* addSparseArrays(SparseArray *a, SparseArray *b) {
    if (!a || !b || a->rows != b->rows || a->cols != b->cols) 
        return NULL;

    SparseArray *result = createSparseArray(a->rows, a->cols); // Create a new sparse matrix for the result
    if (!result) return NULL;

    // Copy elements from first array
    for (int i = 0; i < a->numElements; i++) {
        setValue(result, a->elements[i].row, a->elements[i].col, a->elements[i].value);
    }

    // Add elements from second array
    for (int i = 0; i < b->numElements; i++) {
        addValue(result, b->elements[i].row, b->elements[i].col, b->elements[i].value);
    }
    return result;
}

// Function to multiply two sparse matrices
SparseArray* multiplySparseArrays(SparseArray *a, SparseArray *b) {
    if (!a || !b || a->cols != b->rows) return NULL;

    SparseArray *result = createSparseArray(a->rows, b->cols); // Create a new sparse matrix for the result
    if (!result) return NULL;

    for (int i = 0; i < a->numElements; i++) {
        for (int j = 0; j < b->numElements; j++) {
            if (a->elements[i].col == b->elements[j].row) {
                int product = a->elements[i].value * b->elements[j].value;
                addValue(result, a->elements[i].row, b->elements[j].col, product);
            }
        }
    }
    return result;
}

// Function to multiply the sparse matrix by a scalar
void multiplyScalar(SparseArray *arr, int scalar) {
    if (!arr) return;

    for (int i = 0; i < arr->numElements; i++) {
        arr->elements[i].value *= scalar;
    }
}

// Function to convert the sparse matrix to a dense matrix
int** toDenseArray(SparseArray *arr) {
    if (!arr) return NULL;

    int **dense = (int**)malloc(arr->rows * sizeof(int*)); // Allocate memory for the dense matrix
    if (!dense) return NULL;

    for (int i = 0; i < arr->rows; i++) {
        dense[i] = (int*)malloc(arr->cols * sizeof(int)); // Allocate memory for each row
        if (!dense[i]) {
            // Clean up on allocation failure
            for (int j = 0; j < i; j++) {
                free(dense[j]);
            }
            free(dense);
            return NULL;
        }
        // Initialize the allocated memory to 0
        for (int j = 0; j < arr->cols; j++) {
            dense[i][j] = 0;
        }
    }

    for (int i = 0; i < arr->numElements; i++) {
        dense[arr->elements[i].row][arr->elements[i].col] = arr->elements[i].value; // Set the values in the dense matrix
    }
    return dense;
}

// Function to convert a dense matrix to a sparse matrix
SparseArray* toSparseArray(int** dense, int rows, int cols) {
    if (!dense || rows <= 0 || cols <= 0) return NULL;

    SparseArray *arr = createSparseArray(rows, cols);
    if (!arr) return NULL;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (dense[i][j] != 0) {
                setValue(arr, i, j, dense[i][j]);
            }
        }
    }
    return arr;
}

// Function to free the memory allocated for the sparse matrix
void freeSparseArray(SparseArray *arr) {
    if (arr) {
        free(arr->elements);
        free(arr);
    }
}

// Function to free the memory allocated for the dense matrix
void freeDenseArray(int **arr, int rows) {
    if (arr) {
        for (int i = 0; i < rows; i++) {
            free(arr[i]);
        }
        free(arr);
    }
}