#include "init.h"

#include "Windows.h"

#include <Scintilla/Scintilla.h>

namespace calc {
    static HWND MainWindow = NULL;
    static ATOM MainWindowClass = NULL;

    static HWND ScintillaControl = NULL;

    static void Error(std::string const errorString);

    static LRESULT CALLBACK MainWindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

    namespace constants {
        namespace errors {
            std::string const CreateWindowError = "Could not create main window handle";
            std::string const RegisterClassError = "Could not register main window class";
            std::string const LoadScintillaError = "Could not load SciLexer.dll";
            std::string const CreateScintillaError = "Could not create scintilla control";
        } // namespace errors

        std::string const MainWindowClassName = "MainWindow";
        std::string const MainWindowTitle = "Expression Calculator";

        unsigned const MainWindowStyleEx = 0;
        unsigned const MainWindowStyle = WS_VISIBLE | WS_SIZEBOX | WS_TILEDWINDOW;
        unsigned const MainWindowX = 200;
        unsigned const MainWindowY = 200;
        unsigned const MainWindowWidth = 800;
        unsigned const MainWindowHeight = 600;

        std::string const ScintilaClassName = "Scintilla";
        std::string const ScintillaTitle = "";

        unsigned const ScintillaStyleEx = 0;
        unsigned const ScintillaStyle = WS_VISIBLE | WS_BORDER | WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN;

        unsigned const Separator = 4;
    } // namespace constants

    int Init(HINSTANCE hInstance) {
        HMODULE res = LoadLibraryA("SciLexer.dll");
        if (res == NULL) {
            Error(constants::errors::LoadScintillaError);
            return 1;
        }

        WNDCLASS mainWindowClass;

        mainWindowClass.style = CS_DBLCLKS | CS_PARENTDC;
        mainWindowClass.lpfnWndProc = (WNDPROC)MainWindowProcedure;
        mainWindowClass.cbClsExtra = 0;
        mainWindowClass.cbWndExtra = 0;
        mainWindowClass.hInstance = hInstance;
        mainWindowClass.hIcon = NULL;
        mainWindowClass.hCursor = LoadCursor(NULL, (LPTSTR)IDC_ARROW);
        mainWindowClass.hbrBackground = NULL;
        mainWindowClass.lpszMenuName = NULL;
        mainWindowClass.lpszClassName = constants::MainWindowClassName.c_str();

        MainWindowClass = RegisterClass(&mainWindowClass);
        if (MainWindowClass == NULL) {
            Error(constants::errors::RegisterClassError);
            return 1;
        }

        MainWindow =
            CreateWindowEx(constants::MainWindowStyleEx, constants::MainWindowClassName.c_str(), constants::MainWindowTitle.c_str(), constants::MainWindowStyle,
                           constants::MainWindowX, constants::MainWindowY, constants::MainWindowWidth, constants::MainWindowHeight, NULL, NULL, NULL, NULL);

        if (MainWindow == NULL) {
            Error(constants::errors::CreateWindowError);
            return 1;
        }

        MSG message;
        while (GetMessage(&message, NULL, 0, 0) > 0) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        return 0;
    }

    static LRESULT CALLBACK MainWindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
            case WM_DESTROY: PostQuitMessage(0); return 0;
            case WM_CREATE:
                ScintillaControl = CreateWindowEx(constants::ScintillaStyleEx, constants::ScintilaClassName.c_str(), constants::ScintillaTitle.c_str(),
                                                  constants::ScintillaStyle, 0, 0, 0, 0, window, NULL, NULL, NULL);
                if (ScintillaControl == NULL) {
                    Error(constants::errors::CreateScintillaError);
                    return -1;
                }
                break;
            case WM_SIZE: {
                unsigned width = LOWORD(lParam) - 2 * constants::Separator;
                unsigned height = HIWORD(lParam) - 2 * constants::Separator;

                MoveWindow(ScintillaControl, constants::Separator, constants::Separator, width, height, TRUE);
            } break;
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(window, &ps);

                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

                EndPaint(window, &ps);
            }
                return 0;
        }
        return DefWindowProc(window, message, wParam, lParam);
    }

    static void Error(std::string const errorString) { MessageBox(MainWindow, errorString.c_str(), "Error", MB_ICONERROR | MB_OK); }
} // namespace calc
