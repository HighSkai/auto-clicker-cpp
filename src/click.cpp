#include "click.h"

#include <Windows.h>
#include <WinUser.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace click { // defining variables and methods
    std::atomic<bool> macroPressed = false;
    bool wasGPressed;
    bool LRClick = true;
    short macroKey = 'G';
    int delay = 100;

    std::mutex mtx;
    std::condition_variable cv;

    void click::clicking() noexcept {
        if (GetAsyncKeyState(macroKey) & 0x8000) { // checks if the macroKey was pressed
            std::lock_guard<std::mutex> lock(mtx);
            macroPressed = !macroPressed;
            if (macroPressed) {
                // Start a new thread for the clicking loop
                std::thread([]() {
                    while (true) {
                        std::unique_lock<std::mutex> lock(click::mtx);
                        if (!click::macroPressed) {
                            return;  // Exit the thread if macroPressed is false
                        }
                        lock.unlock();
                        click::click();
                        std::this_thread::sleep_for(std::chrono::milliseconds(click::delay));
                    }
                    }).detach();
            }
            else {
                // Notify the condition variable to potentially stop the clicking thread
                cv.notify_one();
            }
        }
    }

    void click::click() noexcept { // click left or right
        if (LRClick == true)
            click::leftClick();
        else
            click::rightClick();
    }

    void click::setMouseDelay(int d) { // set delay
        click::delay = d;
    }

    void click::setMouseMacroKey(char keyChar[2]) { // set macroKey
        short vkCode = VkKeyScanEx(keyChar[0], GetKeyboardLayout(0));

        if (vkCode != -1) {
            click::macroKey = vkCode;
        }
        else {

        }
    }

    void click::leftClick() noexcept { // left click
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }

    void click::rightClick() noexcept { // right click
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }
}