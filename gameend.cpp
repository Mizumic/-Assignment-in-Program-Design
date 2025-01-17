#define _CRT_SECURE_NO_WARNINGS
#define X 498
#define Y 810
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <graphics.h>
#include<conio.h>
#include<windows.h>
extern int GameEnd;//1是胜利，-1是失败
extern int score; 
char test[100];
char ch;

int Restart();
int end() {
	setbkmode(TRANSPARENT);
	//sprintf_s(test, "GameEnd:%d", GameEnd);
	//outtextxy(100, 600, test);
	//跳出一个结算界面
	if (GameEnd==-1) 
	{
		setlinecolor(BLACK);
		setfillcolor(YELLOW);
		rectangle(80, 130, 400, 520);
		floodfill(85, 135,BLACK);
		// 设置字体
		settextcolor(BLACK);
		settextstyle(25, 0, "Consolas");
		// 输出文字
		char scoreText[20];
		sprintf_s(scoreText, "你的分数是:%d", score);
		outtextxy(100, 150, _T("游戏结束"));
		outtextxy(100, 200, scoreText);
		if (score >= 0 && score <= 250)
		{
			outtextxy(100, 250, _T("就这也想合成中山大学？"));
		}
		else if (score > 250 && score <= 500)
		{
			outtextxy(100, 250, _T("或许刚刚不手贱一下就成功了"));
			outtextxy(100, 300, _T("继续加油！"));
		}
		else if (score > 500 && score <= 1000)
		{
			outtextxy(100, 250, _T("你已经渐入佳境了，继续努力！"));
		}
		else if (score > 1000 && score <= 2000)
		{
			outtextxy(100, 250, _T("你离合成中山大学就差一点点了"));
			outtextxy(100, 300, _T("再尝试一下吧！"));
		}
		else if (score > 2000)
		{
			outtextxy(100, 250, _T("你的分数已经很高了，你是最棒的！"));
		}
		// 设置字体
		settextstyle(15, 0, _T("宋体"));
		// 输出文字
		outtextxy(200, 500, _T("按空格键退出"));
		// 等待按键
		while (1)
		{
			ch = _getch();
			if (ch == ' ')
				break;
			else if (ch == 'R' || ch == 'r')
				Restart();
		}
		// 关闭图形窗口
		closegraph();
	}
	else if (GameEnd == 1)
	{
		setlinecolor(BLACK);
		setfillcolor(YELLOW);
		rectangle(80, 130, 400, 520);
		floodfill(85, 135, BLACK);
		// 设置字体
		settextcolor(BLACK);
		settextstyle(25, 0, "Consolas");
		// 输出文字
		char scoreText[20];
		sprintf_s(scoreText, "你的分数是:%d", score);
		outtextxy(100, 150, _T("恭喜你合成出了中山大学！"));
		outtextxy(100, 200, scoreText);
		// 设置字体
		settextstyle(15, 0, _T("宋体"));
		// 输出文字
		outtextxy(200, 500, _T("按空格键退出"));
		// 等待按键
		while (1)
		{
			ch = _getch();
			if (ch == ' ')
				break;
			else if (ch == 'R' || ch == 'r')
			{
				Restart();
				break;
			}
		}
		// 关闭图形窗口
		closegraph();
	}
	return 0;
}

int Restart() {
	return 0;
}