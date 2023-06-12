#include <iostream>
#include <string>

void ULLAsBitString(unsigned long long inp) //выводит переменную в виде 64-битового множества. выводит инвертированно (интерфейс адаптирован под инвертированный вывод, так что не проблема)
{
	int i = 0;
	while (inp > 0)
	{
		i++;
		std::cout << inp % 2;
		inp /= 2;
	}
	while (i < 64) //дописывает нули в конец (если надо)
	{
		i++;
		printf("0");
	}
}

int CountUnarBitsInULL(unsigned long long a) //считанет кол-во единичных битов в 64-битовом множестве
{
	int counter = 0;
	while (a > 0)
	{
		if (a % 2 == 1)
		{
			counter++;
		}

		a /= 2;
	}
	return counter;
}

unsigned long long pw(unsigned long long a, unsigned long long b) //функция вычисления степеней в формате unsighned long long (стандартная pow на больших числах рботала криво) 
{
	unsigned long long res = 1;
	for (int i = 0; i < b; i++)
	{
		res = res * a;
	}
	return res;
}