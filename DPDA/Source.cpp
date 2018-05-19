#include <iostream>
#include "DPDA.h"

int main()
{
    DPDA machine;
    try
    {
        machine.conformityCheck("");
        machine.conformityCheck("()00");
        machine.conformityCheck("00(1111)00");
        machine.conformityCheck("00(1111)00000");
        machine.conformityCheck("00(11)");
    }
    catch (...)
    {
        std::cout << "Error";
    }
    system("pause");
    return 0;
}