#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include <string.h> // For memcpy

#define RUN 32

void insertion_sort(uint32_t arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        uint32_t temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void merge(uint32_t arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    uint32_t *left = (uint32_t *)malloc(len1 * sizeof(uint32_t));
    uint32_t *right = (uint32_t *)malloc(len2 * sizeof(uint32_t));

    for (int x = 0; x < len1; x++)
        left[x] = arr[l + x];
    for (int x = 0; x < len2; x++)
        right[x] = arr[m + 1 + x];

    int i = 0;
    int j = 0;
    int k = l;

    // Merge the temp arrays back into arr[l..r]
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copy the remaining elements of left[], if there are any
    while (i < len1) {
        arr[k++] = left[i++];
    }

    // Copy the remaining elements of right[], if there are any
    while (j < len2) {
        arr[k++] = right[j++];
    }

    free(left);
    free(right);
}

void tim_sort(uint32_t arr[], int n) {
    // Sort individual subarrays of size RUN using insertion sort
    for (int i = 0; i < n; i += RUN) {
        int right = (i + RUN - 1) < (n - 1) ? (i + RUN - 1) : (n - 1);
        insertion_sort(arr, i, right);
    }

    // Start merging from size RUN (or 32).
    // It will merge to form size 64, then 128, 256, and so on...
    for (int size = RUN; size < n; size = 2 * size) {
        // Pick starting point of left subarray. We are going to merge arr[left..left+size-1] and arr[left+size..left+2*size-1]
        for (int left = 0; left < n; left += 2 * size) {
            // Find ending point of left subarray
            int mid = left + size - 1;
            if (mid >= n - 1)
                continue;

            // Find ending point of right subarray
            int right = (left + 2 * size - 1) < (n - 1) ? (left + 2 * size - 1) : (n - 1);

            // Merge subarrays arr[left...mid] & arr[mid+1...right]
            merge(arr, left, mid, right);
        }
    }
}

// Avoid making changes to this function skeleton, apart from data type changes if required
// In this starter code we have used uint32_t, feel free to change it to any other data type if required
void sort_array(uint32_t *arr, size_t size) {
    // Enter your logic here
    tim_sort(arr, size);
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

       
