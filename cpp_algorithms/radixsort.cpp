#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include "sorting.hpp"

void countSort(std::vector<uint32_t>& arr, int n, uint64_t exp) {
    std::vector<uint32_t> output(n); // Output array
    int count[10] = {0}; // Initialize count array as 0

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

}

std::vector<uint32_t> radix_sort(std::vector<uint32_t>& arr, unsigned long size) {
    uint32_t m = *std::max_element(arr.begin(), arr.end());

    for (uint64_t exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, size, exp);

    return arr;
}
