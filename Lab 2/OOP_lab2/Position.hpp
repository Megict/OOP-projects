//Гаврилов М.С. М8О-206Б-19
//Л.Р. #2. Вар. 16

#pragma once
#include <iostream>

class Position
{
public:
	Position(const double& lng, const double& lat);
	Position();

	double get_latitude() const;
	double get_longitude() const;

	friend Position operator+ (const Position& lhs, const Position& rhs);
	friend Position operator- (const Position& lhs, const Position& rhs);
	friend Position operator* (const Position& lhs, const Position& rhs);
	friend Position operator/ (const Position& lhs, const Position& rhs);

	friend bool operator< (const Position& lhs, const Position& rhs);
	friend bool operator> (const Position& lhs, const Position& rhs);
	friend bool operator== (const Position& lhs, const Position& rhs);

	void operator= (const Position& rhs);

private:
	double longitude_;
	double latitude_;
};

std::ostream& operator<< (std::ostream& out, const Position& position);
std::istream& operator>> (std::istream& out, Position& position);

Position operator "" _pos(const char* inp, size_t size);
