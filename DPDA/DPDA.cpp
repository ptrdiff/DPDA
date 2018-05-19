#include "DPDA.h"
#include <iostream>


DPDA::DPDA()
    : _stack(),
      _currentState(0),
      _dpdaTable({
          {
              {
                  {
                      {{&DPDA::toState000, &DPDA::toState001, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}},
                      {{&DPDA::toState120, &DPDA::toState121, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}}
                  }
              },
              {
                  {
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toState211, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}},
                      {{&DPDA::toState330, &DPDA::toUndefinedState, &DPDA::toUndefinedState}}
                  }
              },
              {
                  {
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toState111, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}}
                  }
              },
              {
                  {
                      {{&DPDA::toState300, &DPDA::toState301, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}},
                      {{&DPDA::toUndefinedState, &DPDA::toUndefinedState, &DPDA::toUndefinedState}}
                  }
              }
          }
      })
{
}

void DPDA::toState000()
{
    _currentState = 0;
    _stack.push(-1);
    _stack.push(0);
}

void DPDA::toState001()
{
    _currentState = 0;
    _stack.push(0);
    _stack.push(0);
}

void DPDA::toState111()
{
    _currentState = 1;
}

void DPDA::toState120()
{
    _currentState = 1;
    _stack.push(-1);
}

void DPDA::toState121()
{
    _currentState = 1;
    _stack.push(0);
}

void DPDA::toState211()
{
    _currentState = 2;
    _stack.push(0);
}

void DPDA::toState300()
{
    _currentState = 3;
    _stack.push(-1);
    _stack.push(0);
}

void DPDA::toState301()
{
    _currentState = 3;

}

void DPDA::toState330()
{
    _currentState = 3;
    _stack.push(-1);
}

void DPDA::toUndefinedState()
{
    _currentState = -1;
}

int DPDA::signalInterpreter(const char preSignal) const
{
    switch (preSignal)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '(':
            return 2;
        case ')':
            return 3;
        default:
            return -1;
    }
}

int DPDA::getFromStack()
{
    switch (_stack.top())
    {
    case  0: _stack.pop(); return 1;
    case  1: _stack.pop(); return 2;
    default: _stack.pop(); return 0;
    }
}

bool DPDA::conformityCheck(std::string inputString)
{
    _stack.push(-1);
    _currentState = 0;
    for(auto simbol: inputString)
    {
        if(signalInterpreter(simbol) == -1)
        {
            std::cout << simbol << " - wrong simbol!" << '\n';
            std::stack<int>().swap(_stack);
            return false;
        }

        (this->*_dpdaTable[_currentState][signalInterpreter(simbol)][getFromStack()])();

        if (_currentState == -1)
        {
            std::cout << inputString << " is uncorrect! " << '\n';
            std::cout << "first unconform simbol - " << simbol << '\n';
            std::stack<int>().swap(_stack);
            return false;
        }
    }
    if (_currentState == 3 && _stack.top() == -1)
    {
        _stack.pop();
        std::cout << inputString << " is correct!" << '\n';
        return true;
    }
    if(!_stack.empty())
    {
        std::cout << inputString << " is uncorrect! " << '\n';
        if (_stack.top() != -1)
        {
            std::cout << "first unconform simbol - " << _stack.top() << '\n';
        }
        std::stack<int>().swap(_stack);
        return false;
    }
    throw 10;
}

