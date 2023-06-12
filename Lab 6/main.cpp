//Вариант #07. Гаврилов М.С. 

#include <iostream>
#include <string>
#include "figures.h"
#include "iterator.h"
#include "allocator.h"
#include "stack.h"
#include <memory>
#include <algorithm>
#include <cmath>
#include <ctime>
#define axtype double


int main()
{

    stack<hexagon<axtype>,allocator<hexagon<axtype>,1000>> main_stack;
    std::string inp;
    std::cout << " |cmd|=> ";
    std::cin >> inp;

    int mode; //это для красивого формата ввода. если идут ввод из файла, то форматирование консоли выводиться не будет. 
    if (inp == "sheet")
    {
        mode = 1;
    }
    else
    {
        mode = 0;
        goto a;
    }

    while (std::cin >> inp)
    {
    a:

        if (inp == "add")
        {
            if (mode == 0) std::cout << " |add|figure|=> ";
            std::cin >> inp;
            if (inp == "hexagon")
            {
                axtype p1, p2;
                axtype p3, p4;
                if (mode == 0) std::cout << " |add|hex|centre|=> ";
                std::cin >> p1 >> p2;
                if (mode == 0) std::cout << " |add|hex|point|=> ";
                std::cin >> p3 >> p4;

                hexagon<axtype> adb;
                adb.centre = std::pair<axtype,axtype>(p1, p2);
                adb.point = std::pair<axtype,axtype>(p3, p4);
                
                adb.b = sixty_deg_turn(adb.centre, adb.point);
                adb.c = sixty_deg_turn(adb.centre, adb.b);
                adb.d = sixty_deg_turn(adb.centre, adb.c);
                adb.e = sixty_deg_turn(adb.centre, adb.d);
                adb.f = sixty_deg_turn(adb.centre, adb.e);
                main_stack.push(adb);
            }
            else
            {
                printf("figure: incorrect input\n");
            }
        }
        else
        if (inp == "print")
        {
            std::cout.precision(3);
            auto print = [](hexagon<axtype> p) { std::cout << std::fixed << "--| " << p.point.first << " " << p.point.second << " | " << p.b.first << " " << p.b.second << " | " << p.c.first << " " << p.c.second << " | " << p.d.first << " " << p.d.second << " | " << p.e.first << " " << p.e.second << " | " << p.f.first << " " << p.f.second << std::endl; };
            std::for_each(main_stack.begin(), main_stack.end(), print);
        }
        else
        if (inp == "count_lsq")
        {
            if(mode == 0) std::cout << " |count_lsq|then|=> ";
            axtype sqm;
            std::cin >> sqm;
            auto check = [sqm](hexagon<axtype> p) {return calculator<axtype>::calculate_hexagon(p) < sqm; };
            int counter = std::count_if(main_stack.begin(), main_stack.end(), check);
            std::cout << "--|" << counter << std::endl; 
        }
        else
        if (inp == "remove")
        {
            if (mode == 0) std::cout << " |remove|index|=> ";
            int ind;
            std::cin >> ind;
            iterator<hexagon<axtype>> it = main_stack.begin();
            for (int i = 0; i < ind; ++i)
            {
                std::cout << "++\n";
                it++;
            }
            std::cout << "erasing: " << it.get_position() << std::endl;
            if (main_stack.erase(it) != 0)
            {
                std::cout << "error: wrong position" << std::endl;
            }
            else
            {
                std::cout << "erased: " << it.get_position() << std::endl;
            }
        }
        else
        if (inp == "quit")
        {
            return 0;
        }
        else
        {
            std::cout << "cmd: incorrect input\n";
        }

        if (mode == 0) std::cout << " |cmd|=> ";
    }


    return 0;
}



