#include "Timer.h"

Timer::Timer() : isRunning(true), pausedDuration(0), startTime(std::chrono::high_resolution_clock::now()){}

void Timer::pause() {
    if (isRunning) {
        pauseTime = std::chrono::high_resolution_clock::now();
        isRunning = false;
        pausedDuration += std::chrono::duration_cast<std::chrono::seconds>(pauseTime - startTime).count();
    }
}

void Timer::resume() {
    if (!isRunning) {
        startTime = std::chrono::high_resolution_clock::now();
        isRunning = true;
    }
}

int Timer::getElapsedTime() const {
    if (isRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        return pausedDuration + std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    } else {
        return pausedDuration;
    }
}