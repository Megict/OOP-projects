#pragma warning(disable : 4996)
#define utype double
#include <iostream>
#include "figure.h"
#include "square.h"
#include "print.h"
#include <tuple>
#include <utility>

int main()
{
    //входные данные
    
    rectangle<utype> a;

    a.a = std::pair<utype, utype> (0.5, 0.5);
    a.b = std::pair<utype, utype> (0.5, 1.5);
    a.c = std::pair<utype, utype> (1.5, 0.5);
    a.d = std::pair<utype, utype> (1.5, 1.5);

    rectangle<utype> r;

    r.a = std::pair<utype, utype>(0,0);
    r.b = std::pair<utype, utype>(0,0);
    r.c = std::pair<utype, utype>(0,0);
    r.d = std::pair<utype, utype>(0,0);

    trapeze<utype> b;

    b.a = std::pair<utype, utype>(2, 2);
    b.b = std::pair<utype, utype>(2, 5);
    b.c = std::pair<utype, utype>(-3, 5);
    b.d = std::pair<utype, utype>(-5, 2);

    rhomb<utype> c;

    c.a = std::pair<utype, utype>(-1, 2);
    c.b = std::pair<utype, utype>(4, 5);
    c.c = std::pair<utype, utype>(8, 5);
    c.d = std::pair<utype, utype>(6, 8);

    rhomb<utype> d;

    d.a = std::pair<utype, utype>(6, 2);
    d.b = std::pair<utype, utype>(4, 5);
    d.c = std::pair<utype, utype>(8, 5);
    d.d = std::pair<utype, utype>(6, 8);

    auto main_tpl = std::make_tuple (a);

    //конец входных данных

    tuple_print::start(main_tpl);
    std::cout << "sumsq is: " << tuple_sumsq::start(main_tpl) << std::endl;
    return 0;
}
