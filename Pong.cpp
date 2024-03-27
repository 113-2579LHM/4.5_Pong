#include <iostream>
#include <windows.h>    //在windows环境下刷新屏幕相关
#include <ctime>
#include <cstdlib>
#include <conio.h>

// using namespace std;

void gotoxy(short x, short y) // 用于在刷新之前清空屏幕    //gcc让我用short int形？(narrowing conversion of 'x' from 'int' to 'SHORT' {aka 'short int'} [-Wnarrowing])
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor()   //避免刷新时鼠标闪烁
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int main()  //游戏主函数
{
    // 1.初始化游戏数据
    auto WIDTH{120}, HEIGHT{40};                                                            //窗口长宽
    auto ball_x{WIDTH / 2}, ball_y{HEIGHT / 2}, ball_vec_x{0}, ball_vec_y{0};               //球的x,y坐标和x,y方向速度
    auto paddle_w{4}, paddle_h{10};                                                         //挡板长宽,(横宽竖高)
    auto paddle1_x{1}, paddle1_y{HEIGHT / 2 - paddle_h / 2}, paddle1_vec{3};                // 挡板1的x,y坐标和速度
    auto paddle2_x{WIDTH - paddle_w}, paddle2_y{HEIGHT / 2 - paddle_h / 2}, paddle2_vec{3}; // 挡板2的x,y坐标和速度
    auto score1{0}, score2{0};                                                              //分数

    // 随机数生成器
    srand((unsigned)time(0));       //生成随机数
    ball_vec_x = rand() % 3 + 1;    
    ball_vec_y = rand() % 3 + 1;    //把生成的随机数作为初始速度
    if (rand() % 2 == 1)            //随机改变初速度的方向
        ball_vec_x = -ball_vec_x;
    if (rand() % 2 == 1)            //随机改变初速度的方向
        ball_vec_y = -ball_vec_y;

    // 主循环
    while (1)   
    {
        // 1.处理事件
        char key;
        if (_kbhit())
        {
            key = _getch();
            if ((key == 'w'|| key == 'W')&& paddle1_y > 1)    //当接受到w，且挡板1不在上边缘时
            {
                paddle1_y -= paddle1_vec;                       //挡板1向上移动
            }
            else if ((key == 's' || key == 'S') && paddle1_y + paddle1_vec + paddle_h + 1 < HEIGHT) //当接收s，且挡板1不在下边缘时
            {
                paddle1_y += paddle1_vec;                   //挡板1向下移动
            }
            else if (key == 72 && paddle2_y > 1)    // 当接受到上，且挡板2不在上边缘时
            {
                paddle2_y -= paddle2_vec; // 挡板2向上移动
            }
            else if (key == 80 && paddle2_y + paddle2_vec + paddle_h + 1 < HEIGHT) // 当接收下，且挡板2不在下边缘时
            {
                paddle1_y += paddle1_vec;                 //挡板1向下移动
            }
        }

        //1.5 更新数据
        ball_x += ball_vec_x;
        ball_y += ball_vec_y;
        if (ball_y < 0|| ball_y > HEIGHT)   //到达上下边界时反弹
        {
            ball_vec_y = -ball_vec_y;
        }
        if (ball_x < paddle1_x + paddle_w && ball_y >= paddle1_y && ball_y <= paddle1_y + paddle_h)  //与挡板1（paddle1）碰撞时
        {
            ball_vec_x = -ball_vec_x;
            score1 += 1;
        }
        if (ball_x > paddle2_x && ball_y >= paddle2_y && ball_y <= paddle2_y + paddle_h) // 与挡板2（paddle2）碰撞时
        {
            ball_vec_x = -ball_vec_x;
            score2 += 1;
        }

        gotoxy(0, 0);   //定位到0，0（相当于清屏）
        hideCursor();   //隐藏光标

        // 2.绘制场景(这部分相当于是渲染引擎)
        for (auto x = 0; x <= WIDTH; x++)   //绘制顶部墙
            std::cout << '=';
        std::cout << '\n';                  // 完成一行刷新，回车

        for (auto y = 0; y <= HEIGHT; y++)  
        {
            for (auto x = 0; x <= WIDTH; x++)
            {
                if (x == ball_x && y == ball_y)
                    std::cout << 'O';                                   //绘制球
                else if (y >= paddle1_y && y < paddle1_y + paddle_h     
                        && x >= paddle1_x && x < paddle1_x + paddle_w)    //绘制挡板1       从这里看，挡板的xy坐标是其左上角坐标
                    std::cout << 'Z';
                else if (y >= paddle2_y && y < paddle2_y + paddle_h
                        && x >= paddle2_x && x < paddle2_x + paddle_w)    //绘制挡板2
                    std::cout << 'Z';
                else if (x == 0 || x == WIDTH / 2 || x == WIDTH)
                    std::cout << '|';                                   //绘制左右边线和竖线
                else                  
                    std::cout << ' ';                                   //其他地方不绘制（空格）
            }
            std::cout << '\n';                                          //完成一行刷新，回车
        }

        for (auto x = 0; x <= WIDTH; x++)
            std::cout << '=';                                           //绘制底部墙
        std::cout << '\n';                                              //完成一行刷新，回车
    }

    // cin >> WIDTH;    //仅用于调试时让窗口不自动关闭
    
    return 0;
}