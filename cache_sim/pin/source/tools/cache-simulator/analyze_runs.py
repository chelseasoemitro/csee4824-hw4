import argparse
import csv
import re
import matplotlib.pyplot as plt
import numpy as np
import math

def makeDistGraph(percentages, category, saveGraph):
    x = 0
    y = 0
    color_idx = 0
    labels = []
    colors = ['black', 'maroon', 'orange', 'gold']

    for key in percentages:
        x = int(re.sub("[^0-9]", "", key))


        for type in percentages[key]:
            y = percentages[key][type]
            if type not in labels:
                labels.append(type)
                plt.scatter(x, y, label=type, color=colors[color_idx])
            else:
                plt.scatter(x, y, color=colors[color_idx])
            color_idx += 1
        color_idx = 0

    plt.xlabel(category)
    plt.ylabel("Percentage of Cache Misses")
    plt.ylim(0, 100)
    plt.legend()
    
    if saveGraph:
        plt.savefig(f"graphs/{category}_Cache_Miss_Rate.png")
    else:
        plt.show()

def makeMissRateGraph(miss_rates, category, saveGraph):
    x = []
    y = []

    for key in miss_rates:
        x.append(int(re.sub("[^0-9]", "", key)))
        y.append(miss_rates[key])

    plt.scatter(x, y)
    plt.xlabel(category)
    plt.ylabel("Average Cache Miss Rate")
    
    if saveGraph:
        plt.savefig(f"graphs/{category}_Cache_Miss_Rate.png")
    else:
        plt.show()

def print_miss_rates(miss_rates):
    print("Average Cache Misses:")

    for key in miss_rates:
        print(f"\t{key}: {miss_rates[key]}")

def print_percentages(miss_percentages, category):
    print("Cache Misses Type Distribution:")

    for key in miss_percentages:
        print(f"\t{category} {key}")
        for type in miss_percentages[key]:
            print(f"\t\t{type}: {miss_percentages[key][type]}%")

def calculate_assoc_data(results, category):
    cache_miss_rates = {}
    miss_percentages = {}

    total_misses = 0
    total_references = 0
    miss_percentages[results[category][0]] = {
        "Cold" : 0,
        "Capacity" : 0,
        "Replacement" : 0,
        "Mapping" : 0,
    }
    
    current_value = results[category][0]

    for i, value in enumerate(results[category]):
        if current_value == value:
            total_misses += int(results["Total"][i])
            total_references += int(results["References"][i])

            for key in miss_percentages[value]:
                miss_percentages[value][key] += int(results[key][i])
        else:
            cache_miss_rates[f"{category} {current_value}"] = round(total_misses / total_references, 5)
            
            for key in miss_percentages[current_value]:
                miss_percentages[current_value][key] = round(100 * (miss_percentages[current_value][key] / total_misses), 2)
            
            miss_percentages[value] = {
                "Cold" : 0,
                "Capacity" : 0,
                "Replacement" : 0,
                "Mapping" : 0,
            }

            total_misses = int(results["Total"][i])
            total_references = int(results["References"][i])

            for key in miss_percentages[value]:
                miss_percentages[value][key] += int(results[key][i])

            current_value = value

    cache_miss_rates[f"{category} {current_value}"] = round(total_misses / total_references, 5)
            
    for key in miss_percentages[current_value]:
        miss_percentages[current_value][key] = round(100 * (miss_percentages[current_value][key] / total_misses), 2)


    return cache_miss_rates, miss_percentages

def analyze_study_csv(category, produceGraph, saveGraph):
    filename = ""
    if category == 'a':
        category = "Associativity"
        filename = "associativity_run.csv"
    elif category == 'b':
        category = "Line Size (B)"
        filename = "block_size_run.csv"
    else:
        category = "Capacity (KB)"
        filename = "capacity_run.csv"


    results = {
        "Capacity (KB)" : [],
        "Line Size (B)" : [],
        "Associativity" : [],
        "Num Sets" : [],
        "Total" : [],
        "Cold" : [],
        "Capacity" : [],
        "Mapping" : [],
        "Replacement" : [],
        "References" : []
    }
    
    with open(filename,'r') as csvfile:
        reader = csv.reader(csvfile)
        headers = next(reader)  # Read the header row

        for row in reader:
            for i, value in enumerate(row):
                if value == '':
                    continue
                results[headers[i]].append(value)

    miss_rates, percentages = calculate_assoc_data(results, category)

    print_miss_rates(miss_rates)
    print()
    print_percentages(percentages, category)

    if produceGraph:
        if produceGraph == "rates":
            makeMissRateGraph(miss_rates, category, saveGraph)
        elif produceGraph == 'dist':
            makeDistGraph(percentages, category, saveGraph)

def Main():
    parser = argparse.ArgumentParser(description="Print information regarding cache sensitivity studies")

    parser.add_argument('-c', '--category', choices=['a', 'b', 'c'], required=True,
                        help="which category to analyze, associativity (a), block size (b), or capacity (c).")
    
    parser.add_argument('-g', '--graph', choices=['rates', 'dist'], help="Set this option if you want to graph the data")
    parser.add_argument('-s', '--save', help="Set this option if you want to save the graph, -g flag must be set", action="store_true")

    args = parser.parse_args()

    if args.graph:
        analyze_study_csv(args.category, args.graph, args.save)
    else:
        analyze_study_csv(args.category, None, args.save)
    


if __name__ == "__main__":
    Main()