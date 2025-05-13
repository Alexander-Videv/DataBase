#include "Interface.hpp"

bool Interface::Run()
{
    std::string command;
    std::cin >> command;
    std::cout << command;

    return true;
}