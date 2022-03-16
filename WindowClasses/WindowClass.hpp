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
    HWND hwnd;     // \brief Handle to your window.
    WNDCLASS wndclass; // \brief WNDCLASS for registration your window class.
    LPCWSTR wndClassName; // \brief Class name for registration your window class.

    // \brief Template for window event handler.
    virtual LRESULT WINAPI wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    { 
        return DefWindowProc(hWnd, Msg, wParam, lParam); 
    }

    // \brief Template for window class registration.
    virtual WNDCLASS WINAPI ClassRegister(LPCWSTR classname, WNDPROC wndproc) 
    { 
        WNDCLASS wclass{};
        return wclass; 
    };

    virtual HDC getDC() { return windowDC; };
    virtual HWND getHWND() { return hwnd; }

};


class GameWindow : protected Window
{
private:
    static LRESULT WINAPI wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
    WNDCLASS WINAPI ClassRegister(LPCWSTR classname, WNDPROC wndproc);
public:
    LPRECT rctScr;
    static bool isOpen;
    HBITMAP BM_Grass;
    HBITMAP BM_Wall;

    HBITMAP BM_RedPortal[11];
    HBITMAP BM_BluePortal[11];
    HBITMAP BM_snaketail;
    HBITMAP BM_snakehead[4];
    HBITMAP BM_meal[3];

    GameWindow();

    DWORD WINAPI StartWindow(HWND parent);

    void setSettings(LPCWSTR wndclassname);
    HDC getDC();
    HWND getHWND();

    void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap);
    void Redraw(int x, int y);
    void StartGame();
    void ResourceLoading();
    void ResourceDestroying();
};

class MainMenu : protected Window
{
private:
    static LRESULT WINAPI wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
    WNDCLASS WINAPI ClassRegister(LPCWSTR classname, WNDPROC wndproc);
public:
    LPRECT rctScr;
    static bool isOpen;

    MainMenu();

    void StartWindow();

    void setSettings(LPCWSTR wndclassname);
    HDC getDC();
    HWND getHWND();
};


#endif // !_WINDOWCLASS

