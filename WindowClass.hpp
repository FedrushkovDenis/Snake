#ifndef _WINDOWCLASS
#define _WINDOWCLASS

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <process.h>
#include <Windows.h>
using namespace std;

// \brief Template class for Window API.
class Window 
{
protected:
    HDC windowDC;    // \brief Device Context for your window.
    HWND window;     // \brief Handle to your window.
    WNDCLASS wclass; // \brief WNDCLASS for registration your window class.
    LPCWSTR wndClassName; // \brief Class name for registration your window class.

    // \brief Template for window event handler.
    virtual LRESULT WINAPI wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    // \brief Template for window class registration.
    //virtual WNDCLASS WINAPI ClassRegister(LPCWSTR classname, WNDPROC wndproc);
    
    // \brief Template for draw function.
    //virtual void Redraw();
};


class GameWindow : Window
{
private:
    static LRESULT WINAPI wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
    WNDCLASS WINAPI ClassRegister(LPCWSTR classname, WNDPROC wndproc);
public:
    LPCWSTR wndClassName;
    HWND hwnd;
    HDC wDC;
    WNDCLASS wndclass;
    LPRECT rctScr;
    static bool isOpen;

    GameWindow()
    {

    }

    DWORD WINAPI StartWindow(HWND parent);

    void setSettings(LPCWSTR wndclassname);
};

class MainMenu : protected Window
{
private:
    static LRESULT WINAPI wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
    WNDCLASS WINAPI ClassRegister(LPCWSTR classname, WNDPROC wndproc);
public:
    HWND hwnd;
    LPCWSTR wndClassName;
    HDC wDC;
    WNDCLASS wndclass;
    LPRECT rctScr;
    static bool isOpen;

    void* testfuncptr;

    MainMenu()
    {

    }

    void StartWindow();

    void setSettings(LPCWSTR wndclassname);
};











#endif // !_WINDOWCLASS

