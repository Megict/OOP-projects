#pragma once

namespace tuple_sumsq
{
    class sum
    {
    public:
        sum()
        {
            s_ = 0;
        }
        double s_;
    };

    sum Ir;


    template <sum* const I, int index, class T>
    int cad(T inp)
    {
        double sq;

        //std::cout << inp.type << std::endl;

        /*calculating...*/
        if (inp.type == "rect")
        {
            sq = calculator<utype>::calculate_rectangle<T>(inp);
        }
        else
        if (inp.type == "rhmb")
        {
            sq = calculator<utype>::calculate_rhomb<T>(inp);
        }
        else
        if (inp.type == "trap")
        {
            sq = calculator<utype>::calculate_trapeze<T>(inp);
        }
        else
        {
            std::cout << "tuple_sumsq: cad: wrong figure type" << std::endl;
            return 1;
        }


        if (sq < 0)
        {
            std::cout << "tuple_sumsq: cad: wrong figure type at pos " << index << " | requested: " << inp.type << std::endl;
            return -1;
        }

        I->s_ += sq;
        return 0;
    }

    template<int index, sum* const I, typename... Args>
    struct iterate
    {
        static void forn(std::tuple<Args...> tpl)
        {
            iterate<index - 1, I, Args...>::forn(tpl);
            cad<I,index>(std::get<index>(tpl));
        }

    };

    template<sum* const I, typename... Args>
    struct iterate<0, I, Args...>
    {
        static void forn(std::tuple<Args...> tpl)
        {
            cad<I,0>(std::get<0>(tpl));
        }
    };

    template<sum* const I, typename... Args>
    struct iterate<-1, I, Args...>
    {
        static void forn(std::tuple<Args...> tpl)
        {
            std::cout << "tuple_sumsq|forn: got empty tuple" << std::endl;
        }
    };


    template<typename... Args>
    double start(std::tuple<Args...> tpl)
    {
        Ir.s_ = 0;
        sum* const I_ptr = &Ir;

        const int ind = std::tuple_size <std::tuple<Args...>>::value;
        iterate<ind - 1, I_ptr, Args...>::forn(tpl);

        return Ir.s_;
    }

}