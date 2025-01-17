//默认0，1，2，3，4代指nx南校，bx,北校，dx东校，zh珠海，sz深圳
//注意button结尾，s start, e exchange, x exit, m music.
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include <bits/stdc++.h>
#include <iostream>
#include <graphics.h>
#include <conio.h> // 用于_getch()函数
#include <cstdlib>
#include <ctime>
#include "2048.h"
#include <iostream>
#pragma comment( lib, "MSIMG32.LIB")

int GameStart=0;
IMAGE imageBuffer;

void transparentimage1(IMAGE img,int x, int y) {
    IMAGE img1;
    DWORD* d1;
    img1 = img;
    d1 = GetImageBuffer(&img1);
    float h, s, l;
    for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
        RGBtoHSL(BGR(d1[i]), &h, &s, &l);
        if (l < 1e-10) {
            d1[i] = BGR(WHITE);
        }
        if (d1[i] != BGR(WHITE)) {
            d1[i] = 0;
        }
    }
    putimage(x, y, &img1, SRCAND);
    putimage(x, y, &img, SRCPAINT);
}

void transparentimage2(IMAGE img, int x, int y) {
    IMAGE img1;
    DWORD* d1;
    img1 = img;
    d1 = GetImageBuffer(&img1);
    float h, s, l;
    for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
        RGBtoHSL(BGR(d1[i]), &h, &s, &l);
        if (l < 0.03) {
            d1[i] = BGR(WHITE);
        }
        if (d1[i] != BGR(WHITE)) {
            d1[i] = 0;
        }
    }
    putimage(x, y, &img1, SRCAND);
    putimage(x, y, &img, SRCPAINT);
}



char GetChar()//输入一个字符（非空格、非回车、ASCII码大于零）
{
    char c;
    do
    {
        c = getchar();
    } while (c == '\n' || c == ' ' || c < 0);
    return c;
}

struct Button {
    IMAGE normal, hover, down;
    int x, y, width, height;
    bool isHover, isDown;
};
//定义按钮，三张图片分别为点击前，鼠标在上方，点击后，x,y为坐标
void initButton(Button& btn, const char* normalPath, const char* hoverPath, const char* downPath, int x, int y, int width, int height) {
    loadimage(&btn.normal, normalPath, width, height);
    loadimage(&btn.hover, hoverPath, width, height);
    loadimage(&btn.down, downPath, width, height);
    btn.x = x;
    btn.y = y;
    btn.width = width;
    btn.height = height;
    btn.isHover = false;
    btn.isDown = false;
}
//画出按钮
void drawButton(Button& btn) {
    if (btn.isDown) {
        putimage(btn.x, btn.y, &btn.down);
        Sleep(50);
    }
    else if (btn.isHover)
        putimage(btn.x, btn.y, &btn.hover);
    else putimage(btn.x, btn.y, &btn.normal);
}
//判断鼠标是否位于按钮上方
bool isMouseOnButton(Button& btn, int x, int y) {
    return x >= btn.x && x <= btn.x + btn.width && y >= btn.y && y <= btn.y + btn.height;
}
//按钮状态函数
void updateButtonState(Button& btn, MOUSEMSG& msg) {
    bool isOnButton = isMouseOnButton(btn, msg.x, msg.y);
    switch (msg.uMsg) {
    case WM_LBUTTONDOWN:
        btn.isDown = isOnButton; // 当鼠标按下时，如果鼠标在按钮上，则设置isDown为true
        btn.isHover = false; // 按下时取消hover状态
        break;
    case WM_LBUTTONUP:
        btn.isDown = false; // 当鼠标释放时，取消按下状态
        if (isOnButton) {
            btn.isHover = true; // 如果鼠标释放时还在按钮上，则设置为hover状态
        }
        else {
            btn.isHover = false; // 否则取消hover状态
        }
        break;
    case WM_MOUSEMOVE:
        btn.isHover = isOnButton; // 当鼠标移动时，如果鼠标在按钮上，则设置为hover状态
        btn.isDown = false; // 移动时取消按下状态
        break;
    default:
        // 其他情况不改变状态
        break;
    }
}
//重置按钮状态
void resetButtonStates(Button& startGameButton, Button& changeBkButton, Button& showRuleButton, Button& quitGameButton) {
    startGameButton.isHover = false;
    startGameButton.isDown = false;
    changeBkButton.isHover = false;
    changeBkButton.isDown = false;
    showRuleButton.isHover = false;
    showRuleButton.isDown = false;
    quitGameButton.isHover = false;
    quitGameButton.isDown = false;
}

void screen0() {
    IMAGE background;
    loadimage(&background, _T("gamefilepics\\nx0.png"), 498, 810);
    putimage(0, 0, &background);
}

void screen1() {
    IMAGE background;
    loadimage(&background, _T("gamefilepics\\bx0.png"), 498, 810);
    putimage(0, 0, &background);
}

void screen2() {
    IMAGE background;
    loadimage(&background, _T("gamefilepics\\dx0.png"), 498, 810);
    putimage(0, 0, &background);
}

void screen3() {
    IMAGE background;
    loadimage(&background, _T("gamefilepics\\zh0.png"), 498, 810);
    putimage(0, 0, &background);
}

void screen4() {
    IMAGE background;
    loadimage(&background, _T("gamefilepics\\sz0.png"), 498, 810);
    putimage(0, 0, &background);
}
//打印屏幕
void printscreen(int Bktype) {
    switch (Bktype) {
    case 0:
        screen0();
        break;
    case 1:
        screen1();
        break;
    case 2:
        screen2();
        break;
    case 3:
        screen3();
        break;
    case 4:
        screen4();
        break;
    }
}
//更换背景，已完成
int chageBk(int* Bktype, int* Buttontype) {
    cleardevice();
    printscreen(*Bktype);
    Button nx, bx, dx, zh, sz, back;
    initButton(nx, "gamefilepics\\button\\button nx.png", "gamefilepics\\button\\button nx.png", "gamefilepics\\button\\button nx1.png", 150, 200, 214, 57);
    initButton(bx, "gamefilepics\\button\\button bx.png", "gamefilepics\\button\\button bx.png", "gamefilepics\\button\\button bx1.png", 150, 300, 214, 57);
    initButton(dx, "gamefilepics\\button\\button dx.png", "gamefilepics\\button\\button dx.png", "gamefilepics\\button\\button dx1.png", 150, 400, 214, 57);
    initButton(zh, "gamefilepics\\button\\button zh.png", "gamefilepics\\button\\button zh.png", "gamefilepics\\button\\button zh1.png", 150, 500, 214, 57);
    initButton(sz, "gamefilepics\\button\\button sz.png", "gamefilepics\\button\\button sz.png", "gamefilepics\\button\\button sz1.png", 150, 600, 214, 57);
    initButton(back, "gamefilepics\\button\\backw.png", "gamefilepics\\back.png", "gamefilepics\\button\\backc.png", 0 , 0, 60, 50);
    MOUSEMSG msg{};
    bool running = true;
    while (running) {
        drawButton(nx);
        drawButton(bx);
        drawButton(dx);
        drawButton(zh);
        drawButton(sz);

        if (*Buttontype == 0) {
            transparentimage1(back.normal, 0, 5);
        }
        if (*Buttontype == 1) {
            transparentimage1(back.down, 0, 5);
        }
        while (msg.uMsg != WM_LBUTTONUP) {
            msg = GetMouseMsg();
            updateButtonState(nx, msg);
            updateButtonState(bx, msg);
            updateButtonState(dx, msg);
            updateButtonState(zh, msg);
            updateButtonState(sz, msg);
            updateButtonState(back, msg);
            if (isMouseOnButton(nx, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                *Bktype = 0;
                *Buttontype = 0;
                running = false; // 返回主菜单
            }
            if (isMouseOnButton(bx, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                *Bktype = 1;
                *Buttontype = 0;
                running = false; // 返回主菜单
            }
            if (isMouseOnButton(dx, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                *Bktype = 2;
                *Buttontype = 1;
                running = false; // 返回主菜单
            }
            if (isMouseOnButton(zh, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                *Bktype = 3;
                *Buttontype = 1;
                running = false; // 返回主菜单
            }
            if (isMouseOnButton(sz, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                *Bktype = 4;
                *Buttontype = 0;
                running = false; // 返回主菜单
            }
            if (isMouseOnButton(back, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                running = false; // 返回主菜单
            }
        }
        // 重置所有按钮的状态
        nx.isDown = false;
        nx.isHover = false;
        bx.isDown = false;
        bx.isHover = false;
        dx.isDown = false;
        dx.isHover = false;
        zh.isDown = false;
        zh.isHover = false;
        sz.isDown = false;
        sz.isHover = false;
        back.isDown = false;
        back.isHover = false;
    }
    return 0;
}

void preface(int Bktype, int Buttontype, IMAGE& background) {
    cleardevice();
    printscreen(Bktype);
    IMAGE preface;
    Button goon;
    if (Buttontype == 1) {
        loadimage(&preface, "gamefilepics\\rule1.png", 454, 454);//前言框的位置与游戏框的位置一致
        putimage(22, 199, &preface);
        initButton(goon, "gamefilepics\\button\\continue1.png", "\gamefilepics\\button\\continue1.png", "\gamefilepics\\button\\continue1.png", 270, 20, 184, 47);
        MOUSEMSG msg{};
        bool running = true;
        while (running) {
            drawButton(goon);
            while (msg.uMsg != WM_LBUTTONUP) {
                msg = GetMouseMsg();
                updateButtonState(goon, msg);
            }
            // 处理按钮点击事件
            if (isMouseOnButton(goon, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                putimage(0, 0, &background); // 恢复背景
                running = false; // 返回主菜单
            }
            // 重置按钮状态
            goon.isDown = false;
            goon.isHover = false;
        }
    }

    else {
        loadimage(&preface, "\gamefilepics\\rule0.png", 454, 454);//前言框的位置与游戏框的位置一致
        putimage(22, 199, &preface);
        initButton(goon, "\gamefilepics\\button\\continue0.png", "\gamefilepics\\button\\continue0.png", "\gamefilepics\\button\\continue0.png", 270, 20, 184, 47);
        MOUSEMSG msg{};
        bool running = true;
        while (running) {
            drawButton(goon);
            while (msg.uMsg != WM_LBUTTONUP) {
                msg = GetMouseMsg();
                updateButtonState(goon, msg);
            }
            // 处理按钮点击事件
            if (isMouseOnButton(goon, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                putimage(0, 0, &background); // 恢复背景
                running = false; // 返回主菜单
            }
            // 重置按钮状态
            goon.isDown = false;
            goon.isHover = false;
        }
    }
}

// suspendface: 暂停界面，支持后续扩展
void suspendface(int Bktype, int Buttontype, IMAGE& snapshot) {
    // 使用传入的屏幕快照绘制暂停前的界面
    putimage(0, 0, &snapshot);

    // 绘制暂停界面
    IMAGE pause;
    Button goon;

    if (Buttontype == 1) {
        loadimage(&pause, "gamefilepics\\rule1.png", 454, 454);
        putimage(22, 199, &pause);
        initButton(goon, "gamefilepics\\button\\continue1.png",
            "gamefilepics\\button\\continue1.png",
            "gamefilepics\\button\\continue1.png",
            270, 450, 184, 47);
    }
    else {
        loadimage(&pause, "gamefilepics\\rule0.png", 454, 454);
        putimage(22, 199, &pause);
        initButton(goon, "gamefilepics\\button\\continue0.png",
            "gamefilepics\\button\\continue0.png",
            "gamefilepics\\button\\continue0.png",
            270, 450, 184, 47);
    }

    // 暂停界面消息循环
    MOUSEMSG msg{};
    bool running = true;

    while (running) {
        drawButton(goon); // 绘制按钮
        msg = GetMouseMsg();
        updateButtonState(goon, msg); // 更新按钮状态

        if (isMouseOnButton(goon, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
            running = false; // 退出暂停界面
        }
    }

    // 暂停结束时不会清屏，界面恢复由调用方负责
}

// play: 支持暂停后完全恢复界面
void play(int Bktype, int Buttontype,IMAGE background) {
    cleardevice(); // 清屏，准备绘制游戏画面
    printscreen(Bktype); // 绘制背景
    setlinecolor(RED);
    rectangle(22, 199, 476, 653);

    // 初始化按钮
    Button back, suspend;
    initButton(back, "gamefilepics\\button\\backw.png", "gamefilepics\\back.png", "gamefilepics\\button\\backc.png", 0, 0, 60, 50);
    initButton(suspend, "gamefilepics\\button\\suspendw.png", "gamefilepics\\button\\suspend.png", "gamefilepics\\button\\suspendc.png", 430, 0, 50, 50);

    MOUSEMSG msg{};
    bool running = true;

    IMAGE pause;
    loadimage(&pause, "gamefilepics\\button\\suspend.png", 50, 50);

    while (running) {
        if (Buttontype == 0) {
            transparentimage1(back.normal, 0, 5);
            transparentimage1(pause, 450, 5);
        }
        if (Buttontype == 1) {
            transparentimage1(back.down, 0, 5);
            transparentimage1(pause, 450, 5);
        }
        msg = GetMouseMsg();
        updateButtonState(back, msg);
        updateButtonState(suspend, msg);

        // 返回主菜单
        if (isMouseOnButton(back, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
            cleardevice();
            running = false;
        }

        // 暂停界面逻辑
        if (isMouseOnButton(suspend, msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
            // 保存当前屏幕内容
            IMAGE snapshot;
            getimage(&snapshot, 0, 0, getwidth(), getheight()); // 保存屏幕快照

            suspendface(Bktype, Buttontype, snapshot); // 进入暂停界面

            // 暂停后恢复屏幕快照
            putimage(0, 0, &snapshot);

            // 重新绘制界面，刷新动态内容（如按钮）
            if (Buttontype == 0) {
                transparentimage1(back.normal, 0, 5);
                transparentimage1(pause, 450, 5);
            }
            if (Buttontype == 1) {
                transparentimage1(back.down, 0, 5);
                transparentimage1(pause, 450, 5);
            }
        }

        // 重置按钮状态
        back.isDown = false;
        back.isHover = false;
        suspend.isDown = false;
        suspend.isHover = false;

        // 游戏
        GameStart = 1;
    }
}



//为何button有两种？为适配校园不同的颜色，利好眼睛，注意游戏内容函数需要写两遍，分别用于两个Buttontype。
void menu() {
    Button startGameButton, changeBkButton, showRuleButton, quitGameButton;
    Button startGameButton1, changeBkButton1, showRuleButton1, quitGameButton1;
    initButton(startGameButton, "gamefilepics\\button\\button browns 0.png", "gamefilepics\\button\\button browns 1.png", "gamefilepics\\button\\button browns 2.png", 150, 300, 214, 57);
    initButton(changeBkButton, "gamefilepics\\button\\button browne 0.png", "gamefilepics\\button\\button browne 1.png", "gamefilepics\\button\\button browne 2.png", 150, 400, 214, 57);
    initButton(showRuleButton, "gamefilepics\\button\\button brownr 0.png", "gamefilepics\\button\\button brownr 1.png", "gamefilepics\\button\\button brownr 2.png", 150, 500, 214, 57);
    initButton(quitGameButton, "gamefilepics\\button\\button brownx 0.png", "gamefilepics\\button\\button brownx 1.png", "gamefilepics\\button\\button brownx 2.png", 150, 600, 214, 57);

    initButton(startGameButton1, "gamefilepics\\button\\button blues 0.png", "gamefilepics\\button\\button blues 1.png", "gamefilepics\\button\\button blues 2.png", 150, 300, 214, 57);
    initButton(changeBkButton1, "gamefilepics\\button\\button bluee 0.png", "gamefilepics\\button\\button bluee 1.png", "gamefilepics\\button\\button bluee 2.png", 150, 400, 214, 57);
    initButton(showRuleButton1, "gamefilepics\\button\\button bluer 0.png", "gamefilepics\\button\\button bluer 1.png", "gamefilepics\\button\\button bluer 2.png", 150, 500, 214, 57);
    initButton(quitGameButton1, "gamefilepics\\button\\button bluex 0.png", "gamefilepics\\button\\button bluex 1.png", "gamefilepics\\button\\button bluex 2.png", 150, 600, 214, 57);
    int Bktype = 0;
    int Buttontype = 0;
    MOUSEMSG msg{};
    bool running = true;
    IMAGE background;

    // 保存初始背景
    getimage(&background, 0, 0, getwidth(), getheight());

    while (running) {
        cleardevice(); // 清除屏幕
        printscreen(Bktype); // 绘制背景

        // 重置按钮状态应该在每次循环开始时进行
        resetButtonStates(startGameButton, changeBkButton, showRuleButton, quitGameButton);
        resetButtonStates(startGameButton1, changeBkButton1, showRuleButton1, quitGameButton1);

        // 绘制按钮
        Button* buttons[4];
        if (Buttontype == 0) {
            buttons[0] = &startGameButton;
            buttons[1] = &changeBkButton;
            buttons[2] = &showRuleButton;
            buttons[3] = &quitGameButton;
        }
        else if (Buttontype == 1) {
            buttons[0] = &startGameButton1;
            buttons[1] = &changeBkButton1;
            buttons[2] = &showRuleButton1;
            buttons[3] = &quitGameButton1;
        }

        // 绘制按钮
        for (int i = 0; i < 4; ++i) {
            drawButton(*buttons[i]);
        }

        // 处理鼠标消息
        while (true) {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONUP) {
                break; // 一旦检测到鼠标左键释放，退出循环
            }
            // 更新按钮状态
            for (int i = 0; i < 4; ++i) {
                updateButtonState(*buttons[i], msg);
            }
        }

        // 处理按钮点击事件
        for (int i = 0; i < 4; ++i) {
            if (isMouseOnButton(*buttons[i], msg.x, msg.y) && msg.uMsg == WM_LBUTTONUP) {
                if (i == 0) { // Start game button
                    preface(Bktype, Buttontype, background); // 传递背景图像
                    GameStart = 1;
                    play(Bktype, Buttontype, background);
                }
                else if (i == 1) { // Change background button
                    chageBk(&Bktype, &Buttontype);
                }
                else if (i == 2) { // Rule exclaim button
                    IMAGE snapshot;
                    getimage(&snapshot, 0, 0, getwidth(), getheight());
                    suspendface(Bktype, Buttontype, snapshot);
                    putimage(0, 0, &snapshot);
                }
                else if (i == 3) { // Quit game button
                    running = false;
                }
            }
        }
    }
}

struct GameState
{
    int score;
    int bestScore;

};