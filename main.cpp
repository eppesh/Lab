// 名称：吃啥(What to eat?)
// 版权：仅供学习
// 作者：Sean (eppesh@163.com)
// 环境：VS2019;EasyX 2021
// 时间：2021/10/21
// 说明：今天吃啥

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <graphics.h>

const int kBreakfast = 0;
const int kLunch = 1;
const int kSupper = 2;

const int kKeyR = 82;       // 字母R键

// 菜品
struct Food
{
    std::string food_name;
    int food_kind;
};

struct Meal 
{
    std::vector<Food> breakfast;
    std::vector<Food> lunch;
    std::vector<Food> supper;
};

void DrawUI();
std::string WhatToEat(std::vector<Food> &food);
void ShowResult(Meal meal); // 显示结果

int main()
{
    std::vector<Food> vec_breakfast;
    std::vector<Food> vec_lunch;
    std::vector<Food> vec_supper;

    // 打开文件并存入内存
    std::ifstream in_file_breakfast;
    in_file_breakfast.open("./data/breakfast.txt", std::ios::in);
    if (!in_file_breakfast.is_open())
    {
        std::cout << "打开文件breakfast.txt失败！" << std::endl;
        closegraph();
        return -1;
    }

    std::ifstream in_file_lunch;
    in_file_lunch.open("./data/lunch.txt", std::ios::in);
    if (!in_file_lunch.is_open())
    {
        std::cout << "打开文件lunch.txt失败！" << std::endl;
        closegraph();
        return -1;
    }

    std::ifstream in_file_supper;
    in_file_supper.open("./data/supper.txt", std::ios::in);
    if (!in_file_supper.is_open())
    {
        std::cout << "打开文件breakfast.txt失败！" << std::endl;
        closegraph();
        return -1;
    }

    std::string content = "";
    Food breakfast;
    while (in_file_breakfast >> content)
    {
        std::cout << content << std::endl;
        breakfast.food_name = content;
        breakfast.food_kind = kBreakfast;
        vec_breakfast.push_back(breakfast);
    }

    content = "";
    Food lunch;
    while (in_file_lunch >> content)
    {
        std::cout << content << std::endl;
        lunch.food_name = content;
        lunch.food_kind = kLunch;
        vec_lunch.push_back(lunch);
    }

    content = "";
    Food supper;
    while (in_file_supper >> content)
    {
        std::cout << content << std::endl;
        supper.food_name = content;
        supper.food_kind = kSupper;
        vec_supper.push_back(supper);
    }

    in_file_breakfast.close();
    in_file_lunch.close();
    in_file_supper.close();

    Meal meal;
    meal.breakfast = vec_breakfast;
    meal.lunch = vec_lunch;
    meal.supper = vec_supper;
    //////////////////////////////////////////////////////////////////////////

    DrawUI();
    
    ShowResult(meal);

    // mouse click
    ExMessage mouse_msg;		// 定义消息变量

    while (true)
    {
        // 获取一条鼠标或按键消息
        mouse_msg = getmessage(EM_MOUSE | EM_KEY);

        switch (mouse_msg.message)
        {
        case WM_LBUTTONDOWN: // 按下鼠标左键        
        {
            if (mouse_msg.x >= 50 && mouse_msg.x <= 250 && mouse_msg.y >= 100 && mouse_msg.y <= 300)
            {
                ShowResult(meal);
            }
            break;
        }
        case WM_KEYDOWN: 
        {
            // 按下R键表示刷新
            if (mouse_msg.vkcode == kKeyR)
            {
                ShowResult(meal);
            }
            break;
        }
        default:
            break;
        }
    }
    _getch();
    closegraph();
    
    return 0;
}

// 绘制UI
void DrawUI()
{
    initgraph(800, 600, EW_SHOWCONSOLE);
    setbkcolor(RGB(35, 170, 240));
    cleardevice(); // 需要加这一句，上面的背景色才能生效

    settextcolor(RGB(50, 50, 50));

    // 最右侧的设置区域
    settextstyle(40, 0, "楷体");
    outtextxy(620, 110, "早");
    outtextxy(620, 160, "中");
    outtextxy(620, 210, "晚");

    // 设置文字的显示样式，该区域同时也充当刷新按钮    
    settextstyle(80, 40, "宋体");
    outtextxy(40, 100, "今天吃");
}

void ShowResult(Meal meal)
{
    std::string result_breakfast = WhatToEat(meal.breakfast);
    std::string result_lunch = WhatToEat(meal.lunch);
    std::string result_supper = WhatToEat(meal.supper);

    settextstyle(40, 0, "楷体");

    // 先清除原来的内容
    setfillcolor(RGB(35, 170, 240));
    setlinecolor(RGB(0, 0, 0));
    fillrectangle(300, 100, 600, 260);

    // 再显示结果
    outtextxy(310, 110, result_breakfast.c_str());
    outtextxy(310, 160, result_lunch.c_str());
    outtextxy(310, 210, result_supper.c_str());
}

// 吃啥核心函数
std::string WhatToEat(std::vector<Food> &food)
{
    srand((unsigned int)time(nullptr));
    int size = food.size();
    unsigned int index = rand() % size;
    //std::cout << "今天吃 " << food[index].food_name << std::endl;
    return food[index].food_name;
}

