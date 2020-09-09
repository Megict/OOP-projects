//Задание. Вариант #7
//
//Создать класс BitString для работы с 128 - битовыми строками.Битовая строка должна быть представлена двумя 
//полями типа unsigned long long. Должны быть реализованы все традиционные операции для работы с битами: and, 
//or, xor, not. Реализовать сдвиг влево shiftLeft и сдвиг вправо shiftRight на заданное количество битов.
//Реализовать операцию вычисления количества единичных битов, операции сравнения по количеству единичных битов.
//Реализовать операцию проверки включения.

#include <iostream>
#include <string>
#include "ULL_arifm.h"

class BitString //класс битовой строки (множетсва их 128 бит) 
{
private: //создана из двух склеенных переменных типа unsigned long long
	unsigned long long FieldOne_;
	unsigned long long FieldTwo_;
public:
	BitString(const unsigned long long& left, const unsigned long long& right) //просто конструктор, по сути не используется...
	{
		FieldOne_ = left;
		FieldTwo_ = right;
	}

	unsigned long long GetFieldOne () const //возвращает первую часть составного множества 
	{
		return FieldOne_;
	}

	unsigned long long GetFieldTwo () const //возвращает вторую часть
	{
		return FieldTwo_;
	}

	void rightShift(unsigned long long a) //правый сдвиг на a элементов
	{
		unsigned long long FieldOne = FieldOne_;
		unsigned long long FieldTwo = FieldTwo_;

		FieldTwo = FieldTwo << a; //так как множество хранится в памяти инвертированно, используем левый сдвиг для каждого из полей. На экране будет выглядеть как правый сдвиг.
		FieldTwo |= FieldOne >> (64 - a); //так реализектся переход некоторых битов через границу полей
		FieldOne = FieldOne << a;

		FieldOne_ = FieldOne;
		FieldTwo_ = FieldTwo;
	}

	void LeftShift(int a) //левый сдвиг на a элементов
	{
		unsigned long long FieldOne = FieldOne_;
		unsigned long long FieldTwo = FieldTwo_;

		FieldOne = FieldOne >> a;
		FieldOne |= FieldTwo << (64 - a);
		FieldTwo = FieldTwo >> a;

		FieldOne_ = FieldOne;
		FieldTwo_ = FieldTwo;
	}

	int ContUnarBits() const //подсчет единичных битов во всем 128-битном множестве
	{
		unsigned long long FieldOne = FieldOne_; 
		unsigned long long FieldTwo = FieldTwo_;

		return CountUnarBitsInULL(FieldOne) + CountUnarBitsInULL(FieldTwo);// реализован как подсчет ед.битов в каждом поле по отдельности
	}

	void PrintAsNum() const //вывод числовых значений каждого из полей (не используется, но может пригодиться при отладке)
	{
		std::cout << FieldOne_ << FieldTwo_ << std::endl;
	}

	void print() const //вывод множества в виде битовой строки (128 нолей и единичек под ряд)
	{
		ULLAsBitString(FieldOne_); ULLAsBitString(FieldTwo_); //реализовано как аоследовательный вызов функций вывода 64-юитных множеств.
	}

	int FillBitStr() //заполнение битовой строки со стандартного ввода. возвращает 0, если заполнение успешно выполнено, 1 - если дано больше, чем 128 битов, 2 - если меньше, чем 128 битов, 3 -введено что-то помимо 1/0
	{
		unsigned long long FieldOne = 0;
		unsigned long long FieldTwo = 0;
		char a;
		for (int i = 0; i < 128;) //цикл, в котором происходит посимвольный ввод элементов множества (0/1) 
		{
			//вначале (первые 64 итерации) заполняется первое поле. Затем второе
			scanf_s("%c", & a); 
			if ((a == '1'))
			{
				if (i < 64)//проверка, в какое из полей надо записать единицу
					FieldOne += pw(2, i % 64); //собственно, запись элементов в битовое множество производится путем прибавлению к текущему значению того или иного поля двойки в степени "порядкового номера" добавляемого бита
				if (i >= 64)
					FieldTwo += pw(2, i % 64); //этот порядковый номер определяется текущим шагом цикла

				i++;
			}
			else
			if (a == '0')
			{
				i++;
			}
			else
			{
				if (a == 10)//если еще не прошло 128 шагов, а было введено что-то помимо 0/1, возвращает ошибку
					return 2;
				else
					return 3;
			}
		}
		scanf_s("%c", &a); //чтение контрольного символа. Если ввод строки закончился нажатием enter (код 10), то мы считаем что заполнение успешно завершено. 
		//если же ввод каких-то (неважно каких) символов продолжился, то происходит возврат сообщения об ошибки.
		if (a != 10)
		{
			return 1;
		}

		FieldOne_ = FieldOne;
		FieldTwo_ = FieldTwo;
		return 0;
	}
};

//последующие четыре оператора реализованы простым выполнением тех или иных побитовых операций с каждым из двух полей множества (множеств). 
const BitString operator ~ (const BitString& cnb)
{
	BitString res(~cnb.GetFieldOne(), ~cnb.GetFieldTwo());
	return res;
}

BitString operator & (const BitString& lhs, const BitString& rhs)
{
	BitString res(lhs.GetFieldOne() & rhs.GetFieldOne(), lhs.GetFieldTwo() & rhs.GetFieldTwo());
	return res;
}

BitString operator | (const BitString& lhs, const BitString& rhs)
{
	BitString res(lhs.GetFieldOne() | rhs.GetFieldOne(), lhs.GetFieldTwo() | rhs.GetFieldTwo());
	return res;
}

BitString operator ^ (const BitString& lhs, const BitString& rhs)
{
	BitString res(lhs.GetFieldOne() ^ rhs.GetFieldOne(), lhs.GetFieldTwo() ^ rhs.GetFieldTwo());
	return res;
}

bool operator > (const BitString& lhs,const BitString& rhs) //оператор сравнения "больше" по количеству элементов (единичных битов) 
{
	if (lhs.ContUnarBits() > rhs.ContUnarBits())//у нас уже есть функция подсчета единичных битов, так что реализуется все очень просто
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator < (const BitString& lhs, const BitString& rhs) //оператор сравнения "меньше" по количеству элементов (единичных битов) 
{
	if (lhs.ContUnarBits() < rhs.ContUnarBits())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator == (const BitString& lhs, const BitString& rhs) //оператор сравнения "равняется" по количеству элементов (единичных битов) 
{
	if (rhs.GetFieldOne() == lhs.GetFieldOne())
	{
		if (rhs.GetFieldTwo() == lhs.GetFieldTwo())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool IncChek (const BitString& lhs, const BitString& rhs) //проверка включения множества lhs в множество rhs. под "включением" подразумевается то что все элементы lhs присутствуют также и в rhs 
{
	if ((lhs | rhs) == rhs)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()//в фунции main реализован небольшой тестовый интерфейс, позволяющий проверить работоспособность класса
{
	int cheker = 0;//это переменная, в которую записывается код завершения той или иной функции для последующий проверки на ошибки

	printf("Input bit string #1 (128 bits required)\n");
	BitString ABitString1(0,0); cheker = ABitString1.FillBitStr(); //ввод первой битовой строки. 

	if (cheker == 3)//проверка ошибок. если обнаружена ошибка, завершаем рабту программы
	{
		std::cout << "wrong input ('1' or '0' required)\n";
		return 103;
	}
	else 
	if (cheker == 2)
	{
		std::cout << "too few bits inputed (need 128)\n";
		return 102;
	}
	else 
	if (cheker == 1)
	{
		std::cout << "too many bits inputed (need 128)\n";
		return 101;
	}

	printf("Input bit string #2 (128 bits required)\n");
	BitString ABitString2(0,0); cheker = ABitString2.FillBitStr();//ввод второй строки

	if (cheker == 3)//проверка ошибок. если обнаружена ошибка, завершаем рабту программы
	{
		std::cout << "wrong input ('1' or '0' required)\n";
		return 103;
	}
	else
	if (cheker == 2)
	{
		std::cout << "too few bits inputed (need 128)\n";
		return 102;
	}
	else
	if (cheker == 1)
	{
		std::cout << "too many bits inputed (need 128)\n";
		return 101;
	}

	BitString ABitStringRes(0,0);//объявление третей строки, нужной для отображения результатов операций. введенные ранее строки останутся неизменными.

	printf("\nGot "); ABitString1.print(); printf(" as bit string #1 (%d '1' bits in it)\n", ABitString1.ContUnarBits());//вывод полученных строк. просто чтобы убедиться, что все считано верно. 
	printf("Got "); ABitString2.print(); printf(" as bit string #2 (%d '1' bits in it)\n\n", ABitString2.ContUnarBits());

	//объявление "эталонных" строк с доступными при роботе командами. 
	std::string s1and = "&";
	std::string s2or = "|";
	std::string s3xor = "^";
	std::string s4no = "~";

	std::string s5 = "<<";
	std::string s6 = ">>";

	std::string s7 = ">";
	std::string s8 = "<";

	std::string s9 = "count";
	std::string s10 = "inclusion?";

	std::cout << "Available commands:\n" << s1and << " - bitwise AND\n" << s2or << " - bitwise OR\n" << s3xor << " - bitwise XOR\n" << s4no << " - bitwise NO\n";
	std::cout << s5 << " - left shift\n" << s6 << " - right shift\n" << s7 << " - (is s1 > s2 ?)\n" << s8 << " - (is s1 < s2 ?)\n" << s9 << " - count unar bits\n" << s10 << " - (is s1 included in s2 ?)\n" << std::endl;

	std::string input;//объявление строки, в которой записывается сообщение пользователя

	for (;;)// в ходе работы происходит считывание сообщения пользователя, после чего оно сравнивается с каждым из доступных имен комнд и, если было найдено совпадение, команда выполняется, иначе выводится сообщение о вводе некорректной команды 
	{
		std::cin >> input;

		if (input == s1and)
		{
			ABitStringRes = ABitString1 & ABitString2;
			ABitStringRes.print(); printf("\n");
		}
		else
		if (input == s2or)
		{
			ABitStringRes = ABitString1 | ABitString2;
			ABitStringRes.print(); printf("\n");
		}
		else
		if (input == s3xor)
		{
			ABitStringRes = ABitString1 ^ ABitString2;
			ABitStringRes.print(); printf("\n");
		}
		else
		if (input == s4no)
		{
			printf("apply to string (1 or 2) ?\n"); //в некоторых случаях (к примеру, если команда состоит в применении унарного оператора) у пользователя такж запрашивается дополнительная информация о том, к какой строке применить команду. 
			std::cin >> input;
			if (input == "1")
			{
				ABitStringRes = ~ABitString1;
				ABitStringRes.print(); printf("\n");
			}
			else
			if (input == "2")
			{
				ABitStringRes = ~ABitString2;
				ABitStringRes.print(); printf("\n");
			}
			else
			{
				printf("incorrect identifer\n");
			}
		}
		else
		if (input == s5)
		{
			printf("(l) input shift step\n"); //также может быть запрошен шаг для осуществления побитового сдвига.
			int step; std::cin >> step;
			if (step > 128) { step = 128; }
			if (step < -128) { step = -128; }
			printf("apply to string (1 or 2) ?\n");
			std::cin >> input;
			if (input == "1")
			{
				ABitStringRes = ABitString1;
				ABitStringRes.LeftShift(step);
				ABitStringRes.print(); printf("\n");
			}
			else
			if (input == "2")
			{
				ABitStringRes = ABitString2;
				ABitStringRes.LeftShift(step);
				ABitStringRes.print(); printf("\n");
			}
			else
			{
				printf("incorrect identifer\n");
			}
		}
		else
		if (input == s6)
		{
			printf("(r) input shift step\n");
			int step; std::cin >> step;
			if (step > 128) { step = 128; }
			if (step < -128) { step = -128; }
			printf("apply to string (1 or 2) ?\n");
			std::cin >> input;
			if (input == "1")
			{
				ABitStringRes = ABitString1;
				ABitStringRes.rightShift(step);
				ABitStringRes.print(); printf("\n");
			}
			else
			if (input == "2")
			{
				ABitStringRes = ABitString2;
				ABitStringRes.rightShift(step);
				ABitStringRes.print(); printf("\n");
			}
			else
			{
				printf("incorrect identifer\n");
			}
		}
		else
		if (input == s7)
		{
			if (ABitString1 > ABitString2)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}
		}
		else
		if (input == s8)
		{
			if (ABitString1 < ABitString2)
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}
		}
		else
		if (input == s9)
		{
			printf("apply to string (1 or 2) ?\n");
			std::cin >> input;
			if (input == "1")
			{
				printf("%d\n", ABitString1.ContUnarBits());
			}
			else
			if (input == "2")
			{
				printf("%d\n", ABitString2.ContUnarBits());
			}
			else
			{
				printf("incorrect identifer\n");
			}
		}
		else
		if (input == s10)
		{
			if (IncChek(ABitString1, ABitString2) == 1)
			{
				printf("String one is included in String Two\n");
			}
			else
			if (IncChek(ABitString2, ABitString1) == 1)
			{
				printf("String two is included in String one\n");
			}
			else
			{
				printf("No inclusion detected\n");
			}
		}
		else
		{
			printf("incorrect command\n");
		}
	}
	return 0;
}



