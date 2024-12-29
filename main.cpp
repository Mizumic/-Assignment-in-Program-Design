#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include<windows.h>
#include <iostream>
#include <graphics.h>
#include <mmsystem.h>
#include<process.h>
#include"picture.cpp"
#include"music.cpp"
// 声明线程函数
DWORD WINAPI MusicThread(LPVOID lpParam);
DWORD WINAPI ScreenAndMenuThread(LPVOID lpParam);
DWORD WINAPI GameThread(LPVOID lpParam);
//int game();
extern bool GameStart;

int main() {
    HANDLE hMusicThread, hScreenAndMenuThread,hGameThread;
    DWORD threadId1, threadId2,threadId3;

    // 初始化图形窗口
    initgraph(498, 810);

    // 创建音乐播放线程
    hMusicThread = CreateThread(
        NULL,                   // 默认安全属性
        0,                      // 使用默认堆栈大小  
        MusicThread,            // 线程函数名称
        NULL,                   // 参数传递给线程函数 
        0,                      // 立即运行线程 
        &threadId1);            // 返回线程标识符 

    if (hMusicThread == NULL) {
        printf("CreateThread failed (%d).\n", GetLastError());
        closegraph();
        return 1;
    }

    // 创建屏幕和菜单显示线程
    hScreenAndMenuThread = CreateThread(
        NULL,                   // 默认安全属性
        0,                      // 使用默认堆栈大小  
        ScreenAndMenuThread,    // 线程函数名称
        NULL,                   // 参数传递给线程函数 
        0,                      // 立即运行线程 
        &threadId2);            // 返回线程标识符 

    if (hScreenAndMenuThread == NULL) {
        printf("CreateThread failed (%d).\n", GetLastError());
        CloseHandle(hMusicThread);
        closegraph();
        return 1;
    }

	// 创建游戏线程
    hGameThread = CreateThread(
        NULL,                   // 默认安全属性
        0,                      // 使用默认堆栈大小  
        GameThread,             // 线程函数名称
        NULL,                   // 参数传递给线程函数 
        0,                      // 立即运行线程 
        &threadId3);            // 返回线程标识符 

    if (hGameThread == NULL) {
        printf("CreateThread failed (%d).\n", GetLastError());
        CloseHandle(hMusicThread);
        closegraph();
        return 1;
    }

    // 等待线程完成
    WaitForSingleObject(hMusicThread, INFINITE);
    WaitForSingleObject(hScreenAndMenuThread, INFINITE);
    WaitForSingleObject(hGameThread, INFINITE);

    // 关闭线程句柄
    CloseHandle(hMusicThread);
    CloseHandle(hScreenAndMenuThread);
	CloseHandle(hGameThread);

    // 关闭图形窗口
    closegraph();

    return 0;
}

// 音乐线程函数
DWORD WINAPI MusicThread(LPVOID lpParam) {
    Music();
    return 0;
}

// 屏幕和菜单线程函数
DWORD WINAPI ScreenAndMenuThread(LPVOID lpParam) {
    screen0();
    menu();
    return 0;
}

DWORD WINAPI GameThread(LPVOID lpParam) {
    printf("Nothing here");
	return 0;
}




//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    //在引入了windows.h头文件，并修改编译方式的链接器为windows（窗口界面）后
//    //main函数的参数列表可以改为WinMain函数的参数列表
//    // 隐藏命令行窗口
//    HWND hwnd = GetConsoleWindow();
//    ShowWindow(hwnd, SW_HIDE);
//    Music();
//    //主程序
//    initgraph(498, 810);
//    IMAGE imageBuffer;
//    getimage(&imageBuffer, 0, 0, getmaxx(), getmaxy()); // 捕获整个窗口的图像
//    screen0();
//    menu();
//    closegraph();
//    return 0;
//}