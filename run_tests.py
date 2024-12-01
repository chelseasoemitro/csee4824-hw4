import argparse
from subprocess import call
import sys

MEGABYTES = 10 ** 6

def runCacheSim(flags, program):
    cmd = []
    cmd.append('./cache_sim/pin/pin')

    if flags.memory:
        cmd.extend(['-pin_memory_size', f'{flags.memory * MEGABYTES}'])

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
    
    parser.add_argument('-b', '--block', type=int)
    parser.add_argument('-c','--capacity', type=int)
    parser.add_argument('-a','--associativity', type=int)
    parser.add_argument('-m', '--memory', type=int, help='Max number of megabytes that can be dynamically allocated (0 = unlimited, at least 52MB is recommended)')

    flags, program = parser.parse_known_args()

    runCacheSim(flags, program)

if __name__ == '__main__':
    main()
