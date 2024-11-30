import argparse
from subprocess import run

def makeCommand(args=[]):
    cmd = []
    cmd.append("../../../pin")
    cmd.append("-t")
    cmd.append("obj-intel64/cache.so")
    cmd.append("--")

    for arg in args:
        cmd.append(arg)
    
    return cmd

def runCommand(cmd):
    process = run(cmd, capture_output=True, text = True)

    lines = process.stderr.replace("\t", "").splitlines()
    output = []

    for line in lines:
        output.append(line.split())
    
    results = {}

    for i, result in enumerate(output[-2]):
        results[result] = int(output[-1][i])
    
    for i, result in enumerate(output[-3]):
        if result == "References:":
            results["References"] = int(output[-3][i + 1])

    return results

def runCacheSim(args):
    filename = ""

    if args.associativity:
        cmd = makeCommand([args.file, "-dl1_a", args.associativity])
        filename = "associativity_run.csv"
    elif args.capacity:
        cmd = makeCommand([args.file, "-dl1_c", args.capacity])
        filename = "capacity_run.csv"
    elif args.block:
        cmd = makeCommand([args.file, "-b", args.block])
        filename = "block_size_run.csv"
    else:
        cmd = makeCommand([args.file])
        filename = "run.csv"

    with open(filename, "w+") as f:
        first_line_written = False

        for i in range(args.num):
            results = runCommand(cmd)
            print(results) 
            if not first_line_written:
                for key in results.keys():
                    f.write(f"{key},")

                f.write("\n")
                first_line_written = True

            for value in results.values():
                f.write(f"{value},")
            f.write("\n")



def Main():
    parser = argparse.ArgumentParser(description='Run cache simulator for sensitivity study')
    
    parser.add_argument('-b','--block', type=int, help="Measure and report misses for a 32KB direct- mapped cache, for the specified block size")
    parser.add_argument('-c','--capacity', type=int, help="Measure and report misses for a direct-mapped cache with 64B blocks for the specified capacity")
    parser.add_argument('-a','--associativity', type=int, help="Measure and report misses for a 64KB, 64B cache for the specified associativity")
    parser.add_argument('-f', '--file', help="executable to pass into the cache simulator", default="./matrix")
    parser.add_argument('-n', '--num', type=int, help="number of runs to record", default=1)

    args = parser.parse_args()

    runCacheSim(args)

if __name__ == "__main__":
    Main()
