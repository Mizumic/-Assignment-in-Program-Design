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
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    //主程序
    initgraph(498, 810);
    screen0();
    menu();
    closegraph();
    return 0;
}