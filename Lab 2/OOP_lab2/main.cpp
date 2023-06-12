//Гаврилов М.С. М8О-206Б-19
//Л.Р. #2. Вар. 16

//Создать класс Position для работы с географическими координатами.
//Координаты задаются двумя числами широта и долгота.
//Долгота находится в диапазоне от - 180 до 180 градусов.Широта находится в диапазоне от - 90 до 90 градусов.
//Реализовать арифметические операции сложения, вычитания, умножения и деления, а также операции сравнения в виде перегрузки операторов.
//Необходимо реализовать пользовательский литерал для работы с константами типа Position.

#include <iostream>
#include "Position.hpp"


int main()
{
	Position a_pos_one, a_pos_two; 
	for(;;)
	{	
		std::cout << "intput two coordinate pairs" << std::endl;
		std::cin >> a_pos_one >> a_pos_two;

		std::cout << "Position one is: " << a_pos_one << "\nPosition two is: " << a_pos_two << std::endl << std::endl;
		std::cout << "sum is: " << a_pos_one + a_pos_two << std::endl << "difference is: " << a_pos_one - a_pos_two << std::endl << "composition is: " << a_pos_one * a_pos_two << std::endl << "quotient is: " << a_pos_one / a_pos_two << std::endl << std::endl;
		if (a_pos_one > a_pos_two)
		{
			std::cout << "pos one is bigger than pos two" << std::endl;
		}
		else
		if (a_pos_one < a_pos_two)
		{
			std::cout << "pos one is smaller than pos two" << std::endl;
		}
		else
		if (a_pos_one == a_pos_two)
		{
			std::cout << "pos one is equal to than pos two" << std::endl;
		}
		else
		{
			std::cout << "unable to determine relation of pos one and pos two" << std::endl;
		}
		std::cout << "_________________________\n";
	}
}