//Вариант #03. Гаврилов М.С.
//класс калькулятора площадей и некоторые геометрические функции

#pragma once
#include <cmath>
#include <vector>
#define Precision 0.0001
#define PI 3.14159265358979323846


template <typename axtype>
class Are {
public:
    static bool Equal(axtype lhs, axtype rhs) {
        //std::cout << "\n(simple)-|" << lhs << " " << rhs << "|-";
        if (lhs == rhs) {
            return true;
        }
        else {
            return false;
        }
    }
};

template <> //функция сравнения с учетом погрешности
class Are<float> {
public:
    static bool Equal(float lhs, float rhs) {
        //std::cout << "\n(float)-|" << lhs << " " << rhs << "|-";
        if (lhs > rhs - Precision && lhs < rhs + Precision) {
            return true;
        }
        else {
            return false;
        }
    }
};

template <>
class Are<double> {
public:
    static bool Equal(double lhs, double rhs) {

        //std::cout << "\n(double)-|" << lhs << " " << rhs << "|-";

        if (lhs > rhs - Precision && lhs < rhs + Precision) {
            return true;
        }
        else {
            return false;
        }
    }
};

//функции для работы в двумерной декартовой системе координат с любым типом оси
template <typename axtype>
axtype calculate_length(std::pair<axtype, axtype> a, std::pair<axtype, axtype> b)
{
    return sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2));
}

template <typename axtype>
bool are_parallel(std::pair<axtype, axtype> L1_a, std::pair<axtype, axtype> L1_b, std::pair<axtype, axtype> L2_a, std::pair<axtype, axtype> L2_b)
{
    std::pair<axtype, axtype> dirVec1 = L1_b - L1_a; //считаем направляющие векторы полученных прямых
    std::pair<axtype, axtype> dirVec2 = L2_b - L2_a;
    if ((Are<axtype>::Equal(dirVec1.second, (double)0) && Are<axtype>::Equal(dirVec2.second, (double)0)) || (Are<axtype>::Equal(dirVec1.first, (double)0) && Are<axtype>::Equal(dirVec2.first, (double)0)) || Are<axtype>::Equal(dirVec1.first / dirVec1.second, dirVec2.first / dirVec2.second))
    {
        return true;
    }
    return false;
}

template <typename axtype>
bool are_perpendecualr(std::pair<axtype, axtype> L1_a, std::pair<axtype, axtype> L1_b, std::pair<axtype, axtype> L2_a, std::pair<axtype, axtype> L2_b)
{
    //std::cout << "\nchecking... " << L1_a.first << " " << L1_a.second << " -- " << L1_b.first << " " << L1_b.second << " and " << L2_a.first << " " << L2_a.second << " -- " << L2_b.first << " " << L2_b.second;
    std::pair<axtype, axtype> dirvec_1 = L1_b - L1_a;
    std::pair<axtype, axtype> dirvec_2 = L2_b - L2_a;
    if (Are<axtype>::Equal(dirvec_1.first * dirvec_2.first + dirvec_1.second * dirvec_2.second, 0.0))
    {
    //    std::cout << "\n" << L1_a.first << " " << L1_a.second << " -- " << L1_b.first << " " << L1_b.second << " and " << L2_a.first << " " << L2_a.second << " -- " << L2_b.first << " " << L2_b.second << " are perpendecular\n";
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

template <typename axtype>
struct FictFigure {
    std::pair<axtype, axtype> a;
    std::pair<axtype, axtype> b;
    std::pair<axtype, axtype> c;
    std::pair<axtype, axtype> d;
};

template <typename axtype>
class calculator
{
public:
    static axtype calculate_rectangle(MyFigures::figure<axtype>* inpFigure)
    {
        struct FictFigure<axtype> inp;
        inp.a = inpFigure->GetPoints()[0];
        inp.b = inpFigure->GetPoints()[1];
        inp.c = inpFigure->GetPoints()[2];
        inp.d = inpFigure->GetPoints()[3];

        axtype length = 0;
        axtype heigth = 0;


        if (are_perpendecualr<axtype>(inp.a, inp.b, inp.b, inp.c) && calculate_length(inp.a, inp.c) == calculate_length(inp.b, inp.d))
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

    static axtype calculate_rhomb(MyFigures::figure<axtype>* inpFigure)
    {
        struct FictFigure<axtype> inp;
        inp.a = inpFigure->GetPoints()[0];
        inp.b = inpFigure->GetPoints()[1];
        inp.c = inpFigure->GetPoints()[2];
        inp.d = inpFigure->GetPoints()[3];

        axtype l1 = calculate_length(inp.a, inp.b);
        axtype l2 = calculate_length(inp.a, inp.c);
        axtype l3 = calculate_length(inp.b, inp.c);

        if (Are<double>::Equal(calculate_length(inp.a, inp.b),calculate_length(inp.a, inp.c)) && Are<double>::Equal(calculate_length(inp.b, inp.d),calculate_length(inp.c, inp.d)) && Are<double>::Equal(calculate_length(inp.a, inp.c),calculate_length(inp.b, inp.d)))
        {
            axtype surface = calculate_length(inp.a, inp.d) * calculate_length(inp.b, inp.c) / 2;
            return abs(surface);
        }
        else
        if (Are<double>::Equal(calculate_length(inp.a, inp.b),calculate_length(inp.a, inp.d)) && Are<double>::Equal(calculate_length(inp.b, inp.c),calculate_length(inp.d, inp.c)) && Are<double>::Equal(calculate_length(inp.a, inp.b),calculate_length(inp.b, inp.c)))
        {
            axtype surface = calculate_length(inp.a, inp.c) * calculate_length(inp.b, inp.d) / 2;
            return abs(surface);
        }
        else
        if (Are<double>::Equal(calculate_length(inp.a, inp.c),calculate_length(inp.a, inp.d)) && Are<double>::Equal(calculate_length(inp.c, inp.b),calculate_length(inp.d, inp.c)) && Are<double>::Equal(calculate_length(inp.a, inp.c),calculate_length(inp.c, inp.b)))
        {
            axtype surface = calculate_length(inp.a, inp.b) * calculate_length(inp.c, inp.d) / 2;
            return abs(surface);
        }
        else
        {
            return -1;
        }
    }

    static axtype calculate_trapeze(MyFigures::figure<axtype>* inpFigure)
    {
        struct FictFigure<axtype> inp;
        inp.a = inpFigure->GetPoints()[0];
        inp.b = inpFigure->GetPoints()[1];
        inp.c = inpFigure->GetPoints()[2];
        inp.d = inpFigure->GetPoints()[3];

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
