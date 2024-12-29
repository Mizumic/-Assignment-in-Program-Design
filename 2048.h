#pragma once
#define MAX_GRID 4 // 4x4网格
#define FRAME_X 10
#define FRAME_Y 199
#define FRAME_WIDTH 466 // 476 - 10（左右边距）
#define FRAME_HEIGHT 454 // 653 - 199（上下边距）
#define INTERVAL 10 // 格子间隔
#define GRID_WIDTH (FRAME_WIDTH / MAX_GRID)
#define GRID_HEIGHT (FRAME_HEIGHT / MAX_GRID)

enum Color {
    zero = RGB(205, 193, 180), //0的颜色
    twoTo1 = RGB(238, 228, 218), //1的颜色
    twoTo2 = RGB(237, 224, 200), //2的颜色
    twoTo3 = RGB(237, 177, 121), //3的颜色
    twoTo4 = RGB(245, 149, 99), //4的颜色
    twoTo5 = RGB(246, 124, 95), //5的颜色
    twoTo6 = RGB(246, 94, 59), //6的颜色
    twoTo7 = RGB(242, 177, 121), //7的颜色
    twoTo8 = RGB(237, 204, 97), //8的颜色
    twoTo9 = RGB(225, 9, 128), //9的颜色
    twoTo10 = RGB(145, 6, 72), //10的颜色
    twoTo11 = RGB(242, 17, 158), //11的颜色
    back = RGB(187, 173, 160), //背景颜色

};

Color arr[13] = { zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back };//设置颜色数组
int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int map[MAX_GRID][MAX_GRID];//全局变量自动化为0,map数组用于存储各个格子里的值
POINT pos[MAX_GRID][MAX_GRID];//结构体保存每个格子左上角的坐标
bool flag = false;
//定义函数，随机返回2/4
int twoOrFour()
{
    if (rand() % 10 == 0)
    {
        return 4;
    }
    else {
        return 2;
    }
}
//在数组的随机位置产生，把数放到数组里
void CreateNumber()
{
    while (1)
    {
        //确保生成的随机数要在数为0的框内
        int x = rand() % MAX_GRID;
        int y = rand() % MAX_GRID;
        if (map[x][y] == 0)
        {
            map[x][y] = twoOrFour();
            break;
        }
    }

}



int score = 0, highScore = 0;
void updateScore(int value)
{
    score = score + value;//将合并的数值加到分数上
}
void updateHighScore()
{
    if (score > highScore)
        highScore = score;//更新最高分数
}

void resetScore()
{
    score = 0;
}




void GameInit() {
    srand(GetTickCount());
    for (int i = 0; i < MAX_GRID; i++) {
        for (int k = 0; k < MAX_GRID; k++) {
            pos[i][k].x = FRAME_X + k * GRID_WIDTH + k * INTERVAL;
            pos[i][k].y = FRAME_Y + i * GRID_HEIGHT + i * INTERVAL;
        }
    }
    CreateNumber();
    CreateNumber();
    resetScore();
}
void GameDraw() {
    setlinecolor(BLACK); // 设置线条颜色为黑色
    rectangle(FRAME_X, FRAME_Y, FRAME_X + FRAME_WIDTH, FRAME_Y + FRAME_HEIGHT); // 绘制游戏框

    for (int i = 0; i < MAX_GRID; i++) {
        for (int k = 0; k < MAX_GRID; k++) {
            for (int q = 0; q < 12; q++) {
                if (map[i][k] == num[q]) {
                    setfillcolor(arr[q]);
                    solidrectangle(pos[i][k].x, pos[i][k].y, pos[i][k].x + GRID_WIDTH, pos[i][k].y + GRID_HEIGHT);
                    if (map[i][k] != 0) {
                        char number[5] = " ";
                        settextcolor(BLACK);
                        settextstyle(30, 0, "Consolas");
                        setbkmode(TRANSPARENT);
                        sprintf_s(number, "%d", map[i][k]);
                        int tempx = GRID_WIDTH / 2 - textwidth(number) / 2;
                        int tempy = GRID_HEIGHT / 2 - textheight(number) / 2;
                        outtextxy(pos[i][k].x + tempx, pos[i][k].y + tempy, number);
                    }
                }
            }
        }
    }
    setfillcolor(back);//使用背景色
    solidrectangle(250, 0, 446, 25);
    solidrectangle(250, 25, 446, 50);

    char scoreText[20];
    sprintf_s(scoreText, "Score:%d", score);
    settextstyle(24, 0, "Consolas");
    settextcolor(WHITE);//设置文本颜色
    outtextxy(260, 0, scoreText);
    char highScoreText[20];
    sprintf_s(highScoreText, "Highest Score:%d", highScore);
    settextstyle(20, 0, "Consolas");
    settextcolor(WHITE);//设置文本颜色
    outtextxy(260, 25, highScoreText);
}







//上移
void moveup()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; begin++)
        {
            if (map[begin][i] != 0)
            {
                if (map[temp][i] == 0)
                {
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;//对纵列进行变化
                }
                else if (map[temp][i] == map[begin][i])
                {
                    updateScore(map[temp][i] * 2);//更新分数
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                }
                else
                {
                    map[temp + 1][i] = map[begin][i];
                    if (temp + 1 != begin)
                    {
                        map[begin][i] = 0;
                    }

                }
                temp++;
                flag = true;

            }
        }

    }
}
//下移
void movedown()
{
    for (int i = MAX_GRID - 1; i >= 0; i--)
    {
        int temp = MAX_GRID - 1;
        for (int begin = MAX_GRID - 2; begin >= 0; begin--)
        {
            if (map[begin][i] != 0)
            {
                if (map[temp][i] == 0)
                {
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;
                }
                else if (map[temp][i] == map[begin][i])
                {
                    updateScore(map[temp][i] * 2);//更新分数
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                }
                else
                {
                    map[temp - 1][i] = map[begin][i];
                    if (temp - 1 != begin)
                    {
                        map[begin][i] = 0;
                    }
                }
                temp--;
                flag = true;
            }
        }
    }
}
// 左移
void moveleft()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; begin++)
        {
            if (map[i][begin] != 0)
            {
                if (map[i][temp] == 0)
                {
                    map[i][temp] = map[i][begin];
                    map[i][begin] = 0;
                }
                else if (map[i][temp] == map[i][begin])
                {
                    updateScore(map[i][begin] * 2);//更新分数
                    map[i][temp] += map[i][begin];
                    map[i][begin] = 0;
                }
                else
                {
                    map[i][temp + 1] = map[i][begin];
                    if (temp + 1 != begin)
                    {
                        map[i][begin] = 0;
                    }
                }
                temp++;
                flag = true;
            }
        }
    }
}
void moveright()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = MAX_GRID - 1;
        for (int begin = MAX_GRID - 2; begin >= 0; begin--)
        {
            if (map[i][begin] != 0)
            {
                if (map[i][temp] == 0)
                {
                    map[i][temp] = map[i][begin];
                    map[i][begin] = 0;
                }
                else if (map[i][temp] == map[i][begin])
                {
                    updateScore(map[i][begin] * 2);//更新分数
                    map[i][temp] += map[i][begin];
                    map[i][begin] = 0;
                }
                else
                {
                    map[i][temp - 1] = map[i][begin];
                    if (temp - 1 != begin)
                    {
                        map[i][begin] = 0;
                    }
                }
                temp--;
                flag = true;
            }
        }
    }
}
void GameJudge()
{
    if (flag)
    {
        CreateNumber();
        flag = false;
    }
}
//实现键盘控制
void GameControl()
{
    //获取键盘输入
    char key = _getch();
    switch (key)
    {
    case'w':
    case'W':
    case 72:
        moveup();
        break;
    case's':
    case'S':
    case 80:
        movedown();
        break;
    case 'a':
    case'A':
    case 75:
        moveleft();
        break;
    case'd':
    case'D':
    case 77:
        moveright();
        break;
    }
}

