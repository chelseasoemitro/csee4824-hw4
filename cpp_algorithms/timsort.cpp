#include <vector>
#include <algorithm>
#include <iterator>
#include "sorting.hpp"

const size_t MIN_MERGE = 32;

struct Run {
    std::vector<uint32_t>::iterator base; // Base iterator of the run
    size_t len;                           // Length of the run
};

struct TimsortState {
    std::vector<uint32_t>& array;        // Reference to the array being sorted
    std::vector<Run> runStack;           // Stack of runs
    size_t minGallop = 7;                // Minimum galloping threshold
};

size_t minRunLength(size_t n) {
    size_t r = 0;
    while (n >= MIN_MERGE) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template <typename Compare>
size_t countRunAndMakeAscending(std::vector<uint32_t>::iterator begin, std::vector<uint32_t>::iterator end, Compare comp) {
    auto iter = begin;
    if (begin == end) return 0;

    ++iter;
    if (iter == end) return 1;

    if (comp(*iter, *begin)) {
        while (++iter != end && comp(*iter, *(iter - 1)));
        std::reverse(begin, iter);
    } else {
        while (++iter != end && !comp(*iter, *(iter - 1)));
    }

    return std::distance(begin, iter);
}

template <typename Compare>
void binaryInsertionSort(std::vector<uint32_t>::iterator begin, std::vector<uint32_t>::iterator end, Compare comp) {
    for (auto it = begin + 1; it < end; ++it) {
        uint32_t temp = std::move(*it);
        auto pos = std::upper_bound(begin, it, temp, comp);
        std::move_backward(pos, it, it + 1);
        *pos = std::move(temp);
    }
}

template <typename Compare>
void mergeAt(TimsortState& state, size_t runIdx, Compare comp) {
    Run& run1 = state.runStack[runIdx];
    Run& run2 = state.runStack[runIdx + 1];

    auto base1 = run1.base;
    auto base2 = run2.base;
    size_t len1 = run1.len;
    size_t len2 = run2.len;

    std::vector<uint32_t> temp(base1, base1 + len1);

    auto cursor1 = temp.begin();
    auto cursor2 = base2;
    auto dest = base1;

    while (cursor1 != temp.end() && cursor2 != base2 + len2) {
        if (comp(*cursor2, *cursor1)) {
            *dest++ = std::move(*cursor2++);
        } else {
            *dest++ = std::move(*cursor1++);
        }
    }

    std::move(cursor1, temp.end(), dest);
    std::move(cursor2, base2 + len2, dest);

    run1.len += run2.len;
    state.runStack.erase(state.runStack.begin() + runIdx + 1);
}

template <typename Compare>
void mergeCollapse(TimsortState& state, Compare comp) {
    while (state.runStack.size() > 1) {
        size_t n = state.runStack.size() - 2;
        if (n > 0 && state.runStack[n - 1].len <= state.runStack[n].len + state.runStack[n + 1].len) {
            if (state.runStack[n - 1].len < state.runStack[n + 1].len) n--;
            mergeAt(state, n, comp);
        } else if (state.runStack[n].len > state.runStack[n + 1].len) {
            break;
        } else {
            mergeAt(state, n, comp);
        }
    }
}

template <typename Compare>
void mergeForceCollapse(TimsortState& state, Compare comp) {
    while (state.runStack.size() > 1) {
        mergeAt(state, state.runStack.size() - 2, comp);
    }
}

template <typename Compare>
void timsort(std::vector<uint32_t>& arr, Compare comp) {
    if (arr.size() < 2) return;

    TimsortState state = {arr};
    size_t minRun = minRunLength(arr.size());

    auto begin = arr.begin();
    auto end = arr.end();

    while (begin != end) {
        size_t runLen = countRunAndMakeAscending(begin, end, comp);
        if (runLen < minRun) {
            size_t forceLen = std::min<size_t>(minRun, std::distance(begin, end));
            binaryInsertionSort(begin, begin + forceLen, comp);
            runLen = forceLen;
        }
        state.runStack.push_back(Run{begin, runLen});
        mergeCollapse(state, comp);
        begin += runLen;
    }

    mergeForceCollapse(state, comp);
}

std::vector<uint32_t> tim_sort(std::vector<uint32_t>& arr, unsigned long size) {
    timsort(arr, std::less<uint32_t>{});
    return arr;
}
