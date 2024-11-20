#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include "quicksort.h"
#include <pthread.h>

/* IMPLEMENT SORTING FUNCTIONS */
// Function to swap two integers
void swap(uint32_t *a, uint32_t *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for QuickSort
int partition(uint32_t array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}

// QuickSort function
void quicksort(uint32_t array[], int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);
        quicksort(array, low, pivot - 1);
        quicksort(array, pivot + 1, high);
    }
}

void *quicksort_thread(void *args) {
    struct sortingArgs *sortingArgs = (struct sortingArgs *) args;
    int low = sortingArgs->low;
    int high = sortingArgs->high;
    uint32_t *arr = sortingArgs->arr;

    if (low < high) {
        int pivot = partition(arr, low, high);

        struct sortingArgs leftArgs = {arr, low, pivot - 1};
        struct sortingArgs rightArgs = {arr, pivot + 1, high};

        pthread_t leftThread, rightThread;
        
        pthread_create(&leftThread, NULL, quicksort_thread, &leftArgs);
        pthread_create(&rightThread, NULL, quicksort_thread, &rightArgs);

        pthread_join(leftThread, NULL);
        pthread_join(rightThread, NULL);
    }

    return NULL;
}

// Avoid making changes to this function skeleton, apart from data type changes if required
// In this starter code we have used uint32_t, feel free to change it to any other data type if required
void sort_array(uint32_t *arr, size_t size) {
    // Enter your logic here
    struct sortingArgs args = {arr, 0, size - 1};

    pthread_t mainThread;
    pthread_create(&mainThread, NULL, quicksort_thread, &args);

    pthread_join(mainThread, NULL);
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

       
