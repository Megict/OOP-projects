#pragma once
#include <iostream>

namespace my
{
    class dec_coords
    {
    public:
        dec_coords();
        dec_coords(const double& x, const double& y);
        double x() const;
        double y() const;

        friend dec_coords operator+ (const dec_coords& lhs, const dec_coords& rhs);
        friend dec_coords operator- (const dec_coords& lhs, const dec_coords& rhs);
        friend dec_coords operator* (const dec_coords& lhs, const dec_coords& rhs);
        friend dec_coords operator/ (const dec_coords& lhs, const dec_coords& rhs);

        friend bool operator== (const dec_coords& lhs, const dec_coords& rhs);
        friend bool operator< (const dec_coords& lhs, const dec_coords& rhs);
        friend bool operator> (const dec_coords& lhs, const dec_coords& rhs);

        dec_coords& operator= (const dec_coords& rhs);

    private:
        double x_;
        double y_;
    };
}

std::ostream& operator<< (std::ostream& out, const my::dec_coords& coord);
double calculate_length(my::dec_coords a, my::dec_coords b);

bool are_parallel(my::dec_coords L1_a, my::dec_coords L1_b, my::dec_coords L2_a, my::dec_coords L2_b);
//проверяем на параллельность две прямые (l1 и l2, заданы двумя точками)

bool are_perpendecualr(my::dec_coords L1_a, my::dec_coords L1_b, my::dec_coords L2_a, my::dec_coords L2_b);

my::dec_coords centre(my::dec_coords a, my::dec_coords b);