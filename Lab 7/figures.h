//Вариант #03. Гаврилов М.С.
//классы фигур
#pragma once
#include <vector>
#include <iostream>

namespace MyFigures
{

    template <typename axtype>
    class figure {
    public:

        figure() {
        }

        figure(std::vector< std::pair<axtype, axtype >> inp) {
            this->points = inp;
        }

        ~figure() {
            points.clear();
        }

        std::vector< std::pair<axtype, axtype >>& GetPoints() {
            return points;
        }

        bool IsInit() {
            if (points.empty()) {
                return false;
            }
            else {
                return true;
            }
        }

        virtual std::string GetType() const = 0;

    protected:
        std::vector<std::pair<axtype, axtype>> points;
    };

    template <typename axtype>
    class rectangle : public figure<axtype>
    {
    public:
        rectangle(std::vector<std::pair<axtype, axtype>> inpvec) : figure<axtype>(inpvec) { //предполагается предварительная проверка вектора 
        }

        std::string GetType() const {
            return std::string("rectangle");
        }
    };

    template <typename axtype>
    class rhomb : public figure<axtype>
    {
    public:
        rhomb(std::vector<std::pair<axtype, axtype>> inpvec) : figure<axtype>(inpvec) { //предполагается предварительная проверка вектора 
        }

        std::string GetType() const {
            return std::string("rhomb");
        }
    };

    template <typename axtype>
    class trapeze : public figure<axtype>
    {
    public:
        trapeze(std::vector<std::pair<axtype, axtype>> inpvec) : figure<axtype>(inpvec) { //предполагается предварительная проверка вектора 
        }

        std::string GetType() const {
            return std::string("trapeze");
        }
    };

    template <typename axtype>
    class hexagon : public figure<axtype>
    {
    public:
        hexagon(std::vector<std::pair<axtype, axtype>> inpvec) : figure<axtype>(inpvec) { //предполагается предварительная проверка вектора 

        };
        std::string GetType() const {
            return std::string("hexagon");
        }


    };

}
