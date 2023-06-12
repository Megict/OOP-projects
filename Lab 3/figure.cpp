#include "figure.h"
#include <cmath>

double figure::calculate_surface() const
{
    return 0.0;
}

rectangle::rectangle(my::dec_coords mas[3])
{
    //на вход идут три точки по разные концы от прямоугольника
    corr = true;
    if (are_perpendecualr(mas[0], mas[1], mas[1], mas[2]) || are_perpendecualr(mas[0], mas[1], mas[0], mas[2]) || are_perpendecualr(mas[0], mas[2], mas[1], mas[2]))
    {
        for (int i = 0; i < 3; ++i)
        {
            points.push_back(mas[i]);
        }


        allpoints = points;

        if (are_perpendecualr(mas[0], mas[1], mas[1], mas[2]))
        {
            allpoints.push_back(mas[0] + (mas[2] - mas[1]));
        }
        else 
        if (are_perpendecualr(mas[0], mas[1], mas[0], mas[2]))
        {
            allpoints.push_back(mas[1] + (mas[2] - mas[0]));
        }
        else
        if (are_perpendecualr(mas[0], mas[2], mas[1], mas[2]))
        {
            allpoints.push_back(mas[1] + (mas[0] - mas[2]));
        }
        
    }
    else
    {
        corr = false;
    }
}

rectangle::~rectangle()
{
    points.empty();
}

std::string rectangle::type() const
{
    return std::string("rect");
}

double rectangle::calculate_surface() const
{
    //найти две точки, одна больше дургой, по разности координат посчитать площадь

    double length = 0;
    double heigth = 0;

    if (are_perpendecualr(points[0], points[1], points[1], points[2]))
    {
        length = calculate_length(points[2] - points[1], points[0] - points[1]);
        heigth = calculate_length(points[0] - points[1], points[2] - points[1]);
    }
    else
    if (are_perpendecualr(points[0], points[1], points[0], points[2]))
    {
        length = calculate_length(points[2] - points[0], points[1] - points[0]);
        heigth = calculate_length(points[1] - points[0], points[2] - points[0]);
    }
    else
    if (are_perpendecualr(points[0], points[2], points[1], points[2]))
    {
        length = calculate_length(points[1] - points[2], points[0] - points[2]);
        heigth = calculate_length(points[0] - points[2], points[1] - points[2]);
    }

    return length*heigth;
}

my::dec_coords rectangle::calculate_centre() const
{
    my::dec_coords cent = my::dec_coords();

    if (are_perpendecualr(points[0], points[1], points[1], points[2]))
    {
        cent = centre(points[0], points[2]);
    }
    else
    if (are_perpendecualr(points[0], points[1], points[0], points[2]))
    {
        cent = centre(points[1], points[2]);
    }
    else
    if (are_perpendecualr(points[0], points[2], points[1], points[2]))
    {
        cent = centre(points[0], points[1]);
    }

    return cent;
}

rhomb::rhomb(my::dec_coords mas[3])//первые две точки - координаты гипотенузы, третья случайная из двух оставшихся
{
    double l1 = calculate_length(mas[0], mas[1]);
 //   printf("l1: %lf\n", l1);
    double l2 = calculate_length(mas[0], mas[2]);
 //   printf("l2: %lf\n", l2);
    double l3 = calculate_length(mas[1], mas[2]);
 //   printf("l3: %lf\n", l3);

    corr = true;
    if (l1 == l2 || l2 == l3 || l1 == l3)
    {
        for (int i = 0; i < 3; ++i)
        {
            points.push_back(mas[i]);
        }

        allpoints = points; 

        if (l1 == l2)
        {
            allpoints.push_back(mas[1] + (mas[2] - mas[0]));
        }
        else
        if (l1 == l3)
        {
            allpoints.push_back(mas[0] + (mas[2] - mas[1]));
        }
        else
        if (l2 == l3)
        {
            allpoints.push_back(mas[2] + (mas[1] - mas[3]));
        }
    }
    else
    {
        corr = false;
    }
}

rhomb::~rhomb()
{
    points.empty();
}

std::string rhomb::type() const
{
    return std::string("rhmb");
}

double rhomb::calculate_surface() const
{
    //подсчет площади треугольника (средниего, из которого состоит ромб)
    double surface = ((points[0].x() - points[2].x()) * (points[1].y() - points[2].y()) - (points[1].x() - points[2].x()) * (points[0].y() - points[2].y()));
    return abs(surface);
}

my::dec_coords rhomb::calculate_centre() const
{
    double l1 = calculate_length(points[0], points[1]);
    double l2 = calculate_length(points[0], points[2]);
    double l3 = calculate_length(points[1], points[2]);

    if (l1 == l2)
    {
        return centre(points[1], points[2]);//центр L3
    }
    else
    if (l1 == l3)
    {
        return centre(points[0], points[2]);//центр L2
    }
    else 
    if (l2 == l3)
    {
        return centre(points[0], points[1]);//центр L1
    }
    else
    return my::dec_coords();
}

trapeze::trapeze(my::dec_coords mas[4])
{
    //строим по 4м точкам + проверка на то что это трапеция
    //проверяем, есть ли среди противоположных прямых параллельные
    ///std::cout << mas[0] << " | " << mas[1] << " | " << mas[2] << " | " << mas[3] << std::endl;
    corr = true;
    if (are_parallel(mas[0], mas[1], mas[2], mas[3]) || are_parallel(mas[1], mas[2], mas[0], mas[3]) || are_parallel(mas[0], mas[2], mas[1], mas[3]))
    {
        for (int i = 0; i < 4; i++)
        {
            points.push_back(mas[i]);
        }
        allpoints = points;
    }
    else
    {
        corr = false;
    }
}

trapeze::~trapeze()
{
    points.empty();
}

std::string trapeze::type() const
{
    return std::string("trap");
}

double trapeze::calculate_surface() const
{
    my::dec_coords l1_a;
    my::dec_coords l1_b;
    my::dec_coords l2_a;
    my::dec_coords l2_b;
    if (are_parallel(points[0], points[1], points[2], points[3]))
    {
        l1_a = points[0];
        l1_b = points[1];
        l2_a = points[2];
        l2_b = points[3];
    }
    if (are_parallel(points[1], points[2], points[0], points[3]))
    {
        l1_a = points[1];
        l1_b = points[2];
        l2_a = points[0];
        l2_b = points[3];
    }
    if (are_parallel(points[0], points[2], points[1], points[3]))
    {
        l1_a = points[0];
        l1_b = points[2];
        l2_a = points[1];
        l2_b = points[3];
    }
    
    my::dec_coords Vec1 = l1_b - l1_a;
    my::dec_coords Vec2 = l2_b - l2_a;

    Vec1 = my::dec_coords(Vec1.y(), Vec1.x());
    Vec2 = my::dec_coords(Vec2.y(), Vec2.x());

    //std::cout << l1_a << " " << l1_b << "\n" << l2_a << " " << l2_b << "\n";

    double A1, B1, C1;
    double A2, B2, C2;
    A1 = l1_b.y() - l1_a.y();
    A2 = l2_b.y() - l2_a.y();

    B1 = -1*(l1_b.x() - l1_a.x());
    B2 = -1*(l2_b.x() - l2_a.x());

    C1 = l1_a.y() * (l1_b.x() - l1_a.x()) - l1_a.x() * (l1_b.y() - l1_a.y());
    C2 = l2_a.y() * (l2_b.x() - l2_a.x()) - l2_a.x() * (l2_b.y() - l2_a.y());

    //std::cout << A1 << " " << B1 << " " << C1 << "\n" << A2 << " " << B2 << " " << C2 << "\n";

    double h = abs(A2 * l1_a.x() + B2 * l1_a.y() + C2)/(sqrt(pow(A2,2)+pow(B2,2)));

    //std::cout << calculate_length(l1_a, l1_b) << " " << calculate_length(l2_a, l2_b) << std::endl;

    return h * (calculate_length(l1_a, l1_b) + calculate_length(l2_a,l2_b))/2;
}

my::dec_coords trapeze::calculate_centre() const
{
    my::dec_coords l1_a;
    my::dec_coords l1_b;
    my::dec_coords l2_a;
    my::dec_coords l2_b;
    if (are_parallel(points[0], points[1], points[2], points[3]))
    {
        l1_a = points[0];
        l1_b = points[1];
        l2_a = points[2];
        l2_b = points[3];
    }
    if (are_parallel(points[1], points[2], points[0], points[3]))
    {
        l1_a = points[1];
        l1_b = points[2];
        l2_a = points[0];
        l2_b = points[3];
    }
    if (are_parallel(points[0], points[2], points[1], points[3]))
    {
        l1_a = points[0];
        l1_b = points[2];
        l2_a = points[1];
        l2_b = points[3];
    }

    return centre (centre(l1_a, l1_b), centre(l2_a, l2_b));
}

std::ostream& operator<<(std::ostream& out, const rectangle& fig)
{
    for (size_t i = 0; i < fig.points.size(); ++i)
    {
        out << fig.points[i] << " | ";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const trapeze& fig)
{
    for (size_t i = 0; i < fig.points.size(); ++i)
    {
        out << fig.points[i] << " | ";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const rhomb& fig)
{
    for (size_t i = 0; i < fig.points.size(); ++i)
    {
        out << fig.points[i] << " | ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, rectangle& fig)
{
    my::dec_coords pairs[3];
    for (int i = 0; i < 3; ++i)
    {
        double x, y;
        in >> x, y;
        pairs[i] = my::dec_coords(x, y);
    }
    fig = rectangle(pairs);
    return in;
}

std::istream& operator>>(std::istream& in, trapeze& fig)
{
    my::dec_coords pairs[3];
    for (int i = 0; i < 3; ++i)
    {
        double x, y;
        in >> x, y;
        pairs[i] = my::dec_coords(x, y);
    }
    fig = trapeze(pairs);
    return in;
}

std::istream& operator>>(std::istream& in, rhomb& fig)
{
    my::dec_coords pairs[4];
    for (int i = 0; i < 4; ++i)
    {
        double x, y;
        in >> x, y;
        pairs[i] = my::dec_coords(x, y);
    }
    fig = rhomb(pairs);
    return in;
}