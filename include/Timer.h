#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    std::chrono::time_point<std::chrono::high_resolution_clock> pauseTime;

    bool isRunning;

    int pausedDuration; // in seconds

    // TODO
    // wprowadzic timeout
    int timeout;

public:
    Timer();

    void start();

    void pause();

    void resume();

    int getElapsedTime() const;
};


#endif // TIMER_H