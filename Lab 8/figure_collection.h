//Вариант #03. Гаврилов М.С.
//класс документа

#pragma once
#include <iostream>
#include <string>
#include "factory.h"
#include "figures.h"
#include "calculator.h"
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>
#include <ctime>
#include <fstream>

class FigureCollection {
public:

    FigureCollection() {
        past_cond_stack.push(main_vector);
    }

    ~FigureCollection() {
        main_vector.clear();
    }

    void add(std::vector<std::pair<double,double>> inp,std::string type) {
        try {
            if (type == "rect") {
                main_vector.push_back(mainFactory.ProduceRectangle(inp));
            }
            else
            if (type == "rhmb") {
                main_vector.push_back(mainFactory.ProduceRhomb(inp));
            }
            else
            if (type == "trap") {
                main_vector.push_back(mainFactory.ProduceTrapeze(inp));
            }
            else {
                throw - 3;
            }
        }
        catch (int err) {
            throw err;
        }
    }
    
    void remove(int index) {

        if (main_vector.size() == 0) {
            throw - 1;
        }

        if (index > main_vector.size() || index < 0) {
            throw - 1;
        }
        auto it = main_vector.begin();
        for (int i = 0; i < index; ++i) {
            it++;
        }
        main_vector.erase(it);
    }

    void print() {
        std::cout.precision(3);
        auto print = [](MyFigures::figure<double>* p) {
            std::cout << p->GetType() << "| ";
            for (std::pair<double, double> elem : p->GetPoints()) {
                std::cout << elem.first << " " << elem.second << "|";
            }
            if (p->GetType() == "rectangle") {
                if(calculator<double>::calculate_rectangle(p) != -1)
                std::cout << " square: " << calculator<double>::calculate_rectangle(p);
            }
            if (p->GetType() == "rhomb") {
                if (calculator<double>::calculate_rhomb(p) != -1)
                std::cout << " square: " << calculator<double>::calculate_rhomb(p);
            }
            if (p->GetType() == "trapeze") {
                if (calculator<double>::calculate_trapeze(p) != -1)
                std::cout << " square: " << calculator<double>::calculate_trapeze(p);
            }
            std::cout << "\n";
        };

        std::cout << "-------------------------------------\n";
        std::for_each(main_vector.begin(), main_vector.end(), print);
        std::cout << "-------------------------------------\n";
    }

    void SaveToDisk(std::string filename) {
        std::ofstream fout;
        fout.open(filename, std::ios::binary | std::ios::out);
        if (!fout.is_open()) {
            throw - 7;
        }
        for (MyFigures::figure<double>* elem : main_vector) {
            fout.write(&elem->GetType()[1], 1);
            for (std::pair<double, double> pr : elem->GetPoints()) {
                fout.write((char*)&pr.first, sizeof(double));
                fout.write((char*)&pr.second, sizeof(double));
            }
        }
        fout.write("/", 5);
    }

    void LoadFromDisk(std::string filename) {
        std::ifstream fin;
        fin.open(filename, std::ios::binary | std::ios::in);
        if (!fin.is_open()) {
            throw - 7;
        }
        char inp = 0;
        main_vector.clear();
        while (true) {
            try {
                fin.read(&inp, 1);
            }
            catch (std::exception ex) {
                throw - 6;
            }

            if (inp == '/') {
                break;
            }

            std::vector<std::pair<double, double>> pointVec;
            std::pair<double, double> elem;
            for (int i = 0; i < 4; ++i) {
                fin.read((char*)&elem.first, sizeof(double));
                fin.read((char*)&elem.second, sizeof(double));
                pointVec.push_back(elem);
            }
            if (inp == 'e') {
                main_vector.push_back(new MyFigures::rectangle<double>(pointVec));
            }
            else
            if (inp == 'h') {
                main_vector.push_back(new MyFigures::rhomb<double>(pointVec));
            }
            else
            if (inp == 'r') {
                main_vector.push_back(new MyFigures::trapeze<double>(pointVec));
            }
            else {
                continue;
            }
        }
    }

    void undo() {
        if (past_cond_stack.size() > 1) {
            past_cond_stack.pop();
            main_vector = past_cond_stack.top();
        }
    }

    void actualize() {
        if (!(past_cond_stack.top() == main_vector)) {
            past_cond_stack.push(main_vector);
        }
    }

    std::vector <MyFigures::figure<double>*> getElements() {
        return main_vector;
    }

    int size() {
        return main_vector.size();
    }

    void clear() {
        main_vector.clear();
    }

private:
    std::vector <MyFigures::figure<double>*> main_vector;
    std::stack <std::vector <MyFigures::figure<double>*>> past_cond_stack;
    Factory mainFactory;
};