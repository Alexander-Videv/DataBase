#include "Headers/Interface/Interface.cpp"
#include "Headers/DataBase/DataBase.cpp"

int main()
{
    Interface::get()->Run();

    Interface::release();

    return 0;
}