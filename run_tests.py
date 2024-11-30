import argparse
from subprocess import call

def makeCommand(args=[]):
    cmd = []
    cmd.append("./cache_sim/pin/pin")
    cmd.append("-t")
    cmd.append("cache_sim/cache_simulator/obj-intel64/cache.so")
    cmd.append("--")
    cmd.append("echo") # todo pick our actual commmand here/pass as command line argument

    for arg in args:
        cmd.append(arg)
    
    return cmd

def runAssoc(assoc):
    cmd = makeCommand()
    call(cmd)

def runCap(capacity):
    cmd = makeCommand()
    call(cmd)

def runBlock(blockSize):
    cmd = makeCommand()
    call(cmd)

def runCacheSim(args):
    if args.associativity:
        runAssoc(args.associativity)
    elif args.capacity:
        runCap(args.capacity)
    else:
        runBlock(args.block)

def Main():
    parser = argparse.ArgumentParser(description='Run cache simulator for sensitivity study')
    
    parser.add_argument('-b','--block', type=int, help="Measure and report misses for a 32KB direct- mapped cache, for the specified block size",
                        default=16)
    parser.add_argument('-c','--capacity', type=int, help="Measure and report misses for a direct-mapped cache with 64B blocks for the specified capacity")
    parser.add_argument('-a','--associativity', type=int, help="Measure and report misses for a 64KB, 64B cache for the specified associativity")

    args = parser.parse_args()
    print(args.associativity)
    runCacheSim(args)

if __name__ == "__main__":
    Main()