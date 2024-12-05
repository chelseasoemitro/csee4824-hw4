#!/bin/bash

# Directory containing the data files
data_dir="./data"
measurements_dir="./measurements"

# Algorithms to run
algorithms=("quicksort" "radixsort" "timsort")
programs=("./c_sorting" "./cpp_sorting" "python3 python_sorting.py")

# Loop through each file in the data directory
for file in "$data_dir"/*; do
  # Check if the file exists and is a regular file
  if [ -f "$file" ] && [[ "$file" != *.png ]]; then
    # Run the for each algorithm
    for algorithm in "${algorithms[@]}"; do
        for program in "${programs[@]}"; do
            output_name="$(echo $program | tr -dc '[:alnum:]\ ')_$(echo $algorithm | tr -dc '[:alnum:]\ ')$(echo $(echo $file | tr / _) | tr -d '[/.]')"
            cmd="python3 run_cache_sim.py $program $algorithm $file > $measurements_dir/$output_name.txt 2>&1"
            echo "Running $cmd"
            eval $cmd
            for cache_output in $(ls *.out); do
                mv $cache_output ${measurements_dir}/${output_name}_${cache_output}
            done
            echo done
        done
    done
  fi
done
