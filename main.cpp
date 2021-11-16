// ���ƣ���ɶ(What to eat?)
// ��Ȩ������ѧϰ
// ���ߣ�Sean (eppesh@163.com)
// ������VS2019;EasyX 2021
// ʱ�䣺2021/10/21
// ˵���������ɶ

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

const int kKeyR = 82;       // ��ĸR��

// ��Ʒ
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
void ShowResult(Meal meal); // ��ʾ���

int main()
{
    std::vector<Food> vec_breakfast;
    std::vector<Food> vec_lunch;
    std::vector<Food> vec_supper;

    // ���ļ��������ڴ�
    std::ifstream in_file_breakfast;
    in_file_breakfast.open("./data/breakfast.txt", std::ios::in);
    if (!in_file_breakfast.is_open())
    {
        std::cout << "���ļ�breakfast.txtʧ�ܣ�" << std::endl;
        closegraph();
        return -1;
    }

    std::ifstream in_file_lunch;
    in_file_lunch.open("./data/lunch.txt", std::ios::in);
    if (!in_file_lunch.is_open())
    {
        std::cout << "���ļ�lunch.txtʧ�ܣ�" << std::endl;
        closegraph();
        return -1;
    }

    std::ifstream in_file_supper;
    in_file_supper.open("./data/supper.txt", std::ios::in);
    if (!in_file_supper.is_open())
    {
        std::cout << "���ļ�breakfast.txtʧ�ܣ�" << std::endl;
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
    ExMessage mouse_msg;		// ������Ϣ����

    while (true)
    {
        // ��ȡһ�����򰴼���Ϣ
        mouse_msg = getmessage(EM_MOUSE | EM_KEY);

        switch (mouse_msg.message)
        {
        case WM_LBUTTONDOWN: // ����������        
        {
            if (mouse_msg.x >= 50 && mouse_msg.x <= 250 && mouse_msg.y >= 100 && mouse_msg.y <= 300)
            {
                ShowResult(meal);
            }
            break;
        }
        case WM_KEYDOWN: 
        {
            // ����R����ʾˢ��
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

// ����UI
void DrawUI()
{
    initgraph(800, 600, EW_SHOWCONSOLE);
    setbkcolor(RGB(35, 170, 240));
    cleardevice(); // ��Ҫ����һ�䣬����ı���ɫ������Ч

    settextcolor(RGB(50, 50, 50));

    // ���Ҳ����������
    settextstyle(40, 0, "����");
    outtextxy(620, 110, "��");
    outtextxy(620, 160, "��");
    outtextxy(620, 210, "��");

    // �������ֵ���ʾ��ʽ��������ͬʱҲ�䵱ˢ�°�ť    
    settextstyle(80, 40, "����");
    outtextxy(40, 100, "�����");
}

void ShowResult(Meal meal)
{
    std::string result_breakfast = WhatToEat(meal.breakfast);
    std::string result_lunch = WhatToEat(meal.lunch);
    std::string result_supper = WhatToEat(meal.supper);

    settextstyle(40, 0, "����");

    // �����ԭ��������
    setfillcolor(RGB(35, 170, 240));
    setlinecolor(RGB(0, 0, 0));
    fillrectangle(300, 100, 600, 260);

    // ����ʾ���
    outtextxy(310, 110, result_breakfast.c_str());
    outtextxy(310, 160, result_lunch.c_str());
    outtextxy(310, 210, result_supper.c_str());
}

// ��ɶ���ĺ���
std::string WhatToEat(std::vector<Food> &food)
{
    srand((unsigned int)time(nullptr));
    int size = food.size();
    unsigned int index = rand() % size;
    //std::cout << "����� " << food[index].food_name << std::endl;
    return food[index].food_name;
}

