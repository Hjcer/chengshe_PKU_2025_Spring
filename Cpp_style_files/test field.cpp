#include <windows.h>

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps); // 获取设备上下文

            // 绘制一个矩形
            Rectangle(hdc, 50, 50, 200, 150);

            // 绘制一条线
            MoveToEx(hdc, 50, 50, NULL);
            LineTo(hdc, 200, 150);

            // 绘制一个椭圆
            Ellipse(hdc, 250, 50, 400, 150);

            // 填充一个区域
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 创建红色画刷
            SelectObject(hdc, hBrush); // 选择画刷
            Rectangle(hdc, 50, 200, 200, 300); // 填充矩形
            DeleteObject(hBrush); // 删除画刷

            EndPaint(hwnd, &ps); // 释放设备上下文
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"GDIExample";

    // 注册窗口类
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClassExW(&wc);

    // 创建窗口
    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"GDI Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    // 消息循环
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}