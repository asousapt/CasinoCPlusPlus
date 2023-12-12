// relogio.cpp
#include "relogio.h"

relogio::relogio(int salto) : incr(salto), start_time(std::chrono::system_clock::now()) {}

std::chrono::system_clock::time_point relogio::now() {
    // Get the current time
    auto real_now = std::chrono::system_clock::now();

    // Calculate the elapsed real-world time
    auto elapsed_real_time = std::chrono::duration_cast<std::chrono::milliseconds>(real_now - start_time);

    // Calculate the accelerated time
    auto accelerated_time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_real_time * incr);

    return start_time + accelerated_time;
}
