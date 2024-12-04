#ifndef SORTING_HPP
#define SORTING_HPP

#include <vector>
#include <cstdint>

std::vector<uint32_t> radix_sort(std::vector<uint32_t>& arr, unsigned long size);
std::vector<uint32_t> quick_sort(std::vector<uint32_t>& arr, unsigned long size);
std::vector<uint32_t> tim_sort(std::vector<uint32_t>& arr, unsigned long size);

#endif // SORTING_HPP
