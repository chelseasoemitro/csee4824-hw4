#include <algorithm>
#include "sorting.hpp"

std::vector<uint32_t> quick_sort(std::vector<uint32_t>& arr, unsigned long size) {
    std::sort(arr.begin(), arr.begin() + size);
    return arr;
}
