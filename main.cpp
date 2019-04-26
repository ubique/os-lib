#include <iostream>
#include <dlfcn.h>
#include "destory.cpp"
#include "tweetybird.cpp"
 using namespace std;
int main() {
    destroy();
    showTweetybird();
    void *s_dynamic_lib = dlopen("./second-dynamic-lib/second-dynamic-lib.so", RTLD_LAZY);
    if (nullptr == s_dynamic_lib) {
        cerr << "Error in loading library: " << dlerror() << endl;
        return -1;
    }

    auto downloadedPrintPics =((void (*)()) dlsym(s_dynamic_lib, "_Z10print_picsv"));
    if (nullptr != downloadedPrintPics) {
         downloadedPrintPics();
    } else {
        cerr << "Error in loading function: \"print_pics()\""<<endl;
        return EXIT_FAILURE;
    }

    if (dlclose(s_dynamic_lib) != 0) {
        cerr << "Error in closing library:  " << dlerror() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}