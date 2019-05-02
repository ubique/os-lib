#!/usr/bin/env bash

mkdir out

cd out
cmake .. --target os-lib || exit 0

cd ..
./compile_plugins.sh || exit 0

cd out
./os-lib plugins