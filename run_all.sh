#!/usr/bin/env bash

mkdir out

cmake --build out --target os-lib || exit 0
./compile_plugins.sh || exit 0

cd out
./os-lib plugins