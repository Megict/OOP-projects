//вариант 3
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <memory>
#include <algorithm>
#include <cmath>
#include <string>
#include <deque>
#include <functional>
#include <fstream>
#include "figures.h"
#include "factory.h"
#include "figure_collection.h"

class handler {
private:
    std::vector<std::function<int(MyFigures::figure<double>*)>> writers;
    std::vector<MyFigures::figure<double>*>* buffer;
    std::ofstream writeFile;
    bool work;
    bool* hasNewMsg;
public:
    handler(std::vector<MyFigures::figure<double>*>* buf,std::string& filename, bool* msgMark) {
        buffer = buf;
        work = false;
        writeFile = std::ofstream(filename, std::ios_base::out);
        writers.push_back([](MyFigures::figure<double>* elem) -> int { /*вывод на экран*/
            std::cout << elem->GetPoints()[0].first << " " << elem->GetPoints()[0].second << " ";
            std::cout << elem->GetPoints()[1].first << " " << elem->GetPoints()[1].second << " ";
            std::cout << elem->GetPoints()[2].first << " " << elem->GetPoints()[2].second << " ";
            std::cout << elem->GetPoints()[3].first << " " << elem->GetPoints()[3].second << "\n";

            return 0;
        });
        writers.push_back([=](MyFigures::figure<double>* elem) -> int {/*вывод в файл*/ 
            writeFile << elem->GetPoints()[0].first << " " << elem->GetPoints()[0].second << " ";
            writeFile << elem->GetPoints()[1].first << " " << elem->GetPoints()[1].second << " ";
            writeFile << elem->GetPoints()[2].first << " " << elem->GetPoints()[2].second << " ";
            writeFile << elem->GetPoints()[3].first << " " << elem->GetPoints()[3].second << "\n";

            return 0; 
        });
        hasNewMsg = msgMark;
    }

    void operator()() {

        //std::cout << "[" << std::this_thread::get_id() << "] " << "Handler operating\n";
        work = true;

        while (work) {
            if (*hasNewMsg) {
                std::cout << "writing...\n";
                std::for_each(buffer->begin(), buffer->end(), writers[0]);
                std::for_each(buffer->begin(), buffer->end(), writers[1]);
                *hasNewMsg = false;
            }
        }
    }

    void stop() {
        std::cout << "stopping\n";
        work = false;
    }

};

int main(int argc, char* argv[]) {
    int N = 0;
    std::string filename("file1.txt");
    if (argc == 1) {
        std::cout << "input max buff size\n";
        std::cin >> N;
    } 
    else {
        N = argv[1][0];
    }

    if (argc == 1) {
        std::cout << "input -out filename\n";
        std::cin >> filename;
    }
    else {
        filename = std::string(argv[2]);
    }

    std::vector<MyFigures::figure<double>*> buffer;
    
    bool msgMark = false;
    //std::cout << "[" << std::this_thread::get_id() << "]\n";

    handler hdl(&buffer,filename,&msgMark);//обработчик, что производит вывод

    std::thread thr(std::ref(hdl));

    FigureCollection mainCollection;


    //стандартный парсер
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
                    mainCollection.add(points, "rect");
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
                    mainCollection.add(points, "rhmb");
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
                    mainCollection.add(points, "trap");
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
        if (inp == "quit" || inp == "q")
        {
            hdl.stop();
            thr.join();
            return 0;
        }
        else
        {
            std::cout << "cmd: incorrect input\n";
        }

        //
        if (mainCollection.size() == N) {
            buffer = mainCollection.getElements();
            msgMark = true;
            while (true) {
                if (msgMark == false) {
                    mainCollection.clear();

                    break;
                }
            }
        }

        if (mode == 0) std::cout << " |cmd|=> ";
    }
    

    hdl.stop();
    thr.join();
    return 0;
}