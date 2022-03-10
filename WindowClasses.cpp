#include "WindowClass.hpp"
#include "Singleton.hpp"

bool MainMenu::isOpen = false;
bool GameWindow::isOpen = false;

void GameWindow::setSettings(LPCWSTR wndclassname)
{
    wndClassName = wndclassname;
    wndclass = ClassRegister(wndClassName, wndProcessor);
}

DWORD WINAPI GameWindow::StartWindow(HWND parent)
{
    GameWindow::isOpen = true;
    rctScr = (LPRECT)malloc(sizeof(*rctScr));
    GetClientRect(GetDesktopWindow(), rctScr);

    hwnd = CreateWindow(wndclass.lpszClassName, L"My Game Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        (rctScr->right / 2), (rctScr->bottom / 4 - 200), 400, 400,
        parent, NULL, NULL, NULL);

    MSG msg;

    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    free(rctScr);
    GameWindow::isOpen = false;
    ShowWindow(Singleton::getMainMenu()->hwnd, SW_SHOW);
    return 0;
}

WNDCLASS WINAPI GameWindow::ClassRegister(LPCWSTR classname, WNDPROC wndproc)
{
    WNDCLASS wclass;
    memset(&wclass, 0, sizeof(WNDCLASS));
    wclass.hbrBackground =
        CreateSolidBrush(RGB(240, 240, 240));
    //CreateSolidBrush(RGB(220,220,220));
    wclass.hIcon = LoadIcon(NULL, IDI_QUESTION);
    wclass.style = (CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW);
    wclass.hCursor = LoadCursor(NULL, IDC_HAND);
    wclass.lpfnWndProc = wndproc;
    wclass.lpszClassName = classname;
    RegisterClass(&wclass);
    return wclass;
}

LRESULT WINAPI GameWindow::wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (Msg == WM_DESTROY)
        PostQuitMessage(0);
    else if (Msg == WM_KEYDOWN)
    {

    }
    else if (Msg == WM_CHAR)
    {
        cout << "GameWindow: " << (char)wParam << endl;
    }
    else if (Msg == WM_SIZE)
    {

    }
    else if (Msg == WM_MOVE)
    {

    }
    else if (Msg == WM_LBUTTONDOWN)
    {

    }
    else if (Msg == WM_MOUSEMOVE)
    {

    }
    else if (Msg == WM_COMMAND)
    {

    }
    else return DefWindowProc(hWnd, Msg, wParam, lParam);
}

/* Main menu class */
//class MainMenu : protected Window
//{
//private:
//    static LRESULT WINAPI wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
//    WNDCLASS WINAPI ClassRegister(LPCWSTR classname, WNDPROC wndproc);
//public:
//    LPCWSTR wndClassName;
//    HWND hwnd;
//    HDC wDC;
//    WNDCLASS wndclass;
//    LPRECT rctScr;
//    static bool first;
//
//    
//
//    
//};

void MainMenu::setSettings(LPCWSTR wndclassname)
{
    wndClassName = wndclassname;
    wndclass = ClassRegister(wndClassName, wndProcessor);
}

void MainMenu::StartWindow()
{
    rctScr = (LPRECT)malloc(sizeof(*rctScr));
    GetClientRect(GetDesktopWindow(), rctScr);

    hwnd = CreateWindow(wndclass.lpszClassName, L"My Main Menu",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        (rctScr->right / 2) - 300, (rctScr->bottom / 4 - 200), 600, 800,
        NULL, NULL, NULL, NULL);

    MSG msg;

    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    free(rctScr);
}

WNDCLASS WINAPI MainMenu::ClassRegister(LPCWSTR classname, WNDPROC wndproc)
{
    WNDCLASS wclass;
    memset(&wclass, 0, sizeof(WNDCLASS));
    wclass.hbrBackground =
        CreateSolidBrush(RGB(240, 240, 240));
    //CreateSolidBrush(RGB(220,220,220));
    wclass.hIcon = LoadIcon(NULL, IDI_QUESTION);
    wclass.style = (CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW);
    wclass.hCursor = LoadCursor(NULL, IDC_HAND);
    wclass.lpfnWndProc = wndproc;
    wclass.lpszClassName = classname;
    RegisterClass(&wclass);
    return wclass;
}

LRESULT WINAPI MainMenu::wndProcessor(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (Msg == WM_DESTROY)
        PostQuitMessage(0);
    else if (Msg == WM_KEYDOWN)
    {

    }
    else if (Msg == WM_CHAR)
    {
        if (wParam == VK_RETURN)
        {
            if (!Singleton::getGameWindow()->isOpen)
            {
                ShowWindow(Singleton::getMainMenu()->hwnd, SW_HIDE);
                Singleton::getGameWindow()->StartWindow(Singleton::getMainMenu()->hwnd);
            }
        }
        cout << "MainWindow: " << (char)wParam << endl;
    }
    else if (Msg == WM_SIZE)
    {

    }
    else if (Msg == WM_MOVE)
    {

    }
    else if (Msg == WM_LBUTTONDOWN)
    {

    }
    else if (Msg == WM_MOUSEMOVE)
    {

    }
    else if (Msg == WM_COMMAND)
    {

    }
    else return DefWindowProc(hWnd, Msg, wParam, lParam);
}