#include <iostream>

void alert(bool condition, std::string passMessage, std::string failMessage)  {
    if (!condition) {
        std::cerr << "\033[31m" << failMessage + "\033[0m\n";
        exit(0);
    }
    else
        std::cerr << "\033[32m" << passMessage + "\033[0m\n";
}
