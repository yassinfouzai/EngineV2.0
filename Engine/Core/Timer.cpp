#include "Timer.h"

Timer::Timer() {
    lastFrameTime = std::chrono::high_resolution_clock::now();
}

float Timer::GetDeltaTime() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - lastFrameTime;
    lastFrameTime = now;
    return duration.count();
}
