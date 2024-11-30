from sorting_techniques import pysort
import sys

# pulled from google
def quicksort_iterative(arr):
    """Iterative implementation of quicksort using a stack."""
    if not arr:
        return []

    stack = [(0, len(arr) - 1)]
    while stack:
        low, high = stack.pop()
        if low < high:
            pivot_index = partition(arr, low, high)
            stack.append((low, pivot_index - 1))
            stack.append((pivot_index + 1, high))

    return arr

def partition(arr, low, high):
    """Partition the array around a pivot."""
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def read_integers(filename):
	# we can just fread them from C
	# shouldn't have to do any endianness conversions
	integers = []

	with open(filename, 'rb') as input_file:
		binary_ints = input_file.read()
		for i in range(0,len(binary_ints), 4):
			val = int.from_bytes(binary_ints[i : i + 4], signed=False)
			integers.append(val)

	return integers

supported_sorts = {'timsort', 'radixsort', 'quicksort'}

def sort_integers(argv):

	if len(argv) != 3 or argv[1].lower() not in supported_sorts:
		print(f'usage: python3 {argv[0]} [sorting algorithm {supported_sorts}] [integer file]', file=sys.stderr)
		exit(1)


	algorithm_name = argv[1].lower()

	integers = read_integers(argv[2])

	sorter = pysort.Sorting()


	name_to_algorithm = {
		'quicksort': quicksort_iterative, # our data is too big for pysort recursive quicksort
		'radixsort': sorter.radixSort,
		'timsort': sorted,
	}

	result = name_to_algorithm[algorithm_name](integers)
	print(result)


if __name__ == '__main__':
	sort_integers(sys.argv)
