#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dlfcn.h>

#include <libfnv32.h>
#include <libthermal.h>

static char const* LIB_STRESS = "libstress/libstress.so";

unsigned int calc_fnv(char const* file) {
    char buf[4096];
    ssize_t nread;
    struct fnv32 fnv;

    int fd = open(file, O_RDONLY);
    
    if(fd < 0) {
        perror(strerror(errno));
        return -1;
    }

    fnv32_init(&fnv);

    while (1) {
        nread = read(fd, buf, sizeof(buf));
        if (nread < 0 && errno == EINTR) {
            continue;
        } else if(nread < 0) {
            perror(strerror(errno));
            break;
        } else if(nread == 0) {
            break;
        }

        fnv32_update(&fnv, buf, nread);
    }

    close(fd);

    return fnv32_get_hash(&fnv);
}

void stress_run_dlopen() {
    void* hndl;
    char* error;

    hndl = dlopen(LIB_STRESS, RTLD_NOW | RTLD_GLOBAL);
    
    if (!hndl) {
        fprintf(stderr, "WARN: Could not load lib: %s\n", dlerror());
        return;
    }

    dlerror();

    void(*stress_run)(void) = dlsym(hndl, "stress_run");

    if ((error = dlerror())) {
        fprintf(stderr, "WARN: Could not get symbol: %s\n", error);
        dlclose(hndl);
        return; 
    }

    stress_run();

    dlclose(hndl);
}

int main(int argc, char** argv) {
    if (argc <= 0) {
        return 1;
    }
    
    unsigned int hash = calc_fnv(argv[0]);

    printf("Our hash is: %u\n", hash);

    printf("Avg temp is: %f\n", thermal_get_average());

    stress_run_dlopen();

    printf("Avg temp is: %f\n", thermal_get_average());

}
