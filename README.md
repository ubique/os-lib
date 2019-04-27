# Library linkage

## Goal
This is an educational task aimed at understanding how to link
with static and dynamic libraries and use `dlopen(3)` at
runtime.

## Components
`libfoo` — static library  
`libbar` — dynamic library, linked  
`libbaz` — dynamic library, loaded with dlopen  
`foobarbaz` — executable that loads the 3 libs

## Usage
```
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX=../prefix
$ make install
$ cd ../prefix/bin
$ LD_LIBRARY_PATH=. ./foobarbaz   # Prints 'FooBarBaz'
$ ldd ./foobarbaz   # Does not show libbaz.so
```

## Copyright
Ilya Bizyaev, 2019 (<me@ilyabiz.com>)

Available in public domain.

