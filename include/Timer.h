#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    Timer();
    void start();
    void pause();
    void resume();
    int getElapsedTime() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> pauseTime;
    bool isRunning;
    int pausedDuration; // in seconds
};

#endif // TIMER_H