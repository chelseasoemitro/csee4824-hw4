#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "cpptimsort.h"

int main() {
    size_t size = 100;
    std::vector<int> arr(size);

    // Generate random numbers
    std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 99);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }

    // Print the original array
    std::cout << "Original array:\n";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Sort using Timsort
    timsort(arr, std::less<int>());

    // Print the sorted array
    std::cout << "Sorted array:\n";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}
