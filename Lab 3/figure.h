#pragma once
#include <vector>
#include <iostream>
#include "coords.h"

class figure
{
public:
    virtual double calculate_surface() const = 0;
    virtual my::dec_coords calculate_centre() const = 0;
    virtual std::string type() const = 0;

    std::vector<my::dec_coords> points;
    std::vector<my::dec_coords> allpoints;
    bool corr = false;
};

class rectangle : public figure
{
public:
    rectangle(my::dec_coords mas[3]);
    ~rectangle();

    std::string type() const;
    double calculate_surface() const;
    my::dec_coords calculate_centre() const;
};

class trapeze : public figure
{
public:
    trapeze(my::dec_coords mas[4]);
    ~trapeze();

    std::string type() const;
    double calculate_surface() const;
    my::dec_coords calculate_centre() const;
};

class rhomb : public figure
{
public:
    rhomb(my::dec_coords mas[3]);
    ~rhomb();

    std::string type() const;
    double calculate_surface() const;
    my::dec_coords calculate_centre() const;
};

std::ostream& operator<< (std::ostream& out, const rectangle& fig);
std::istream& operator>> (std::istream& in, rectangle& fig);

std::ostream& operator<< (std::ostream& out, const trapeze& fig);
std::istream& operator>> (std::istream& in, trapeze& fig);

std::ostream& operator<< (std::ostream& out, const rhomb& fig);
std::istream& operator>> (std::istream& in, rhomb& fig);

