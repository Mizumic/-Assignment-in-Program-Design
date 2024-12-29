#pragma once
#define MAX_GRID 4 // 4x4网格
#define FRAME_X 10
#define FRAME_Y 199
#define FRAME_WIDTH 466 // 476 - 10（左右边距）
#define FRAME_HEIGHT 454 // 653 - 199（上下边距）
#define INTERVAL 3 // 格子间隔
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
int gamemap[MAX_GRID][MAX_GRID];//全局变量自动化为0,map数组用于存储各个格子里的值
POINT pos[MAX_GRID][MAX_GRID];//结构体保存每个格子左上角的坐标
bool flag = false;
int GameEnd=0;

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
        if (gamemap[x][y] == 0)
        {
            gamemap[x][y] = twoOrFour();
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
                if (gamemap[i][k] == num[q]) {
                    setfillcolor(arr[q]);
                    solidrectangle(pos[i][k].x, pos[i][k].y, pos[i][k].x + GRID_WIDTH, pos[i][k].y + GRID_HEIGHT);
                    if (gamemap[i][k] != 0) {
                        char number[5] = " ";
                        settextcolor(BLACK);
                        settextstyle(30, 0, "Consolas");
                        setbkmode(TRANSPARENT);
                        sprintf_s(number, "%d", gamemap[i][k]);
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
    //solidrectangle(250, 25, 446, 50);

    char scoreText[20];
    sprintf_s(scoreText, "Score:%d", score);
    settextstyle(24, 0, "Consolas");
    settextcolor(WHITE);//设置文本颜色
    outtextxy(260, 0, scoreText);
    //char highScoreText[20];
    //sprintf_s(highScoreText, "Highest Score:%d", highScore);
    //settextstyle(20, 0, "Consolas");
    //settextcolor(WHITE);//设置文本颜色
    //outtextxy(260, 25, highScoreText);
}

//上移
void MoveUp() {
    for (int y = 0; y < MAX_GRID; y++) {
        for (int x = 1; x < MAX_GRID; x++) {
            if (gamemap[x][y] != 0) {
                int targetX = x;
                while (targetX > 0 && gamemap[targetX - 1][y] == 0) {
                    targetX--;
                }
                if (targetX != x) {
                    gamemap[targetX][y] = gamemap[x][y];
                    gamemap[x][y] = 0;
                }
            }
        }
    }

    // 接下来进行合并
    for (int y = 0; y < MAX_GRID; y++) { // 只需要考虑某一列的情况即可
        int x;
        for (x = 0; x < MAX_GRID - 1; x++) {
            if (gamemap[x][y] == gamemap[x + 1][y]) 
            { // 如果和下一个格子数值相同，就合并
                score += gamemap[x][y] * 2;//将合并的数值加到分数上
                gamemap[x][y] *= 2; // 自身乘二
                gamemap[x + 1][y] = 0; // 被吸收为0
                for (int k = x + 1; k < MAX_GRID - 1; k++) { // 从这一格向后遍历，将之后的数字上移
                    gamemap[k][y] = gamemap[k + 1][y];
                }
                gamemap[MAX_GRID - 1][y] = 0; // 将最后一格设置为0
            }
        }
    }
    flag = 1;
}

void MoveDown() {
    for (int y = 0; y < MAX_GRID; y++) {
        for (int x = MAX_GRID - 2; x >= 0; x--) {
            if (gamemap[x][y] != 0) {
                int targetX = x;
                while (targetX < MAX_GRID - 1 && gamemap[targetX + 1][y] == 0) {
                    targetX++;
                }
                if (targetX != x) {
                    gamemap[targetX][y] = gamemap[x][y];
                    gamemap[x][y] = 0;
                }
            }
        }
    }

    // 接下来进行合并
    for (int y = 0; y < MAX_GRID; y++) { // 只需要考虑某一列的情况即可
        int x;
        for (x = MAX_GRID - 1; x > 0; x--) {
            if (gamemap[x][y] == gamemap[x - 1][y]) 
            { // 如果和上一个格子数值相同，就合并
                score += gamemap[x][y] * 2;//将合并的数值加到分数上
                gamemap[x][y] *= 2; // 自身乘二
                gamemap[x - 1][y] = 0; // 被吸收为0
                for (int k = x - 1; k > 0; k--) { // 从这一格向前遍历，将之前的数字下移
                    gamemap[k][y] = gamemap[k - 1][y];
                }
                gamemap[0][y] = 0; // 将第一格设置为0
            }
        }
    }
    flag = 1;
}

void MoveLeft() {
    for (int x = 0; x < MAX_GRID; x++) {
        for (int y = 1; y < MAX_GRID; y++) {
            if (gamemap[x][y] != 0) {
                int targetY = y;
                while (targetY > 0 && gamemap[x][targetY - 1] == 0) {
                    targetY--;
                }
                if (targetY != y) {
                    gamemap[x][targetY] = gamemap[x][y];
                    gamemap[x][y] = 0;
                }
            }
        }
    }

    // 接下来进行合并
    for (int x = 0; x < MAX_GRID; x++) { // 只需要考虑某一行的情况即可
        int y;
        for (y = 0; y < MAX_GRID - 1; y++) {
            if (gamemap[x][y] == gamemap[x][y + 1]) 
            { // 如果和下一个格子数值相同，就合并
                score += gamemap[x][y] * 2;//将合并的数值加到分数上
                gamemap[x][y] *= 2; // 自身乘二
                gamemap[x][y + 1] = 0; // 被吸收为0
                for (int k = y + 1; k < MAX_GRID - 1; k++) { // 从这一格向后遍历，将之后的数字左移
                    gamemap[x][k] = gamemap[x][k + 1];
                }
                gamemap[x][MAX_GRID - 1] = 0; // 将最后一格设置为0
            }
        }
    }
    flag = 1;
}

void MoveRight() {
    for (int x = 0; x < MAX_GRID; x++) {
        for (int y = MAX_GRID - 2; y >= 0; y--) {
            if (gamemap[x][y] != 0) {
                int targetY = y;
                while (targetY < MAX_GRID - 1 && gamemap[x][targetY + 1] == 0) {
                    targetY++;
                }
                if (targetY != y) {
                    gamemap[x][targetY] = gamemap[x][y];
                    gamemap[x][y] = 0;
                }
            }
        }
    }

    // 接下来进行合并
    for (int x = 0; x < MAX_GRID; x++) { // 只需要考虑某一行的情况即可
        int y;
        for (y = MAX_GRID - 1; y > 0; y--) {
            if (gamemap[x][y] == gamemap[x][y - 1]) 
            { // 如果和前一个格子数值相同，就合并
                score += gamemap[x][y] * 2;//将合并的数值加到分数上
                gamemap[x][y] *= 2; // 自身乘二
                gamemap[x][y - 1] = 0; // 被吸收为0
                for (int k = y - 1; k > 0; k--) { // 从这一格向前遍历，将之前的数字右移
                    gamemap[x][k] = gamemap[x][k - 1];
                }
                gamemap[x][0] = 0; // 将第一格设置为0
            }
        }
    }
    flag = 1;
}

int checkGrid() {
    for (int i = 0; i < MAX_GRID; i++)
    {
        for (int j = 0; j < MAX_GRID; j++)
        {
            if (gamemap[i][j] == 2048)
            {
                return 1; // 胜利
            }
        }
    }
    for (int i = 0; i < MAX_GRID; i++)
    {
        for (int j = 0; j < MAX_GRID; j++)
        {
            if (gamemap[i][j] == 0)
            {
                return 0; // 游戏继续
            }
        }
    }

    for (int row = 0; row < MAX_GRID; row++) {
        for (int col = 0; col < MAX_GRID; col++) {
            int currentValue = gamemap[row][col];
            int isDifferent = 1;

            if (row > 0 && gamemap[row - 1][col] == currentValue) {
                isDifferent = 0;
            }
            if (row < MAX_GRID - 1 && gamemap[row + 1][col] == currentValue) {
                isDifferent = 0;
            }
            if (col > 0 && gamemap[row][col - 1] == currentValue) {
                isDifferent = 0;
            }
            if (col < MAX_GRID - 1 && gamemap[row][col + 1] == currentValue) {
                isDifferent = 0;
            }

            if (isDifferent) {
                return -1; // 游戏结束
            }
        }
    }

    return 0; //正常
}

void GameJudge()
{
    int check = checkGrid();
    if (check == -1)
    {
        printf("lose");
        GameEnd = 1;
    }
    if (check == 1)
    {
        printf("win");
        GameEnd = 1;
    }
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
        printf("up\n");
        MoveUp();
        break;
    case's':
    case'S':
    case 80:
        printf("down\n");
        MoveDown();
        break;
    case 'a':
    case'A':
    case 75:
        printf("left\n");
        MoveLeft();
        break;
    case'd':
    case'D':
    case 77:
        printf("right\n");
        MoveRight();
        break;
    }
}

