#!/bin/bash

# 1KB 10KB 100KB ... 100MB 1GB
sizes=(1 10 100 1000 10000 100000 1000000)
distributions=('uniform' 'normal' 'lognormal')
sorting_options=('none' 'partial' 'full')

output_dir=$1

for num_kb in "${sizes[@]}"; do
    for dist in "${distributions[@]}"; do
        for sorting in "${sorting_options[@]}"; do
            cmd="python3 generate_data.py $num_kb $dist $sorting $output_dir"
            echo -en "running [$cmd]... "
            echo "done"
        done
    done
done