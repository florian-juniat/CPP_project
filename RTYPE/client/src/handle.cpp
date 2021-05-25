/*
** EPITECH PROJECT, 2018
** handle.cpp
** File description:
** handle
*/

#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> split(std::string str, char c)
{
    std::string stock = "";
    std::vector<std::string> ret;

    for (std::string::iterator it = str.begin(); it != str.end(); it++) {
        if (*it == c) {
            ret.push_back(stock);
            stock = "";
        } else {
            stock+=(*it);
        }
    }
    ret.push_back(stock);
    return (ret);
}

