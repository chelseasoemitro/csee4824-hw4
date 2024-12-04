#include <stdlib.h>
#include <stdint.h> 
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "c_algorithms/sorting.h"

long get_file_size(const char *filename) {
    struct stat file_status;
    if (stat(filename, &file_status) < 0) {
        return -1;
    }

    return file_status.st_size;
}

int check_if_sorted(uint32_t sorted_arr[], size_t length) {
    for (int i = 1; i < length; i++) {
        if (sorted_arr[i-1] > sorted_arr[i]) {
            return 0;
        }
    }
    return 1;
}

uint32_t* read_integers(const char* filename, size_t* count) {
    int file_size = get_file_size(filename);

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Cannot open file");
        return NULL;
    }

    // Allocate memory to hold the integers
    uint32_t* integers = malloc(file_size);
    if (integers == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    *count = file_size / 4;

    // Read the integers from the file
    if (fread(integers, 4, *count, file) != *count) {
        perror("Error reading file");
        free(integers);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return integers;
}

void print_arr(uint32_t arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++)
        printf("%u ", arr[i]);

    printf("]\n");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s [sorting algorithm {supported_sorts}] [integer file]", argv[0]);
		exit(1);
    }

    char *algorithm_name = argv[1];

    // Parse integer file
    size_t num_integers;
    uint32_t *integers = read_integers(argv[2], &num_integers);
    if (integers == NULL)
        exit(1);

    // Sort integers
    uint32_t *result = NULL;
    if (strcmp(algorithm_name, "quicksort") == 0) {
        result = quick_sort(integers, num_integers);
    } else if (strcmp(algorithm_name, "radixsort") == 0) {
        result = radix_sort(integers, num_integers);
    } else if (strcmp(algorithm_name, "timsort") == 0) {
        result = tim_sort(integers, num_integers);
    } else {
        fprintf(stderr, "Unsupported sorting algorithm %s provided.", algorithm_name);
        exit(1);
    }

    print_arr(result, num_integers);
    if (check_if_sorted(result, num_integers)) {
        printf("sorted\n");
    } else {
        printf("not sorted\n");
    }
    return 0;
}
