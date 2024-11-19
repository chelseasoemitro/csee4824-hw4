#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

#include <algorithm>

#include "x86simdsort.h"

// Avoid making changes to this function skeleton, apart from data type changes if required
// In this starter code we have used uint32_t, feel free to change it to any other data type if required
// x86-simd-sort
// cloned https://github.com/intel/x86-simd-sort
// apt installed meson
// apt installed pgk-config
// Installing libx86simdsortcpp.so.1 to /usr/local/lib/x86_64-linux-gnu
// Installing /home/bm2530/x86-simd-sort/lib/x86simdsort.h to /usr/local/include/
// Installing /home/bm2530/x86-simd-sort/builddir/meson-private/x86simdsortcpp.pc to /usr/local/lib/x86_64-linux-gnu/pkgconfig
// Installing symlink pointing to libx86simdsortcpp.so.1 to /usr/local/lib/x86_64-linux-gnu/libx86simdsortcpp.so


void sort_array(uint32_t *arr, size_t size) {
    // Enter your logic here
    // std::sort(arr, arr + size);
    x86simdsort::qsort(arr, size, true);
}

int main() {
    //Initialise the array
    const uint64_t size = 100;
    uint32_t *sorted_arr = (uint32_t *) malloc(size * sizeof(uint32_t)); // Allocate memory for the sorted array
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

       
