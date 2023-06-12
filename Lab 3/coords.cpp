#include "..\..\..\Desktop\ООП\Лаба3\coords.h"
#include <cmath>

namespace my
{
    dec_coords::dec_coords()
    {
        x_ = 0.0;
        y_ = 0.0;
    }

    dec_coords::dec_coords(const double& x, const double& y)
    {
        x_ = x;
        y_ = y;
    }

    double dec_coords::x() const
    {
        return x_;
    }

    double dec_coords::y() const
    {
        return y_;
    }

    dec_coords& dec_coords::operator=(const dec_coords& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        x_ = rhs.x_;
        y_ = rhs.y_;
        return *this;
    }

    dec_coords operator+(const dec_coords& lhs, const dec_coords& rhs)
    {
        return dec_coords(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
    }

    dec_coords operator-(const dec_coords& lhs, const dec_coords& rhs)
    {
        return dec_coords(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
    }

    dec_coords operator*(const dec_coords& lhs, const dec_coords& rhs)
    {
        return dec_coords(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
    }

    dec_coords operator/(const dec_coords& lhs, const dec_coords& rhs)
    {
        return dec_coords(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_);
    }

    bool operator==(const dec_coords& lhs, const dec_coords& rhs)
    {
        if (lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_)
        {
            return true;
        }
        return false;
    }

    bool operator<(const dec_coords& lhs, const dec_coords& rhs)
    {
        if (lhs.x_ < rhs.x_ && lhs.y_ < rhs.y_)
        {
            return true;
        }
        return false;
    }

    bool operator>(const dec_coords& lhs, const dec_coords& rhs)
    {
        if (lhs.x_ > rhs.x_ && lhs.y_ > rhs.y_)
        {
            return true;
        }
        return false;
    }
}

std::ostream& operator<<(std::ostream& out, const my::dec_coords& coord)
{
    //возможно, нужен cout.precision
    double x = coord.x();
    double y = coord.y();
    out << x << " " << y;
    return out;
}

double calculate_length(my::dec_coords a, my::dec_coords b)
{
    /*double x = b.x() - a.x();
    double y = b.y() - a.y();*/
    return sqrt(pow(b.x()-a.x(),2)+pow(b.y()-a.y(),2));
}

bool are_parallel(my::dec_coords L1_a, my::dec_coords L1_b, my::dec_coords L2_a, my::dec_coords L2_b)
//проверяем на параллельность две прямые (l1 и l2, заданы двумя точками)
{
 //   std::cout << L1_a << " | " << L1_b << " <-L1|L2-> " << L2_a << " | " << L2_b << std::endl;
    L1_b = L1_b - L1_a;
    L2_b = L2_b - L2_a;
 //   std::cout << L1_b << "\n" << L2_b << std::endl;
    if ((L1_b.y() == 0 && L2_b.y() == 0) || (L1_b.x()==0 && L2_b.x()==0)||(L1_b.x() / L1_b.y() == L2_b.x() / L2_b.y()))
    {
 //       std::cout << "parallel\n" << std::endl;
        return true;
    }
    return false;
}

bool are_perpendecualr(my::dec_coords L1_a, my::dec_coords L1_b, my::dec_coords L2_a, my::dec_coords L2_b)
{
    L1_b = L1_b - L1_a;
    L2_b = L2_b - L2_a;
    if (L1_b.x() * L2_b.x() + L1_b.y() * L2_b.y() == 0.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

my::dec_coords centre(my::dec_coords a, my::dec_coords b)
{
    return my::dec_coords((a.x()+b.x())/2.0,(a.y()+b.y())/2.0);
}
