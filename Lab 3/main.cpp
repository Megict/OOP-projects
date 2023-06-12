#pragma warning(disable : 4996)
#include <iostream>
#include "figure.h"
#include "coords.h"

double trans(std::string &inp)
{
    double res = 0;
    int mode;
    int point = 0; 
    int minus = 0;
    int counter = 0;
    for (int i = inp.size() - 1; i >= 0; --i)
    {
        if (inp[i] >= '0' && inp[i] <= '9')
        {
            mode = 1;
        }
        else
        if (inp[i] == '.' && point == 0)
        {
            point = 1;
            mode = 2;
        }
        else 
        if (inp[i] == '-' && minus == 0)
        { 
            minus = 1;
            mode = 3; 
        }
        else
        {
            inp = "####";
            return 0;
        }

        if (mode == 2)
        {
            res /= pow(10, counter);
            counter = -1;
        }
        else 
        if (mode == 1)
        {
            res += (inp[i]-48) * pow(10, counter);
        }
        else
        if (mode == 3 && i == 0)
        {
            res *= -1;
        }
        else
        {
            inp = "####";
            return 0;
        }

        counter++;
    }

    return res;
}

int main()
{
    std::vector <figure*> main_vec;
    std::vector <double> iv;
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
            if (inp == "rectangle")
            {
                my::dec_coords mas[3];
                for (int i = 0; i < 3; ++i)
                {
                    std::string p1, p2;
                    if (mode == 0) std::cout << " |add|rect|coord_pair|=> ";
                    std::cin >> p1 >> p2;
                    double k1 = trans(p1), k2 = trans(p2);
                    if (p1 != "####" && p2 != "####")
                    {
                        mas[i] = my::dec_coords(k1, k2);
                    }
                    else
                    {
                        std::cout << "rectangle: incorrect input\n";
                        break;
                    }
                }

                if (rectangle(mas).corr == true)
                {
                    main_vec.push_back(new rectangle(mas));
                }
                else
                {
                    std::cout << "rectangle: incorrect input\n";
                }
            }
            else
            if (inp == "rhomb")
            {
                my::dec_coords mas[3];
                for (int i = 0; i < 3; ++i)
                {
                    std::string p1, p2;
                    if (mode == 0) std::cout << " |add|rhmb|coord_pair|=> ";
                    std::cin >> p1 >> p2;
                    double k1 = trans(p1), k2 = trans(p2);
                    if (p1 != "####" && p2 != "####")
                    {
                        mas[i] = my::dec_coords(k1, k2);
                    }
                    else
                    {
                        std::cout << "rhomb: incorrect input\n";
                        break;
                    }
                }
                if (rhomb(mas).corr == true)
                {
                    main_vec.push_back(new rhomb(mas));
                }
                else
                {
                    std::cout << "rhomb: incorrect input\n";
                }
            }
            else
            if (inp == "trapeze")
            {
                my::dec_coords mas[4];
                for (int i = 0; i < 4; ++i)
                {                       
                    std::string p1, p2;
                    if (mode == 0) std::cout << " |add|trpz|coord_pair|=> ";
                    std::cin >> p1 >> p2;
                    double k1 = trans(p1), k2 = trans(p2);
                    if (p1 != "####" && p2 != "####")
                    {
                        mas[i] = my::dec_coords(k1, k2);
                    }
                    else
                    {
                        std::cout << "trapeze: incorrect input\n";
                        break;
                    }
                }
                if (trapeze(mas).corr == true)
                {
                    main_vec.push_back(new trapeze(mas));
                }
                else
                {
                    std::cout << "trapeze: incorrect input\n";
                }
            }
            else
            {
                printf("figure: incorrect input\n");
            }
        }
        else
        if (inp == "print")
        {
            for (size_t i = 0; i < main_vec.size(); ++i)
            {
                std::cout << "print: |i: " << i << "| figure type: " << main_vec[i]->type() << "| surface: " << main_vec[i]->calculate_surface() << "\t| centre: " << main_vec[i]->calculate_centre() << "\n";
            }
        }
        else
        if (inp == "sumsq")
        {
            double sumsq = 0;
            for (size_t i = 0; i < main_vec.size(); ++i)
            {
                sumsq += main_vec[i]->calculate_surface();
            }
            std::cout << "summary squere: " << sumsq << "\n";
        }
        else
        if (inp == "printpoints")
        {
            for (size_t i = 0; i < main_vec.size(); ++i)
            {
                std::cout << "print points: |i: " << i << "| figure type: " << main_vec[i]->type() << " |points: ";
                for (size_t j = 0; j < main_vec[i]->allpoints.size(); ++j)
                {
                    std::cout << main_vec[i]->allpoints[j] << " | ";
                }
                std::cout << std::endl;
            }
        }
        else 
        if (inp == "remove")
        {
            if (mode == 0) std::cout << " |remaove|index|=> ";
            int x; 
            std::cin >> x;
            if (x >= 0 && x < main_vec.size())
            {
                for (int i = x; i < main_vec.size()-1; ++i)
                {
                    main_vec[i] = main_vec[i + 1];
                }
                main_vec.resize(main_vec.size()-1);
            }
            else
            {
                std::cout << "index: incorrect input\n";
            }
        }
        else
        {
            std::cout << "cmd: incorrect input\n";
        }

        if (mode == 0) std::cout << " |cmd|=> ";
    }


    return 0;
}
