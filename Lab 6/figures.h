#pragma once
#pragma once
#include <iostream>
#include <tuple>
#include <utility>
#include <cmath>
#define PI 3.14159265358979323846
//*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*--*-**-*-*-*-*-*-*-*--*-*-*--*-*-*
template <typename axtype>
axtype calculate_length(std::pair<axtype, axtype> a, std::pair<axtype, axtype> b) 
{
    return sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2));
}

template <typename axtype>
bool are_parallel(std::pair<axtype, axtype> L1_a, std::pair<axtype, axtype> L1_b, std::pair<axtype, axtype> L2_a, std::pair<axtype, axtype> L2_b)
{
    L1_b = L1_b - L1_a;
    L2_b = L2_b - L2_a;
    if ((L1_b.second == 0 && L2_b.second == 0) || (L1_b.first == 0 && L2_b.first == 0) || (L1_b.first / L1_b.second == L2_b.first / L2_b.second))
    {
        return true;
    }
    return false;
}

template <typename axtype>
bool are_perpendecualr(std::pair<axtype, axtype> L1_a, std::pair<axtype, axtype> L1_b, std::pair<axtype, axtype> L2_a, std::pair<axtype, axtype> L2_b)
{
    L1_b = L1_b - L1_a;
    L2_b = L2_b - L2_a;
    if (L1_b.first * L2_b.first + L1_b.second * L2_b.second == 0.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename axtype>
std::pair<axtype, axtype> sixty_deg_turn(std::pair<axtype, axtype> centre, std::pair<axtype, axtype> point)
{
    std::pair<axtype, axtype> fcv(point.first - centre.first, point.second - centre.second);
    std::pair<axtype, axtype> res(fcv.first * cos(PI / 3) - fcv.second * sin(PI / 3), fcv.first * sin(PI / 3) + fcv.second * cos(PI / 3));
    return std::pair<axtype, axtype>(res.first + centre.first, res.second + centre.second);
}

template <typename axtype>
std::pair<axtype, axtype> centre(std::pair<axtype, axtype> a, std::pair<axtype, axtype> b)
{
    return std::pair<axtype, axtype>((a.first + b.first) / 2.0, (a.second + b.second) / 2.0);
}

template<typename T>
std::pair<T, T> operator- (std::pair<T, T> lhs, std::pair<T, T> rhs)
{
    return std::pair<T, T>(lhs.first - rhs.first, lhs.second - rhs.second);
}

template<typename T>
std::pair<T, T> operator+ (std::pair<T, T> lhs, std::pair<T, T> rhs)
{
    return std::pair<T, T>(lhs.first + rhs.first, lhs.second + rhs.second);
}

template<typename T>
std::pair<T, T> operator* (std::pair<T, T> lhs, std::pair<T, T> rhs)
{
    return std::pair<T, T>(lhs.first * rhs.first, lhs.second * rhs.second);
}

template<typename T>
std::pair<T, T> operator/ (std::pair<T, T> lhs, std::pair<T, T> rhs)
{
    return std::pair<T, T>(lhs.first / rhs.first, lhs.second / rhs.second);
}

//*------*-*-*-*--*-*--**--**--*-*-*--**--**--*-**-*-*-*--*-*-*-**-*---*-*-*-*-*-*---*---*-**-*-*-*-*-*--*-**--*-*----*-*-*-**--*-*-*-*-*-**--*-**--*-*-*-**-*--*-**-*-*-*-

template <typename axtype>
struct rectangle {
    std::string type = "rect";
    std::pair<axtype, axtype> a, b, c, d;
};

template <typename axtype>
struct rhomb {
    std::string type = "rhmb";
    std::pair<axtype, axtype> a, b, c, d;
};

template <typename axtype>
struct trapeze {
    std::string type = "trap";
    std::pair<axtype, axtype> a, b, c, d;
};

template <typename axtype>
struct hexagon {
    //std::string type = "hex";
    std::pair<axtype, axtype> centre, point;
    std::pair<axtype, axtype> b, c, d, e, f;
};

template <typename axtype>
class calculator
{
public:
    template<typename T>
    static axtype calculate_hexagon(T inp)
    {
        axtype radius = (calculate_length(inp.centre, inp.point));
        axtype square = (radius / 2) * radius * 3 * sqrt(3);
        return square;
    }

    template<typename T>
    static axtype calculate_rectangle(T inp) //Ð¿Ð¾Ð´ÑÑ‡ÐµÑ‚ Ð¿Ð»Ð¾Ñ‰Ð°Ð´Ð¸ Ð¿Ñ€ÑÐ¼Ð¾ÑƒÐ³Ð¾Ð»ÑŒÐ½Ð¸ÐºÐ°. ÐœÐ¾Ð´Ð¸Ñ„Ð¸ÐºÐ°Ñ†Ð¸Ñ Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ Ð¸Ð· Ð›Ð 3
    {
        axtype length = 0;
        axtype heigth = 0;

        if (are_perpendecualr<axtype>(inp.a, inp.b, inp.b, inp.c) && calculate_length(inp.a, inp.c) == calculate_length(inp.b, inp.d))//Ð¿Ñ€Ð¾Ð²ÐµÑ€ÐºÐ°, Ñ‡Ñ‚Ð¾ Ð·Ð° ÐºÐ¾Ð¾Ñ€Ð´Ð¸Ð½Ð°Ñ‚Ñ‹ Ð¼Ñ‹ Ð¿Ð¾Ð»ÑƒÑ‡Ð¸Ð»Ð¸. Ð’Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾, ÑÑ‚Ð¾ Ð½Ðµ Ð¿Ñ€ÑÐ¼Ð¾ÑƒÐ³Ð¾Ð»ÑŒÐ½Ð¸Ðº
        {                                                                                                                           //Ð²ÑÑ ÑÑ‚Ð° ÐºÑƒÑ‡Ð° ÑƒÑÐ»Ð¾Ð²Ð¸Ð¹ Ð½ÑƒÐ¶Ð½Ð°, Ñ‡Ñ‚Ð¾Ð±Ñ‹ Ð¿Ñ€Ð°Ð²Ð¸Ð»ÑŒÐ½Ð¾ Ð¿Ð¾Ð½ÑÑ‚ÑŒ, ÐºÐ°Ðº ÑÑ‚Ð¾Ñ‚ Ð¿Ñ€ÑÐ¼Ð¾ÑƒÐ³Ð¾Ð»ÑŒÐ½Ð¸Ðº ÑÐ¾Ñ€Ð¸ÐµÐ½Ñ‚Ð¸Ñ€Ð¾Ð²Ð°Ð½
            length = calculate_length<axtype>(inp.b, inp.a);
            heigth = calculate_length<axtype>(inp.b, inp.c);
        }
        else
            if (are_perpendecualr<axtype>(inp.a, inp.b, inp.a, inp.c) && calculate_length(inp.b, inp.c) == calculate_length(inp.a, inp.d))
            {
                length = calculate_length<axtype>(inp.c, inp.a);
                heigth = calculate_length<axtype>(inp.b, inp.a);
            }
            else
                if (are_perpendecualr<axtype>(inp.a, inp.c, inp.b, inp.c) && calculate_length(inp.a, inp.b) == calculate_length(inp.c, inp.d))
                {
                    length = calculate_length<axtype>(inp.c, inp.a);
                    heigth = calculate_length<axtype>(inp.c, inp.b);
                }
                else
                {
                    //ÑÑ‚Ð¾ Ð½Ðµ Ð¿Ñ€ÑÐ¼Ð¾ÑƒÐ³Ð¾Ð»ÑŒÐ½Ð¸Ðº
                    return -1;
                }

        return length * heigth;//Ð¿Ð¾Ð´ÑÑ‡ÐµÑ‚ Ð¿Ð»Ð¾Ñ‰Ð°Ð´Ð¸
    }

    template<typename T>
    static axtype calculate_rhomb(T inp)
    {
        axtype l1 = calculate_length(inp.a, inp.b);
        axtype l2 = calculate_length(inp.a, inp.c);
        axtype l3 = calculate_length(inp.b, inp.c);

        if (calculate_length(inp.a, inp.b) == calculate_length(inp.a, inp.c) && calculate_length(inp.b, inp.d) == calculate_length(inp.c, inp.d) && calculate_length(inp.a, inp.c) == calculate_length(inp.b, inp.d))
        {
            axtype surface = calculate_length(inp.a, inp.d) * calculate_length(inp.b, inp.c) / 2;
            return abs(surface);
        }
        else
        if (calculate_length(inp.a, inp.b) == calculate_length(inp.a, inp.d) && calculate_length(inp.b, inp.c) == calculate_length(inp.d, inp.c) && calculate_length(inp.a, inp.b) == calculate_length(inp.b, inp.c))
        {
            axtype surface = calculate_length(inp.a, inp.c) * calculate_length(inp.b, inp.d) / 2;
            return abs(surface);
        }
        else
        if (calculate_length(inp.a, inp.c) == calculate_length(inp.a, inp.d) && calculate_length(inp.c, inp.b) == calculate_length(inp.d, inp.c) && calculate_length(inp.a, inp.c) == calculate_length(inp.c, inp.b))
        {
            axtype surface = calculate_length(inp.a, inp.b) * calculate_length(inp.c, inp.d) / 2;
            return abs(surface);
        }
        else
        {
            return -1;
        }
    }

    template<typename T>
    static axtype calculate_trapeze(T inp)
    {
        std::pair<axtype, axtype> l1_a;
        std::pair<axtype, axtype> l1_b;
        std::pair<axtype, axtype> l2_a;
        std::pair<axtype, axtype> l2_b;
        if (are_parallel(inp.a, inp.b, inp.c, inp.d))
        {
            l1_a = inp.a;
            l1_b = inp.b;
            l2_a = inp.c;
            l2_b = inp.d;
        }
        else
        if (are_parallel(inp.b, inp.c, inp.a, inp.d))
        {
            l1_a = inp.b;
            l1_b = inp.c;
            l2_a = inp.a;
            l2_b = inp.d;
        }
        else
        if (are_parallel(inp.a, inp.c, inp.b, inp.d))
        {
            l1_a = inp.a;
            l1_b = inp.c;
            l2_a = inp.b;
            l2_b = inp.d;
        }
        else
        {
            return -1;
        }

        std::pair<axtype, axtype> vec1 = l1_b - l1_a;
        std::pair<axtype, axtype> vec2 = l2_b - l2_a;


        vec1 = std::pair<axtype, axtype>(vec1.second, vec1.first);
        vec2 = std::pair<axtype, axtype>(vec2.second, vec2.first);

        axtype a1, b1, c1;
        axtype a2, b2, c2;
        a1 = l1_b.second - l1_a.second;
        a2 = l2_b.second - l2_a.second;

        b1 = -1 * (l1_b.first - l1_a.first);
        b2 = -1 * (l2_b.first - l2_a.first);

        c1 = l1_a.second * (l1_b.first - l1_a.first) - l1_a.first * (l1_b.second - l1_a.second);
        c2 = l2_a.second * (l2_b.first - l2_a.first) - l2_a.first * (l2_b.second - l2_a.second);

        axtype h = abs(a2 * l1_a.first + b2 * l1_a.second + c2) / (sqrt(pow(a2, 2) + pow(b2, 2)));

        return h * (calculate_length<axtype>(l1_a, l1_b) + calculate_length<axtype>(l2_a, l2_b)) / 2;
    }

};
