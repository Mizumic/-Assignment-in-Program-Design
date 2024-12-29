#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include<windows.h>
#include <iostream>
#include <graphics.h>
#include <mmsystem.h>
#include"picture.cpp"
int main() {
    initgraph(498, 810);
    screen0();
    menu();
    closegraph();
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //在引入了windows.h头文件，并修改编译方式的链接器为windows（窗口界面）后
    //main函数的参数列表可以改为WinMain函数的参数列表
    // 隐藏命令行窗口

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = GameControl; // 指定窗口过程
    wc.hInstance = hInstance; // 程序实例句柄
    wc.lpszClassName = "MyWindowClass"; // 窗口类名
    RegisterClass(&wc); // 注册窗口类

    HWND hwnd = CreateWindow("MyWindowClass", "My Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    //主程序
    initgraph(498, 810);
    IMAGE imageBuffer;
    getimage(&imageBuffer, 0, 0, getmaxx(), getmaxy()); // 捕获整个窗口的图像
    screen0();
    menu(hwnd, msg, wParam, lParam);
    closegraph();
    return 0;
}