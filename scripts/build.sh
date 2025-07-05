#!/usr/bin/env bash
set -e

mkdir -p build
cd build
cmake .. -DLLVM_DIR=$(llvm-config --cmakedir)
make -j$(sysctl -n hw.ncpu)

./test_main
