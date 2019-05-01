#include <ctime>
#include "get_day.h"

int get_day() {
    time_t seconds = time(nullptr);
    tm* timeinfo = localtime(&seconds);
    return timeinfo->tm_mday;
}
