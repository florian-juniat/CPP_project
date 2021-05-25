/*
** EPITECH PROJECT, 2018
** name
** File description:
** contact
*/

#include <iostream>
#include <fstream>
#include "contact.hpp"

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

std::string contact::in_str()
{
    return (str);
}

contact::contact(std::string ps, std::string one, std::string two)
{
    str = ps + " " + one + " " + two;
    pseudo = ps;
    public_addr = one;
    local_addr = two;
}

contact_list::contact_list()
{
    std::ifstream flux("contact/list_contact.txt");

    if (flux) {
        std::string line;
        while (getline(flux, line)) {
            std::vector<std::string> ss = split(line, ' ');
            contact p(ss[0], ss[1], ss[2]);
            list.push_back(p);
        }
    } else
        std::cout << "open file contact is impossible" << std::endl;
}

void contact_list::add(contact one)
{
    list.push_back(one);
}

contact contact_list::get(std::string pseudo)
{
    contact p("NO", "NO", "NO");

    for (contact co : list) {
        if (co.pseudo.compare(pseudo) == 0)
            return (co);
    }
    return (p);
}
