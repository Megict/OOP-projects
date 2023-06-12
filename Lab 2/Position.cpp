//Гаврилов М.С. М8О-206Б-19
//Л.Р. #2. Вар. 16

#include <iostream>
#include <string>
#include "Position.hpp"

Position::Position(const double& lng, const double& lat)
{
	longitude_ = lng; //долгота
	latitude_ = lat; //широта
	while (longitude_ > 180.0) //значения приводятся в необходимый диапазон прямо в конструкторе
	{
		longitude_ -= 180.0;
	}
	while (longitude_ < -180.0)
	{
		longitude_ += 180.0;
	}
	while (latitude_ > 90.0)
	{
		latitude_ -= 90.0;
	}
	while (latitude_ < -90.0)
	{
		latitude_ += 90.0;
	}
}

Position::Position()
{
	longitude_ = 0.0;
	latitude_ = 0.0;
}

double Position::get_latitude() const
{
	return latitude_;
}

double Position::get_longitude() const
{
	return longitude_;
}

void Position::operator= (const Position& rhs)
{
	longitude_ = rhs.longitude_; 
	latitude_ = rhs.latitude_;
}


Position operator+ (const Position& lhs, const Position& rhs) //операторы +-*/ реализуются просто почленным применением к частям к элементам класса
{ 
	Position res(lhs.longitude_ + rhs.longitude_, lhs.latitude_ + rhs.latitude_);
	return res;
}

Position operator- (const Position& lhs, const Position& rhs)
{
	Position res(lhs.longitude_ - rhs.longitude_, lhs.latitude_ - rhs.latitude_);
	return res;
}

Position operator* (const Position& lhs, const Position& rhs)
{
	Position res(lhs.longitude_ * rhs.longitude_, lhs.latitude_ * rhs.latitude_);
	return res;
}

Position operator/ (const Position& lhs, const Position& rhs)
{
	Position res(lhs.longitude_ / rhs.longitude_, lhs.latitude_ / rhs.latitude_);
	return res;
}

bool operator< (const Position& lhs, const Position& rhs) //оператор < возвращает истину, только если и долгота, и широта левого элемента сеньше правого 
{
	if (lhs.longitude_ < rhs.longitude_)
	{
		if (lhs.latitude_ < rhs.latitude_)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool operator> (const Position& lhs, const Position& rhs) //аналогично и для >
{
	if (lhs.longitude_ > rhs.longitude_)
	{
		if (lhs.latitude_ > rhs.latitude_)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool operator==(const Position& lhs, const Position& rhs) //оператор == возвращае истину, если и широта и долгота обоих элементов соответственно, равны
{
	if (lhs.latitude_ == rhs.latitude_ && lhs.longitude_ == rhs.longitude_)
	{
		return true; 
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const Position& position)
{
	std::cout.precision(6);
	out << position.get_longitude() << " " << position.get_latitude();
	return out;
}

std::istream& operator>>(std::istream& in, Position& position)
{
	double lng, lat;
	in >> lng;
	in >> lat;
	position = Position(lng, lat);
	return in;
}

bool correct_char(char a) //проверка на корректный символ в строке
{
	if ((a >= '0' && a <= '9') || a == '.' || a == ' ' || a == '-')
	{
		return true;
	}
	return false;
}

Position operator"" _pos(const char* inp, size_t size)//лиерал, который должен приписываться к строке. Далее строка посимвольно разбирается и преобразуется в position 
{
	int mode = 0;
	int a_count = 0;
	int b_count = 0;
	int min_mark_a = 1;
	int min_mark_b = 1;
	int j = 1; 
	unsigned long long ua = 0, ub = 0;
	for (int i = size-1; i >= 0; --i)
	{
		if (!correct_char(inp[i]))
		{
			return Position();
		}

		if (inp[i] == '.')//переключение между режимами ввода. режим определяет, в какую часть (долготу или широту) будет записываться символ
		{
			if (mode == 0)
			{
				mode = 1;
				continue;
			}
			else
			if (mode == 2)
			{
				mode = 3;
				continue;
			}
			else
			{
				return Position();
			}
		}
		else
		if (inp[i] == ' ')
		{
			if (mode == 1)
			{
				j = 1;
				mode = 2;
				continue;
			}
			else
			{
				return Position();
			}
		}
		else 
		if (inp[i] == '-') //отдельный вариант для минуса
		{
			if (mode == 1 && i > 0 && inp[i-1] == ' ')
			{
				min_mark_b = -1;
				continue;
			}
			else
			if (mode == 3 && i == 0)
			{
				min_mark_a = -1;
				continue;
			}
			else
			{
				return Position();
			}
		}
			
		if (mode == 0 || mode == 1) //собственно, заполнение 
		{
			if (mode == 0)
			{
				a_count++;
			}
			ub += (inp[i] - 48ULL)*j;
			j *= 10;
		}
		if (mode == 2 || mode == 3)
		{
			if (mode == 2)
			{
				b_count++;
			}
			ua += (inp[i] - 48ULL)*j;
			j *= 10;
		}

	}

	double a = ua;
	double b = ub;

	a /= pow(10,a_count);
	b /= pow(10,b_count); 

	a *= min_mark_a;
	b *= min_mark_b;

	printf("\n\n%lf\n%lf\n", a, b);

	return Position(a,b);
}
