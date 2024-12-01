import argparse
from subprocess import call
import sys

def runCacheSim(flags, program):
    cmd = []
    cmd.append('./cache_sim/pin/pin')
    cmd.extend(['-t', 'cache_sim/cache_simulator/obj-intel64/cache.so'])

    if flags.block:
        cmd.extend(['-b', f'{flags.block}'])

    if flags.capacity:
        cmd.extend(['-dl1_c', f'{flags.capacity}'])

    if flags.associativity:
        cmd.extend(['-dl1_a',f'{flags.associativity}'])

    # add program and all args
    cmd.append('--')
    cmd.extend(program if program else ['echo', 'default'])

    print(' '.join(cmd))
    call(cmd)


def main():
    parser = argparse.ArgumentParser(description='Run cache simulator for sensitivity study')
    
    parser.add_argument('-b', '--block', type=int, help='Measure and report misses for a 32KB direct- mapped cache, for the specified block size')
    parser.add_argument('-c','--capacity', type=int, help='Measure and report misses for a direct-mapped cache with 64B blocks for the specified capacity')
    parser.add_argument('-a','--associativity', type=int, help='Measure and report misses for a 64KB, 64B cache for the specified associativity')

    flags, program = parser.parse_known_args()

    runCacheSim(flags, program)

if __name__ == '__main__':
    main()
