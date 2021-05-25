/*
** EPITECH PROJECT, 2018
** data.cpp
** File description:
** data
*/

#include "data.hpp"

Coo::Coo(int a, int b, std::string ty)
{
    x = a;
    y = b;
    type = ty;
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

void Data::addCoo(int a, int b, std::string type)
{
    data.push_back(new Coo(a, b, type));
}

Data& Data::operator=(Data t)
{
    if ((t.data).size() != data.size()) {
        while (data.size() != 0)
            data.erase(data.begin());
        for (Coo *cc : t.data) {
            data.push_back(new Coo(cc->x, cc->y, cc->type));
        }
    } else {
        int count = 0;
        for (Coo *cc : data) {
            cc->x = (t.data[count])->x;
            cc->y = (t.data[count])->y;
            cc->type = (t.data[count])->type;
            count++;
        }
    }
}
