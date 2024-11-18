#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 


static int compare_ints(const void *a, const void *b) {
    int *a_int = (int *)a;
    int *b_int = (int *)b;
    return *a_int - *b_int;
}

void qsort_array(uint32_t *arr, size_t size) {
    qsort(arr, size, sizeof(*arr), compare_ints);
}

// Avoid making changes to this function skeleton, apart from data type changes if required
// In this starter code we have used uint32_t, feel free to change it to any other data type if required
void sort_array(uint32_t *arr, size_t size) {
    // Enter your logic here
    qsort_array(arr, size);
}

int main() {
    //Initialise the array
    const uint64_t size = 100;
    uint32_t *sorted_arr = malloc(size * sizeof(uint32_t)); // Allocate memory for the sorted array
    for (int i = 0; i < size; i++) {
        sorted_arr[i] = rand() % 100;
    }

    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%u ", sorted_arr[i]);
    }
    printf("}\n");
    printf("\n");

    // Sort the copied array
    sort_array(sorted_arr, size);

    // Print the sorted array
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%u ", sorted_arr[i]);
    }
    printf("}\n");

    return 0;
}

       
