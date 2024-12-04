#include <stdlib.h>
#include <stdint.h> 
#include <stdio.h>
#include "sorting.h"

// Find max value in an array
int get_max_value(uint32_t arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
// Counting Sort based on exp
void countSort(uint32_t arr[], int n, uint64_t exp) {
    uint32_t output[n];
    int i, count[10] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Copy the output array to arr[]
    for (i = 0; i < n; i++)
        arr[i] = output[i];

}

uint32_t *radix_sort(uint32_t *arr, size_t size) {
    // Find max value to know max number of digits
    uint32_t m = get_max_value(arr, size);

    // Perform counting sort on each digit
    for (uint64_t exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, size, exp);

    return arr;
}
