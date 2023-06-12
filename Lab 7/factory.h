//Вариант #03. Гаврилов М.С.
//класс создания фигур
#pragma once
#include "figures.h"
#include "calculator.h"

class Factory {
public:

    ~Factory() {
        for (MyFigures::figure<double>* elem : all_production) {
            delete elem;
        }

        all_production.clear();
    }

    MyFigures::rectangle<double>* ProduceRectangle(std::vector<std::pair<double, double>> inp) {
        if (inp.size() != 3) {
            throw - 1; //неверное количество введенных точек
        }

        //на вход идут три точки по разные концы от прямоугольника
        if (are_perpendecualr<double>(inp[0], inp[1], inp[1], inp[2]) || are_perpendecualr<double>(inp[0], inp[1], inp[0], inp[2]) || are_perpendecualr<double>(inp[0], inp[2], inp[1], inp[2]))
        {
            //проверили, можно ли на основе полученных точек построить прямоугольник
            if (are_perpendecualr<double>(inp[0], inp[1], inp[1], inp[2]))
            {
                inp.push_back(inp[0] + (inp[2] - inp[1]));
            }
            else
            if (are_perpendecualr<double>(inp[0], inp[1], inp[0], inp[2]))
            {
                inp.push_back(inp[1] + (inp[2] - inp[0]));
            }
            else
            if (are_perpendecualr<double>(inp[0], inp[2], inp[1], inp[2]))
            {
                inp.push_back(inp[1] + (inp[0] - inp[2]));
            }


            MyFigures::rectangle<double>* result = new MyFigures::rectangle<double>(inp);
            all_production.push_back(result);
            return result;
        }
        else {
            throw - 2; //нельзя построить прямоугольник
        }
    }

    MyFigures::rhomb<double>* ProduceRhomb(std::vector<std::pair<double, double>> inp) {
        if (inp.size() != 3) {
            throw - 1; //неверное количество введенных точек
        }

        double l1 = calculate_length(inp[0], inp[1]);
        double l2 = calculate_length(inp[0], inp[2]);
        double l3 = calculate_length(inp[1], inp[2]);

        if (l1 == l2 || l2 == l3 || l1 == l3)
        {
            if (l1 == l2)
            {
                inp.push_back(inp[1] + (inp[2] - inp[0]));
            }
            else
            if (l1 == l3)
            {
                inp.push_back(inp[0] + (inp[2] - inp[1]));
            }
            else
            if (l2 == l3)
            {
                inp.push_back(inp[0] + (inp[1] - inp[2]));
            }


            MyFigures::rhomb<double>* result = new MyFigures::rhomb<double>(inp);
            all_production.push_back(result);
            return result; 
        }
        else
        {
            throw - 2; //нельзя построить ромб
        }
    }

    MyFigures::trapeze<double>* ProduceTrapeze(std::vector<std::pair<double, double>> inp) {
        if (inp.size() != 4) {
            throw - 1; //неверное количество введенных точек
        }

        if (are_parallel(inp[0], inp[1], inp[2], inp[3]) || are_parallel(inp[1], inp[2], inp[0], inp[3]) || are_parallel(inp[0], inp[2], inp[1], inp[3]))
        {
            MyFigures::trapeze<double>* result = new MyFigures::trapeze<double>(inp);
            all_production.push_back(result);
            return result;
        }
        else
        {
            throw - 2; //нельзя построить трапецию
        }
    }

private:
    std::vector< MyFigures::figure<double>*> all_production;
};