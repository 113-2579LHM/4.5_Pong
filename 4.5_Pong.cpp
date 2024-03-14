#include <iostream>
using namespace std;
int main()
{
    // 1.初始化游戏数据
    auto WIDTH{120}, HEIGHT{40};    //窗口大小
    auto ball_x{WIDTH / 2}, ball_y{HEIGHT / 2}, ball_vec_x{0}, ball_vec_y{0};   //球的位置和速度
    auto paddle_w{4}, paddle_h{10}; //挡板的长宽
    auto paddle1_x{0}, paddle1_y{HEIGHT / 2 - paddle_h / 2}, paddle_vec{3}; //挡板1的位置和速度
    auto paddle2_x{WIDTH - paddle_w}, paddle2_y{HEIGHT / 2 - paddle_h / 2}, paddle2_vec{3}; //挡板2的位置和速度
    auto score1{0}, score2{0};  //分数

    // 2.绘制场景(这部分相当于是渲染引擎)
        // 2.1背景
            // 2.1.1顶部墙
            for (auto x = 0; x < WIDTH; x++)
                cout << '=';
            cout << '\n';
            // 2.1.2 3条竖线
            for (auto y = 0; y < HEIGHT; y++)
            {
                for (auto x = 0; x < WIDTH; x++)
                {
                    if (x == ball_x && y == ball_y)
                    {
                        cout << 'O';
                    }
                    else if (y >= paddle1_y && y < paddle1_y + paddle_h && x >= paddle1_x && x < paddle1_x + paddle_w)
                    {
                        cout << 'Z';
                    }
                    else if (y >= paddle2_y && y < paddle2_y + paddle_h && x >= paddle2_x && x < paddle2_x + paddle_w)
                    {
                        cout << 'Z';
                    }
                    else if (x == 0 || x == WIDTH / 2 || x == WIDTH)
                    {
                        cout << '|';
                    }
                    else
                    {
                        cout << ' ';
                    }
                }
                cout << '\n';
            }
            // 底部墙
            for (auto x = 0; x < WIDTH; x++)
            {
                cout << '=';
            }

            return 0;
}