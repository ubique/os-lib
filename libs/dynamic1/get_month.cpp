#include <ctime>
#include "get_month.h"

int get_month() {
    time_t seconds = time(nullptr);
    tm* timeinfo = localtime(&seconds);
    return timeinfo->tm_mon + 1;
}
