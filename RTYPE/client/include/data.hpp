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
    std::string type;
    Coo(int, int, std::string);
    ~Coo();
};

class Data
{
public:
    Data();
    ~Data();
    void addCoo(int, int, std::string);
    Data& operator=(Data);
    std::vector<Coo *> data;
};
