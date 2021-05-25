/*
** EPITECH PROJECT, 2018
** data.hpp
** File description:
** data
*/

#include <iostream>
#include <vector>
#include <string>


class Coo
{
public:
    int x;
    int y;
    Coo(int, int);
    ~Coo();
};

class Data
{
public:
    Data();
    ~Data();
    void addCoo(int, int);
    std::vector<Coo *> data;
};
