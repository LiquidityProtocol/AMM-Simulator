#include <iostream>

void alert(bool condition, std::string failMessage, std::string passMessage = "")   {
    if (!condition) {
        std::cerr << "\033[31m" << failMessage + "\033[0m\n";
        exit(0);
    }
    else if (passMessage != "")
        std::cerr << "\033[32m" << passMessage + "\033[0m\n";
}
