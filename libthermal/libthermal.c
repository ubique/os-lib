#include <sys/types.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "libthermal.h"

static float get_temp(char const* name) {
    char buf[256];
    int fd;
    size_t pos;
    ssize_t nread;
    float temp;

    pos = 0;

    fd = open(name, O_RDONLY);

    temp = NAN;

    if (fd > 0) {
        while ((nread = read(fd, buf, sizeof(buf) - pos)) > 0 || errno == EINTR) {
            pos += nread;
        }

        if (nread < 0) {
            fprintf(stderr, "WARN: could not read %s: %s\n",
                    name,
                    strerror(errno));
        }

        temp = atol(buf) / 1000.0f;
    } else {
            fprintf(stderr, "WARN: could not open %s: %s\n",
                    name,
                    strerror(errno));
    }

    close(fd);

    return temp;
}

float thermal_get_average() {
    struct dirent *ent;
    char buf[FILENAME_MAX * 4];
    float sum;
    int count;
    char const* prefix = "/sys/class/thermal";
    char const* zone = "thermal_zone";
    char const* file = "temp";
    
    DIR* dir = opendir(prefix);

    sum = 0;
    count = 0;

    while ((ent = readdir(dir)) != NULL) {
        if (strncmp(ent->d_name, zone, strlen(zone)) == 0) {
            strncpy(buf, prefix, sizeof(buf));
            strcat(buf, "/");
            strcat(buf, ent->d_name);
            strcat(buf, "/");
            strcat(buf, file);
            printf("%s\n",buf);

            float res = get_temp(buf);

            if (res != NAN) {
                sum += res;
                count++;
            }
        }
    }

    if (count == 0) {
        return NAN;
    }

    return sum / count;
}
