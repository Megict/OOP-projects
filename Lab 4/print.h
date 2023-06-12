#pragma once

namespace tuple_print
{
    template <class T>
    int print_points(int index, T inp)
    {
        std::cout << "[" << index << "] <-index|type-> " << inp.type << std::endl;
        std::cout << "points: (" << inp.a.first << "," << inp.a.second << ") ";
        std::cout << "(" << inp.b.first << "," << inp.b.second << ") ";
        std::cout << "(" << inp.c.first << "," << inp.c.second << ") ";
        std::cout << "(" << inp.d.first << "," << inp.d.second << ")" << std::endl;
        return 0;
    }

    template<int index, typename... Args>
    struct iterate
    {
        static void forn(std::tuple<Args...> tpl)
        {
            iterate<index - 1, Args...>::forn(tpl);
            print_points(index, std::get<index>(tpl));
        }

    };

    template<typename... Args>
    struct iterate<0, Args...>
    {
        static void forn(std::tuple<Args...> tpl)
        {
            print_points(0, std::get<0>(tpl));
        }
    };

    template<typename... Args>
    struct iterate<-1, Args...>
    {
        static void forn(std::tuple<Args...> tpl)
        {
            std::cout << "tuple_print|forn: got empty tuple" << std::endl;
        }
    };


    template<typename... Args>
    void start(std::tuple<Args...> tpl)
    {
        const int ind = std::tuple_size <std::tuple<Args...>>::value;
        iterate<ind - 1, Args...>::forn(tpl);
    }

}