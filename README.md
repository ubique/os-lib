#Three ways to link library
* static linking (.a file)
* dynamic linking (.so file)
* dynamic linking (`dlopen` function)

##Setup project
* `mkdir build`
* `cd build`
* `cmake ../`

##Run the first way
* `make static-linking`
* `./src/static-linking`

##Run the second way
* `make shared-linking`
* `./src/shared-linking`

##Run the third way
* `make framework-shared`
* `make dl-loading`
* `./src/dl-loading ./framework/libframework-shared.so`