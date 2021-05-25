/*
** EPITECH PROJECT, 2018
** data.cpp
** File description:
** data
*/

#include "data.hpp"

Coo::Coo(int a, int b)
{
    x = a;
    y = b;
}

Coo::~Coo()
{
}

Data::Data()
{
}

Data::~Data()
{
}

void Data::addCoo(int a, int b)
{
    data.push_back(new Coo(a, b));
}
