#pragma once

template <class T> 
class iterator : public std::iterator<std::forward_iterator_tag, T, int, T*, T&>
{
public:

    iterator(T* start,int pos)
    {
        current_element = start;
        position = pos;
    }

    T elem()
    {
        return *current_element;
    }

    int get_position()
    {
        return position;
    }

    iterator<T>& operator= (const iterator<T> &rhs)
    {
        current_element = rhs.current_element;
        position = rhs.position;
        return *this;
    }

    iterator<T>& operator++ ()
    {
        iterator<T> ret = *this;
        ++position;
        current_element = &current_element[1];
        return ret;
    }

    iterator<T> operator++ (int)
    {
        ++position;
        current_element = &current_element[1];
        return *this;
    }

    iterator<T> operator-- (int)
    {
        --position;
        current_element = &current_element[-1];
        return *this;
    }

    const T operator* ()
    {
        return *current_element;
    }

    const bool operator== (const iterator<T>& rhs)
    {
        if (current_element == rhs.current_element)
            return true;
        else
            return false;
    }

    const bool operator!= (const iterator<T>& rhs)
    {
        if (current_element != rhs.current_element)
            return true;
        else
            return false;
    }

private:
    T* current_element;
    int position;
};

