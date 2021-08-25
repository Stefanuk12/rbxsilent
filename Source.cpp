// Dependencies
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>

//
bool ShowWindows = false;
HWND WindowName;

// 
static BOOL CALLBACK windcallback(HWND hWnd, LPARAM lparam) {
    // Vars
    int length = GetWindowTextLength(hWnd) + 1;
    char* buffer = new char[length];

    // Get window name
    GetWindowTextA(hWnd, buffer, length);
    std::string title(buffer);

    // If it is roblox
    if (title == "Roblox") {
        bool Visible = IsWindowVisible(hWnd);

        if (!ShowWindows) {
            if (Visible) {
                // Hide Window
                ShowWindow(hWnd, SW_HIDE);

                // Minimise - ensures that rendering is disabled
                PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            }
        }
        else {
            if (!Visible) {
                // Show Window
                ShowWindow(hWnd, SW_SHOW);

                // Maximise - ensures that rendering is enabled
                PostMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
            }
        }
    }

    //
    delete[] buffer;
    return true;
};

// Vars
std::chrono::milliseconds THREAD_WAIT = std::chrono::milliseconds(50);

// See when key is pressed
void GetKeyPress()
{
    bool done = false;

    // Constant loop
    while (true)
    {
        // Get input and make sure if focused
        if (GetKeyState(VK_RSHIFT) & 0x8000 && GetForegroundWindow() == WindowName) {
            ShowWindows = !ShowWindows;

            std::cout << (ShowWindows ? "Shown" : "Hidden") << std::endl;
        }

        // Sleep
        std::this_thread::sleep_for(THREAD_WAIT);
    }
}

// Main
int main(int argc, char** argv) {
    //
    WindowName = GetForegroundWindow();
    std::cout << "All roblox clients that are open/opened will now be hidden. Press Right Shift to show all ROBLOX windows" << std::endl;

    //
    std::thread thread(GetKeyPress);

    // Constant Loop
    while (true) {
        // Handle
        EnumWindows(windcallback, 0);

        // Sleep
        Sleep(1);
    }

    //
    return 0;
}