#include "../Headers/Interface/Interface.cpp"
#include "../Headers/DataBase/DataBase.cpp"

int main()
{
    Interface *console = Interface::get();
    console->Run();

    Interface::release();

    return 0;
}