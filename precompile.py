import argparse
import itertools
import sys
import subprocess
import tempfile


EMPTY_SIZE = 0
EMPTY_FILE = [b'#include <bits/stdc++.h>']

GCC_FLAGS = [
    'g++', '-E',
    '-x', 'c++',
    '-I', '.',
]


def compile_lines(lines):
    with tempfile.NamedTemporaryFile() as t:
        for line in lines:
            t.write(line)
        t.seek(0)

        flags = GCC_FLAGS + [t.name]
        for line in subprocess.Popen(flags, stdout=subprocess.PIPE).stdout:
            yield line.decode('utf-8').rstrip()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('name')
    parser.add_argument('-std', help='c++ coding standard', choices=['c++11', 'c++14', 'c++17'], required=False)
    parser.add_argument('--flags', required=False)

    args = parser.parse_args()
    
    global GCC_FLAGS
    if args.flags:
        GCC_FLAGS += args.flags.split()
    
    if args.std:
        GCC_FLAGS += [f'-std={args.std}']

    EMPTY_SIZE = sum(1 for _ in compile_lines(EMPTY_FILE))

    with open(args.name, 'rb') as source:
        full_file = itertools.chain(EMPTY_FILE, source)
        full_preprocessed = compile_lines(full_file)

        print('#include <bits/stdc++.h>')
        is_empty = False
        for line in itertools.islice(full_preprocessed, EMPTY_SIZE, sys.maxsize):
            if line.startswith('#'):
                continue

            if is_empty and line == '':
                continue

            print(line)
            is_empty = not line


if __name__ == '__main__':
    main()
