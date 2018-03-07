#ifndef INIT_H
#define INIT_H

#include <Windows.h>

#include <string>

namespace calc {
    namespace constants {
        extern std::string const MainWindowClassName;
        extern std::string const MainWindowTitle;

        extern unsigned const MainWindowStyleEx;
        extern unsigned const MainWindowStyle;
        extern unsigned const MainWindowX;
        extern unsigned const MainWindowY;
        extern unsigned const MainWindowWidth;
        extern unsigned const MainWindowHeight;
    } // namespace constants
    int Init(HINSTANCE hInstance = NULL);
} // namespace calc

#endif // INIT_H
