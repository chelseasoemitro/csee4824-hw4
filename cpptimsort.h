#ifndef CPPTIMSORT_H
#define CPPTIMSORT_H

#include <vector>
#include <algorithm>
#include <iterator>

const size_t MIN_MERGE = 32;

template <typename T>
struct Run {
    typename std::vector<T>::iterator base; // Base iterator of the run
    size_t len;                             // Length of the run
};

template <typename T>
struct TimsortState {
    std::vector<T>& array;       // Reference to the array being sorted
    std::vector<Run<T>> runStack; // Stack of runs
    size_t minGallop = 7;        // Minimum galloping threshold
};

size_t minRunLength(size_t n) {
    size_t r = 0;
    while (n >= MIN_MERGE) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template <typename T, typename Compare>
size_t countRunAndMakeAscending(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, Compare comp) {
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

template <typename T, typename Compare>
void binaryInsertionSort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, Compare comp) {
    for (auto it = begin + 1; it < end; ++it) {
        T temp = std::move(*it);
        auto pos = std::upper_bound(begin, it, temp, comp);
        std::move_backward(pos, it, it + 1);
        *pos = std::move(temp);
    }
}

template <typename T, typename Compare>
void mergeAt(TimsortState<T>& state, size_t runIdx, Compare comp) {
    Run<T>& run1 = state.runStack[runIdx];
    Run<T>& run2 = state.runStack[runIdx + 1];

    auto base1 = run1.base;
    auto base2 = run2.base;
    size_t len1 = run1.len;
    size_t len2 = run2.len;

    std::vector<T> temp(base1, base1 + len1);

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

template <typename T, typename Compare>
void mergeCollapse(TimsortState<T>& state, Compare comp) {
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

template <typename T, typename Compare>
void mergeForceCollapse(TimsortState<T>& state, Compare comp) {
    while (state.runStack.size() > 1) {
        mergeAt(state, state.runStack.size() - 2, comp);
    }
}

template <typename T, typename Compare>
void timsort(std::vector<T>& arr, Compare comp) {
    if (arr.size() < 2) return;

    TimsortState<T> state = {arr};
    size_t minRun = minRunLength(arr.size());

    auto begin = arr.begin();
    auto end = arr.end();

    while (begin != end) {
        // Explicitly specify template arguments for countRunAndMakeAscending
        size_t runLen = countRunAndMakeAscending<T, Compare>(begin, end, comp);
        if (runLen < minRun) {
            size_t forceLen = std::min<size_t>(minRun, std::distance(begin, end));
            // Explicitly specify template arguments for binaryInsertionSort
            binaryInsertionSort<T, Compare>(begin, begin + forceLen, comp);
            runLen = forceLen;
        }
        state.runStack.push_back(Run<T>{begin, runLen});
        mergeCollapse(state, comp);
        begin += runLen;
    }

    mergeForceCollapse(state, comp);
}

#endif // CPPTIMSORT_H
