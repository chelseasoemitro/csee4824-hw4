#!/bin/bash

# Directory containing the data files
data_dir="./data"

# Algorithms to run
algorithms=("quicksort" "radixsort" "timsort")

# Loop through each file in the data directory
for file in "$data_dir"/*; do
  # Check if the file exists and is a regular file
  if [ -f "$file" ] && [[ "$file" != *.png ]]; then
    # Run the script for each algorithm
    for algorithm in "${algorithms[@]}"; do
      echo "Running ./c_sorting $algorithm $file"
      ./c_sorting "$algorithm" "$file"
    done
  fi
done
