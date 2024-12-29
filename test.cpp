#define _CRT_SECURE_NO_WARNINGS
#define MAX_GRID 4 // 4x4网格
//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include<string.h>
#include <bits/stdc++.h>
using namespace std;

int gamemap[MAX_GRID][MAX_GRID];//全局变量自动化为0,map数组用于存储各个格子里的值
bool flag = false;

void MoveUp() {//以向上移动为例
	//先进行位移
	for (int y = 0; y < MAX_GRID; y++) 
	{
		flag = 1;
		int x = 1;
		while(flag==1)//在下方格子不全为0时持续运行
		{
			if (gamemap[x - 1][y] == 0)//如果上方格子为空
			{
				gamemap[x - 1][y] = gamemap[x][y];//将当前格子的值赋给上方格子
				gamemap[x][y] = 0;//当前格子清零
				x++;//继续向下移动
			}
			for (int k = x-1; k < MAX_GRID; k++)//检查上一个移动的格子下方是否有数字
			{
				if (gamemap[k][y] != 0)//如果有数字
				{
					break;//说明移动没有结束，跳出循环
				}
				flag = 0;//如果没有数字，说明移动结束，flag设置为0
			}
		}
	}
	//位移结束，开始合并
	for (int y = 0; y < MAX_GRID; y++)
	{
		flag = 1;//每次遍历列时，初始化flag
		int temp = gamemap[0][y];//初始化temp
		if (temp == 0)//如果第一个格子为空
		{
			continue;//说明这一列没有数字，跳过这一列
		}
		if (temp == gamemap[1][y])//如果第一个格子的值等于第二个格子的值
		{
			if (temp == gamemap[2][y])//前三个格子相同
			{
				if (temp == gamemap[3][y]) //四个格子全部相同
				{
					gamemap[0][y] = temp * 2;
					gamemap[1][y] = temp * 2;
					gamemap[2][y] = 0;
					gamemap[3][y] = 0;
					continue;
				}
				else//前三个格子相同
				{
					gamemap[0][y] = temp * 2;
					gamemap[1][y] = gamemap[2][y];
					gamemap[2][y] = gamemap[3][y];
					gamemap[3][y] = 0;
					continue;
				}
			}
			else//前两个格子相同
			{
				temp = gamemap[2][y];
				if (temp == gamemap[3][y])//第三个格子和第四个格子相同
				{
					gamemap[0][y] = gamemap[0][y]*2;
					gamemap[1][y] = temp * 2;
					gamemap[2][y] = 0;
					gamemap[3][y] = 0;
					continue;
				}
				else//前两个格子相同
				{
					gamemap[0][y] = gamemap[0][y];
					gamemap[1][y] = gamemap[2][y];
					gamemap[2][y] = gamemap[3][y];
					gamemap[3][y] = 0;
					continue;
				}
			}
		}
		else//第一个格子和第二个格子不同，从第二个格子再开始检查
		{
			temp = gamemap[1][y];
			if (temp == 0)//第二个格子为空
			{
				continue;//跳过这一列
			}
			if (temp == gamemap[2][y])//如果第二个和第三个相同，说明是合并一次的情况
			{
				gamemap[1][y] = temp * 2;
				gamemap[2][y] = gamemap[3][y];
			}
			else//第二个和第三个不同，从第三个开始检查
			{
				temp = gamemap[2][y];
				if (temp == 0)//第三个为空
				{
					continue;//跳过这一列
				}
				if (temp == gamemap[3][y])//第三个和第四个相同,说明是合并一次的情况，直接执行
				{
					gamemap[2][y] = temp * 2;
					gamemap[3][y] = 0;
				}
			}
		}
	}
}