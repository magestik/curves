#!/bin/sh

# Recursive
mkdir build_recursive
pushd build_recursive/
cmake .. -DUSE_RECURSIVE_EVAL=TRUE
make
popd

# Iterative
mkdir build_iterative
pushd build_iterative/
cmake .. -DUSE_RECURSIVE_EVAL=FALSE
make
popd

echo "----------------- recursive"
time ./build_recursive/test/benchmark 10000000

echo "----------------- iterative"
time ./build_iterative/test/benchmark 10000000


