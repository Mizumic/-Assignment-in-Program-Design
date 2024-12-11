#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
/*
4.	游戏状态模块2：
状态追踪：胜利/失败
当前分数
方块是否可合并（如2+2可，2+4不可）
得分记录和排行榜
皮肤显示
调用的函数：当前使用的皮肤
提供的全局变量：当前游戏状态，当前分数
*/
int canMerge(int a, int b) {
	return a != 0 && a == b;//如果可以合并，返回1，否则返回0，需要自己调整输入参数
}

int if_win(int game[4][4]) {//应该持续运行，每次移动后调用
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (game[i][j] == 2048)
				return 1;
			if (game[i][j] == 0)
				return 0;
		}
	}
	return 0;
}