#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include "cpp_algorithms/sorting.hpp"
#include "timing.h"

long get_file_size(const std::string& filename) {
    struct stat file_status;
    if (stat(filename.c_str(), &file_status) < 0) {
        return -1;
    }

    return file_status.st_size;
}

std::vector<uint32_t> read_integers(const std::string& filename) {
    long file_size = get_file_size(filename);
    if (file_size < 0) {
        std::cerr << "Error getting file size" << std::endl;
        return {};
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return {};
    }

    size_t count = file_size / 4;
    std::vector<uint32_t> integers(count);

    file.read(reinterpret_cast<char*>(integers.data()), file_size);
    if (!file) {
        std::cerr << "Error reading file" << std::endl;
        return {};
    }

    return integers;
}

void print_arr(const std::vector<uint32_t>& arr) {
    std::cout << "[ ";
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " [sorting algorithm {supported_sorts}] [integer file]" << std::endl;
        return 1;
    }

    std::string algorithm_name = argv[1];
    std::string filename = argv[2];

    // Parse integer file
    std::vector<uint32_t> integers = read_integers(filename);
    if (integers.empty()) {
        return 1;
    }

    // Sort integers
    std::vector<uint32_t> result;
    int start, end;
    if (algorithm_name == "quicksort") {
        start = time_start(); 
        result = quick_sort(integers, integers.size());
        end = time_stop();
    } else if (algorithm_name == "radixsort") {
        start = time_start();
        result = radix_sort(integers, integers.size());
        end = time_stop();
    } else if (algorithm_name == "timsort") {
        start = time_start();
        result = tim_sort(integers, integers.size());
        end = time_stop();
    } else {
        std::cerr << "Unsupported sorting algorithm: " << algorithm_name << std::endl;
        return 1;
    }

    std::cout << "Number of ticks: " << end-start << "\n";
    // print_arr(result);
    return 0;
}
