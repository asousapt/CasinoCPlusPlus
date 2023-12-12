// relogio.h
#ifndef RELOGIO_H
#define RELOGIO_H
#pragma once

#include <chrono>

class relogio {
public:
    relogio(int salto);
    std::chrono::system_clock::time_point now();

private:
    int incr;
    std::chrono::system_clock::time_point start_time;
};


#endif // RELOGIO_H
