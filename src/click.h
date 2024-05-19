#pragma once

#include <atomic>

namespace click { // declaring variables and methods
    // macroKey is pressed
    extern std::atomic<bool> macroPressed;

    // click left or right
    extern bool LRClick;

    // macro key
    extern short macroKey;

    // cps
    extern int delay;

    // enable clicking
    void clicking() noexcept;

    // clicking
    void click() noexcept;

    // set delay and macroKey
    void setMouseDelay(int d);
    void setMouseMacroKey(char keyChar[2]);

    // click
    void leftClick() noexcept;
    void rightClick() noexcept;
}