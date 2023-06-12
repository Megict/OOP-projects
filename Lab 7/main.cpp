//Вариант #03. Гаврилов М.С. 

//Спроектировать простейший «графический» векторный редактор.
//Требование к функционалу редактора :
//•	создание нового документа
//•	импорт документа из файла
//•	экспорт документа в файл
//•	создание графического примитива(согласно варианту задания)
//•	удаление графического примитива
//•	отображение документа на экране(печать перечня графических объектов и их характеристик в std::cout)
//•	реализовать операцию undo, отменяющую последнее сделанное действие.Должно действовать для операций добавления / удаления фигур.
//
//Требования к реализации :
//•	Создание графических примитивов необходимо вынести в отдельный класс – Factory.
//•	Сделать упор на использовании полиморфизма при работе с фигурами;
//•	Взаимодействие с пользователем(ввод команд) реализовать в функции main;


#include <iostream>
#include <string>
#include "factory.h"
#include "figures.h"
#include "calculator.h"
#include "figure_collection.h"
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>
#include <ctime>
#include <fstream>
#define type double



int main()
{
    FigureCollection mainCollection;
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
                std::vector<std::pair<double, double>> points;
                std::pair<double, double> p;
                if (mode == 0) std::cout << " |add|rectangle|3 points|=> ";
                for (int i = 0; i < 3; ++i) {
                    std::cin >> p.first >> p.second;
                    points.push_back(p);
                }

                try {
                    mainCollection.add(points,"rect");
                } 
                catch (int errtype) {
                    if (errtype == -1) {
                        std::cout << "ERROR: wroung count of points\n";
                    }
                    else
                    if (errtype == -2) {
                        std::cout << "ERROR: unable to construct a rectangle from this points\n";
                    }
                    else {
                        std::cout << "ERROR: unknown error";
                    }
                }
                                
            }
            else
            if (inp == "rhomb")
            {
                std::vector<std::pair<double, double>> points;
                std::pair<double, double> p;
                if (mode == 0) std::cout << " |add|rhomb|3 points|=> ";
                for (int i = 0; i < 3; ++i) {
                    std::cin >> p.first >> p.second;
                    points.push_back(p);
                }

                try {
                    mainCollection.add(points,"rhmb");
                }
                catch (int errtype) {
                    if (errtype == -1) {
                        std::cout << "ERROR: wroung count of points\n";
                    }
                    else
                    if (errtype == -2) {
                        std::cout << "ERROR: unable to construct a rhomb from this points\n";
                    }
                    else {
                        std::cout << "ERROR: unknown error";
                    }
                }

            }
            else
            if (inp == "trapeze")
            {
                std::vector<std::pair<double, double>> points;
                std::pair<double, double> p;
                if (mode == 0) std::cout << " |add|trapeze|3 points|=> ";
                for (int i = 0; i < 4; ++i) {
                    std::cin >> p.first >> p.second;
                    points.push_back(p);
                }

                try {
                    mainCollection.add(points,"trap");
                }
                catch (int errtype) {
                    if (errtype == -1) {
                        std::cout << "ERROR: wroung count of points\n";
                    }
                    else
                    if (errtype == -2) {
                        std::cout << "ERROR: unable to construct a trapeze from this points\n";
                    }
                    else {
                        std::cout << "ERROR: unknown error";
                    }
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
            mainCollection.print();
        }
        else
        if (inp == "remove")
        {
            if (mode == 0) std::cout << " |remove|index|=> ";
            int ind = -1;
            std::cin >> ind;
            try {
                mainCollection.remove(ind);
            }
            catch (int errtype) {
                if (errtype == -1) {
                    std::cout << "Error: wrong index\n";
                }
                else {
                    std::cout << "Error: unknown error\n";
                }
            }
        }
        else
        if (inp == "save") 
        {
            if (mode == 0) std::cout << " |save|filename|=> ";
            std::string filename; 
            std::cin >> filename;

            try {
                mainCollection.SaveToDisk(filename);
            }
            catch (int errtype) {
                if (errtype == -7) {
                    std::cout << "Error: unable to open file\n";
                }
                else {
                    std::cout << "Error: unknown error\n";
                }
            }
        }
        else 
        if (inp == "load") 
        {
            if (mode == 0) std::cout << " |load|filename|=> ";
            std::string filename;
            std::cin >> filename;
            try {
                mainCollection.LoadFromDisk(filename);
            }
            catch (int errtype) {
                if (errtype == -7) {
                    std::cout << "Error: unable to open file\n";
                }
                else
                if (errtype == -6) {
                    std::cout << "Error: unable to read file\n";
                }
                else {
                    std::cout << "Error: unknown error\n";
                }
            }
        }
        else
        if (inp == "undo")
        {
            mainCollection.undo();
        }
        else
        if (inp == "quit" || inp == "q")
        {
            return 0;
        }
        else
        {
            std::cout << "cmd: incorrect input\n";
        }

        mainCollection.actualize();

        if (mode == 0) std::cout << " |cmd|=> ";
    }

    return 0;
}