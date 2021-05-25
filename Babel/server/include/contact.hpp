/*
** EPITECH PROJECT, 2018
** contact.hpp
** File description:
** contact
*/

#include <vector>
#include <string>

class contact
{
public:
    std::string str;
    std::string pseudo;
    std::string public_addr;
    std::string local_addr;
    contact(std::string ps, std::string one, std::string two);
    std::string in_str();
};

class contact_list
{
public:
    std::vector<contact> list;
    contact_list();
    void add(contact);
    contact get(std::string);
};
