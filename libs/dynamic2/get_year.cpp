#include <ctime>
#include "get_year.h"

extern "C" {
int get_year() {
    time_t seconds = time(nullptr);
    tm *timeinfo = localtime(&seconds);
    return timeinfo->tm_year + 1900;
}
}
