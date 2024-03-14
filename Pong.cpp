#include <iostream>
#include <windows.h>    //在windows环境下刷新屏幕相关
#include <ctime>
#include <cstdlib>

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
    auto WIDTH{120}, HEIGHT{40};                                                            //窗口大小
    auto ball_x{WIDTH / 2}, ball_y{HEIGHT / 2}, ball_vec_x{0}, ball_vec_y{0};               // 球的位置和速度
    auto paddle_w{4}, paddle_h{10};                                                         //挡板的长宽
    auto paddle1_x{1}, paddle1_y{HEIGHT / 2 - paddle_h / 2}, paddle_vec{3};                 //挡板1的位置和速度
    auto paddle2_x{WIDTH - paddle_w}, paddle2_y{HEIGHT / 2 - paddle_h / 2}, paddle2_vec{3}; //挡板2的位置和速度
    auto score1{0}, score2{0};                                                              //分数

    // 随机数生成器
    srand((unsigned)time(0));
    ball_vec_x = rand() % 3 + 1;    
    ball_vec_y = rand() % 3 + 1;    //生成随机数
    if (rand() % 2 == 1)
        ball_vec_x = -ball_vec_x;
    if (rand() % 2 == 1)
        ball_vec_y = -ball_vec_y;

    // 主循环
    while (1)   
    {
        // 1.处理事件

        //1.5 更新数据
        ball_x += ball_vec_x;
        ball_y += ball_vec_y;

        gotoxy(0, 0);   //定位到0，0（相当于清屏）
        hideCursor();   //隐藏光标

        // 2.绘制场景(这部分相当于是渲染引擎)
            // 2.1背景
                // 2.1.1顶部墙
                for (auto x = 0; x <= WIDTH; x++)
                    std::cout << '=';
                std::cout << '\n';

                // 2.1.2 3条竖线
                for (auto y = 0; y <= HEIGHT; y++)
                {
                    for (auto x = 0; x <= WIDTH; x++)
                    {
                        if (x == ball_x && y == ball_y)
                            std::cout << 'O';
                        else if (y >= paddle1_y && y < paddle1_y + paddle_h 
                              && x >= paddle1_x && x < paddle1_x + paddle_w)
                            std::cout << 'Z';
                        else if (y >= paddle2_y && y < paddle2_y + paddle_h
                              && x >= paddle2_x && x < paddle2_x + paddle_w)
                            std::cout << 'Z';
                        else if (x == 0 || x == WIDTH / 2 || x == WIDTH)
                            std::cout << '|';
                        else
                            std::cout << ' ';
                    }
                    std::cout << '\n';
                }

                // 2.1.3底部墙
                for (auto x = 0; x <= WIDTH; x++)
                    std::cout << '=';
                std::cout << '\n';
    }

    // cin >> WIDTH;    //仅用于调试时让窗口不自动关闭
    
    return 0;
}