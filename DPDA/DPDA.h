#pragma once
#include <string>
#include <stack>
#include <array>

class DPDA
{
private:
    std::stack<int> _stack;
    int _currentState;
    using States = void(DPDA::*)();
    std::array<std::array<std::array<States, 3>, 4>, 4> _dpdaTable;
    
    void toState000();
    void toState001();

    void toState111();
    void toState120();
    void toState121();

    void toState211();

    void toState300();
    void toState301();
    void toState330();

    void toUndefinedState();

    int signalInterpreter(const char preSignal) const;
    int getFromStack();
public:
    DPDA();
    bool conformityCheck(std::string inputString);
};

