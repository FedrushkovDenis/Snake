#include "..\WindowClasses\WindowClass.hpp"
#include "..\Singleton\Singleton.hpp"
#include "..\Game\Game.hpp"
#include "..\resource.h"
#include "..\Stuff.hpp"
#include <wchar.h>
#include <corecrt_wstdlib.h>

using namespace std;

bool GameWindow::isOpen = false;

GameWindow::GameWindow() {}

HDC GameWindow::getDC() { return windowDC; };

HWND GameWindow::getHWND() { return hwnd; }

void GameWindow::setSettings(LPCWSTR wndclassname)
{
    wndClassName = wndclassname;
    wndclass = ClassRegister(wndClassName, wndProcessor);
}

void GameWindow::ResourceLoading()
{
    BM_Wall = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 32, 32, NULL);
    BM_Grass = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 32, 32, NULL);

    // Red Portal resources
    for (int i = 0; i < 11; i++)
    {
        BM_RedPortal[i] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP3 + i), IMAGE_BITMAP, 32, 32, NULL);
    }

    // Blue Portal resources
    for (int i = 0; i < 11; i++)
    {
        BM_BluePortal[i] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP14 + i), IMAGE_BITMAP, 32, 32, NULL);
    }
    BM_snaketail = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP25), IMAGE_BITMAP, 32, 32, NULL);

    
    // Snake head direction sprites
    // Up
    BM_snakehead[0] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP26), IMAGE_BITMAP, 32, 32, NULL);
    // Left
    BM_snakehead[1] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP27), IMAGE_BITMAP, 32, 32, NULL);
    // Down
    BM_snakehead[2] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP28), IMAGE_BITMAP, 32, 32, NULL);
    // Right
    BM_snakehead[3] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP29), IMAGE_BITMAP, 32, 32, NULL);

    
    BM_meal[0] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP30), IMAGE_BITMAP, 32, 32, NULL); // Banan texture
    BM_meal[1] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP31), IMAGE_BITMAP, 32, 32, NULL); // Grape texture
    BM_meal[2] = (HBITMAP)LoadImage(Singleton::hInst, MAKEINTRESOURCE(IDB_BITMAP32), IMAGE_BITMAP, 32, 32, NULL); // Apple texture
}

void GameWindow::ResourceDestroying()
{
    DeleteObject(BM_Wall);
    DeleteObject(BM_Grass);

    for (short i = 0; i < 11; i++)
    {
        DeleteObject(BM_RedPortal[i]);
    }
    for (short i = 0; i < 11; i++)
    {
        DeleteObject(BM_BluePortal[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        DeleteObject(BM_meal[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        DeleteObject(BM_snakehead[i]);
    }

    DeleteObject(BM_snaketail);
}

DWORD WINAPI GameWindow::StartWindow(HWND parent)
{
    GameWindow::isOpen = true;
    rctScr = (LPRECT)malloc(sizeof(*rctScr));
    GetClientRect(GetDesktopWindow(), rctScr);

    hwnd = CreateWindow(wndclass.lpszClassName, L"My Game Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        (rctScr->right / 2) - 400, (rctScr->bottom / 4 - 200), 800, 800,
        parent, NULL, NULL, NULL);

    ResourceLoading();

    windowDC = GetDC(hwnd);

    Redraw(32, 32);
    StartGame();

    MSG msg;

    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Game* myGame = Singleton::getGame();
            if (Singleton::getGame()->UserControl('W', 'S', 'A', 'D'))
            {
                myGame->resetPoints();
                myGame->snake.Init(3, 8, dirDown);
                myGame->snake.addTailSegment(3, 4);
                myGame->snake.addTailSegment(3, 5);
                myGame->snake.addTailSegment(3, 6);
                myGame->snake.addTailSegment(3, 7);
            }
            myGame->field.clearField();

            myGame->snake.drawOnMap();
            Singleton::getGameWindow()->Redraw(32, 32);
            Sleep(100);
        }
    }
    free(rctScr);
    ResourceDestroying();
    GameWindow::isOpen = false;
    ShowWindow(Singleton::getMainMenu()->getHWND(), SW_SHOW);
    return 0;
}

void GameWindow::StartGame()
{
    Game* myGame = Singleton::getGame();

    myGame->snake.ConnectToMap(myGame->field.getCharField());

    myGame->snake.Init(3, 8, dirDown);
    myGame->snake.addTailSegment(3, 4);
    myGame->snake.addTailSegment(3, 5);
    myGame->snake.addTailSegment(3, 6);
    myGame->snake.addTailSegment(3, 7);

    myGame->field.CreatePortals();

    for (short i = 0; i < PORTALCOUNT; i++)
    {
        myGame->field.addPortal(myGame->field.getPortals()[i]);
    }

    myGame->field.addFruit(10, 10);
    myGame->field.addFruit(12, 12);
    myGame->field.addFruit(14, 14);

    myGame->snake.drawOnMap();
}

void GameWindow::Redraw(int x, int y)
{
    HDC memDC = CreateCompatibleDC(windowDC);
    HBITMAP memBM = CreateCompatibleBitmap(windowDC, rctScr->right - rctScr->left, rctScr->bottom - rctScr->top);

    SelectObject(memDC, memBM);
    SelectObject(memDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(memDC, RGB(255, 255, 255));
    SelectObject(memDC, GetStockObject(DC_PEN));
    SetDCPenColor(memDC, RGB(255, 255, 255));
    Rectangle(memDC, 0, 0, 1920, 1080);
    
    // Points render
    WCHAR buf[20];
    int result = Singleton::getGame()->getPoints();
    _itow_s(result, buf, 10);
    TextOut(memDC, (rctScr->right/5)+20, 15, buf, (result/10)+1);


    static int BMRP_tickrate = 0; // tickrate to drawing BitMap Red Portal (BMRP)
    static int BMRP_order = 0;    // frame counter for BMBP
    static int BMRP_times = 0;    // Synchronization mech to draw frame every 2 ticks, not one

    static int BMBP_tickrate = 0; // tickrate to drawing BitMap Blue Portal (BMBP)
    static int BMBP_order = 0;    // etc...
    static int BMBP_times = 0;
    
    int curX = x;
    int curY = y;

    for (short i = 0; i < ROWS; i++)
    {
        curX = x;
        for (short j = 0; j < COLUMNS; j++)
        {
            if (Singleton::getGame()->field.getCharField()[i][j] == '#')
                DrawBitmap(memDC, curX, curY, BM_Wall);
            if (Singleton::getGame()->field.getCharField()[i][j] == REDPORTAL)
            {
                DrawBitmap(memDC, curX, curY, BM_RedPortal[0]);
                if (BMRP_tickrate >= 30)
                {
                    DrawBitmap(memDC, curX, curY, BM_RedPortal[BMRP_order]);
                    BMRP_times++;
                    if (BMRP_times % 2 == 0 && BMRP_times != 0)
                    {
                        BMRP_order++;
                    }
                }
                if (BMRP_order > 10)
                {
                    BMRP_tickrate = 0;
                    BMRP_order = 0;
                    BMRP_times = 0;
                }
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == BLUEPORTAL)
            {
                DrawBitmap(memDC, curX, curY, BM_BluePortal[0]);
                if (BMBP_tickrate >= 45)
                {
                    DrawBitmap(memDC, curX, curY, BM_BluePortal[BMBP_order]);
                    BMBP_times++;
                    if (BMBP_times % 2 == 0 && BMBP_times != 0)
                    {
                        BMBP_order++;
                    }
                }
                if (BMBP_order > 10)
                {
                    BMBP_tickrate = 0;
                    BMBP_order = 0;
                    BMBP_times = 0;
                }
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == TAIL)
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_snaketail);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == FRUIT1)
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_meal[0]);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == FRUIT2)
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_meal[1]);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == FRUIT3)
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_meal[2]);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == 'A')
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_snakehead[0]);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == '<')
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_snakehead[1]);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == 'V')
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_snakehead[2]);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == '>')
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
                DrawBitmap(memDC, curX, curY, BM_snakehead[3]);
            }
            else if (Singleton::getGame()->field.getCharField()[i][j] == ' ')
            {
                DrawBitmap(memDC, curX, curY, BM_Grass);
            }
            curX += 32;
        }
        curY += 32;
    }

    BitBlt(windowDC, 0, 0, rctScr->right - rctScr->left, rctScr->bottom - rctScr->top, memDC, 0, 0, SRCCOPY);

    DeleteDC(memDC);
    DeleteObject(memBM);
    BMRP_tickrate++;
    BMBP_tickrate++;
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
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(Singleton::getGameWindow()->getHWND());
        }
        Game* myGame = Singleton::getGame();
        if (Singleton::getGame()->UserControl('W', 'S', 'A', 'D'))
        {
            myGame->snake.Init(3, 8, dirDown);
            myGame->snake.addTailSegment(3, 4);
            myGame->snake.addTailSegment(3, 5);
            myGame->snake.addTailSegment(3, 6);
            myGame->snake.addTailSegment(3, 7);
        }
        myGame->field.clearField();

        myGame->snake.drawOnMap();
        Singleton::getGameWindow()->Redraw(32, 32);
        Sleep(100);
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

void GameWindow::DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
    HBITMAP hOldbm;
    HDC hMemDC;
    BITMAP bm;
    POINT  ptSize, ptOrg;

    // Создаем контекст памяти, совместимый
    // с контекстом отображения
    hMemDC = CreateCompatibleDC(hDC);

    // Выбираем изображение bitmap в контекст памяти
    hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // Если не было ошибок, продолжаем работу
    if (hOldbm)
    {
        // Для контекста памяти устанавливаем тот же
        // режим отображения, что используется в
        // контексте отображения
        SetMapMode(hMemDC, GetMapMode(hDC));

        // Определяем размеры изображения
        GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

        ptSize.x = bm.bmWidth;   // ширина
        ptSize.y = bm.bmHeight;  // высота

        // Преобразуем координаты устройства в логические
        // для устройства вывода
        DPtoLP(hDC, &ptSize, 1);

        ptOrg.x = 0;
        ptOrg.y = 0;

        // Преобразуем координаты устройства в логические
        // для контекста памяти
        DPtoLP(hMemDC, &ptOrg, 1);

        //BitBlt(hDC, x, y, ptSize.x, ptSize.y, hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

        GdiTransparentBlt(hDC, x, y, ptSize.x, ptSize.y, hMemDC, 0, 0, ptSize.x, ptSize.y, RGB(255, 255, 255));

        // Восстанавливаем контекст памяти
        SelectObject(hMemDC, hOldbm);
    }

    // Удаляем контекст памяти
    DeleteDC(hMemDC);
}





/* Main menu class */

bool MainMenu::isOpen = false;

MainMenu::MainMenu() {}

HDC MainMenu::getDC() { return windowDC; };

HWND MainMenu::getHWND() { return hwnd; }

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
        else Sleep(100);
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